/*
 * Copyright 2017 Shannon F. Stewman
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include <fsm/fsm.h>
#include <fsm/options.h>
#include <fsm/bool.h>
#include <fsm/pred.h>
#include <fsm/walk.h>

#include <adt/alloc.h>
#include <adt/set.h>
#include <adt/stateset.h>
#include <adt/edgeset.h>
#include <adt/tupleset.h>

#include "internal.h"
#include "walk2.h"

/*
 * 3-tuple (a, b, comb) for walking the two DFAs.
 * a & b are the states of the original FSMs, at least one of which
 * must be present.
 * comb is the state of the combined FSM.
 */
struct fsm_walk2_tuple {
	int have_a;
	int have_b;
	fsm_state_t a;
	fsm_state_t b;
	fsm_state_t comb;
};

/* comparison of fsm_walk2_tuples for the (ordered) set */
static int
cmp_walk2_tuple(const void *a, const void *b)
{
	const struct fsm_walk2_tuple *pa = a, *pb = b;
	ptrdiff_t delta;

	assert(pa->have_a || pa->have_b);
	assert(pb->have_a || pb->have_b);

	if (pa->have_a != pb->have_a) {
		return -1;
	}

	if (pa->have_b != pb->have_b) {
		return +1;
	}

	delta = (pa->a > pb->a) - (pa->a < pb->a);
	if (delta == 0) {
		delta = (pa->b > pb->b) - (pa->b < pb->b);
	}

	return delta;
}

struct fsm_walk2_data {
	struct fsm_walk2_tuple_pool *head;
	size_t top;

	struct fsm *new;
	struct tuple_set *states;

	/*
	 * Table for which combinations are valid bits.
	 * There are four combinations:
	 *
	 *   a_end  b_end    AB  bit endmask
	 *   false  false    00  0       0x1
	 *   false  true     01  1       0x2
	 *   true   false    10  2       0x4
	 *   true   true     11  3       0x8
	 *
	 * Here bit is the bit that expresses whether that combination
	 * is a valid end state or not. We need four bits.
	 *
	 * Operation    Requirement             endmask
	 * intersect    both true                   0x8
	 * subtract     first true, second false    0x4
	 * union        either true                 0xE
	 */
	unsigned endmask :4; /* bit table for what states are end states in the combined graph */
	unsigned edgemask:4; /* bit table for which edges should be followed */
};

/*
 * Size of the tuple pool (see comment in struct fsm_walk2_tuple_pool below).
 *
 * XXX: revisit what would be a good size for this.
 */
#define FSM_WALK2_TUPLE_POOL_SIZE 1024

/*
 * Allocation pool to allow for easy cleanup of the struct
 * fsm_walk2_tuple that are allocated while walking the two DFAs.
 *
 * The tuples allocated during walking the DFAs are only needed during
 * the walk. Pooling the allocation allows all of the tuples to be
 * cleaned up at once when the walk is finished.
 */
struct fsm_walk2_tuple_pool {
	struct fsm_walk2_tuple_pool *next;
	struct fsm_walk2_tuple items[FSM_WALK2_TUPLE_POOL_SIZE];
};

static void
fsm_walk2_data_free(const struct fsm *fsm, struct fsm_walk2_data *data)
{
	struct fsm_walk2_tuple_pool *p, *next;

	if (data->states) {
		tuple_set_free(data->states);
	}

	for (p = data->head; p != NULL; p = next) {
		next = p->next;
		f_free(fsm->opt->alloc, p);
	}

	if (data->new) {
		fsm_free(data->new);
	}
}

static struct fsm_walk2_tuple *
alloc_walk2_tuple(struct fsm_walk2_data *data)
{
	struct fsm_walk2_tuple *item;
	struct fsm_walk2_tuple_pool *pool;

	if (data->head == NULL) {
		goto new_pool;
	}

	if (data->top >= (sizeof data->head->items / sizeof data->head->items[0])) {
		goto new_pool;
	}

	item = &data->head->items[data->top++];

	goto done;

new_pool:

	pool = f_malloc(data->new->opt->alloc, sizeof *pool);
	if (pool == NULL) {
		return NULL;
	}

	pool->next = data->head;
	data->head = pool;
	data->top  = 1;

	item = &pool->items[0];

done:

	item->have_a = 0;
	item->have_b = 0;

	return item;
}

static unsigned
walk2mask(int has_a, int has_b)
{
	if (has_a) {
		return has_b ? FSM_WALK2_BOTH  : FSM_WALK2_ONLYA;
	}

	return has_b ? FSM_WALK2_ONLYB : FSM_WALK2_NEITHER;
}

static struct fsm_walk2_tuple *
fsm_walk2_tuple_new(struct fsm_walk2_data *data,
	const struct fsm *fsm_a, fsm_state_t a,
	const struct fsm *fsm_b, fsm_state_t b)
{
	struct fsm_walk2_tuple *p;
	const struct fsm_options *opt;
	int is_end;

	int have_a = !!fsm_a, have_b = !!fsm_b;

	assert(data->states);
	assert(have_a || have_b);

	{
		struct fsm_walk2_tuple lkup, *q;

		lkup.have_a = have_a;
		lkup.have_b = have_b;

		if (have_a) {
			lkup.a = a;
		}
		if (have_b) {
			lkup.b = b;
		}

		q = tuple_set_contains(data->states, &lkup);
		if (q != NULL) {
			return q;
		}
	}

	p = alloc_walk2_tuple(data);
	if (p == NULL) {
		return NULL;
	}

	if (!fsm_addstate(data->new, &p->comb)) {
		return NULL;
	}

	data->new->states[p->comb]->tmp.visited = 0;
	p->have_a = have_a;
	p->have_b = have_b;

	if (have_a) {
		p->a = a;
	}
	if (have_b) {
		p->b = b;
	}
	if (!tuple_set_add(data->states, p)) {
		return NULL;
	}

	is_end = data->endmask & walk2mask(have_a
		&& fsm_isend(fsm_a, a), have_b && fsm_isend(fsm_b, b));

	if (is_end) {
		fsm_setend(data->new, p->comb, 1);

		opt = data->new->opt;
		if (opt != NULL && opt->carryopaque != NULL) {
			fsm_state_t states[2];
			size_t nst = 0;

			if (have_a) {
				states[nst++] = a;
			}

			if (have_b) {
				states[nst++] = b;
			}

			if (nst > 0) {
				/*
				 * This is slightly cheesed, but it avoids
				 * constructing a set just to pass these two
				 * states to the carryopaque function
				 */
				opt->carryopaque(states, nst, data->new, p->comb);
			}
		}
	}

	return p;
}

static int
fsm_walk2_edges(struct fsm_walk2_data *data,
	const struct fsm *a, const struct fsm *b, struct fsm_walk2_tuple *start)
{
	fsm_state_t qa, qb, qc;
	int have_qa, have_qb;
	struct edge_iter ei, ej;
	const struct fsm_edge *ea, *eb;

	assert(a != NULL);
	assert(b != NULL);

	assert(data->new != NULL);
	assert(data->states != NULL);

	assert(start != NULL);
	assert(start->have_a || start->have_b);

	/* This performs the actual walk by a depth-first search. */
	have_qa = start->have_a;
	have_qb = start->have_b;
	if (have_qa) {
		qa = start->a;
	}
	if (have_qb) {
		qb = start->b;
	}
	qc = start->comb;

	assert(qc < data->new->statecount);

	/* fast exit if we've already visited the combined state */
	if (data->new->states[qc]->tmp.visited) {
		return 1;
	}

	/* mark combined state as visited */
	data->new->states[qc]->tmp.visited = 1;

	/*
	 * fsm_walk2_edges walks the edges of two graphs, generating combined
	 * states.
	 *
	 * To do this, we need to provide some way to iterate over the
	 * cross-product of the states of both, but in a way that
	 * satisfies the operators. There are two decision points:
	 *
	 *   1) whether to follow an edge to combined state (qa', qb'),
	 *      where either qa' or qb' may be absent
	 *
	 *   2) whether a combined state (qa, qb) is an end state of the
	 *      two graphs, where either qa or qb may be absent, and
	 *      either may be an end state.
	 *
	 * For each decision, there are four possible states and two
	 * possible outcomes (follow/don't-follow and end/not-end).
	 * These decisions can thus be compactly represented with two
	 * 4-bit tables.  The follow table is in data->edgemask.  The end
	 * state table is in data->endmask.
	 *
	 * There are two major loops, over the edges of A and over the
	 * edges of B.  In the first loop, we handle the ONLYA and BOTH
	 * cases.  In the second loop we handle the ONLYB cases.
	 */

	/* If qb is absent, we can follow edges if ONLYA is allowed. */
	if (!have_qb && !(data->edgemask & FSM_WALK2_ONLYA)) {
		return 1;
	}

	/* If qa is absent, jump ahead to the ONLYB loop */
	if (!have_qa) {
		goto only_b;
	}

	/*
	 * If we can't follow ONLYA or BOTH edges, then jump ahead to
	 * the ONLYB loop
	 */
	if (!(data->edgemask & (FSM_WALK2_BOTH|FSM_WALK2_ONLYA))) {
		goto only_b;
	}

	/* take care of only A and both A&B edges */
	for (ea = edge_set_first(a->states[qa]->edges, &ei); ea != NULL; ea = edge_set_next(&ei)) {
		struct state_iter dia, dib;
		fsm_state_t da;

		eb = have_qb ? fsm_hasedge_literal(b, qb, ea->symbol) : NULL;

		/*
		 * If eb == NULL we can only follow this edge if ONLYA
		 * edges are allowed
		 */
		if (!eb && !(data->edgemask & FSM_WALK2_ONLYA)) {
			continue;
		}

		for (state_set_reset(ea->sl, &dia); state_set_next(&dia, &da); ) {
			fsm_state_t db;
			int have_db;

			if (eb != NULL) {
				state_set_reset(eb->sl, &dib);
				if (state_set_next(&dib, &db)) {
					have_db = 1;
				} else {
					have_db = 0;
				}
			} else {
				have_db = 0;
			}

			/*
			 * for loop with break to handle the situation where there is no
			 * corresponding edge in the B graph. This will proceed through
			 * the loop once, even when db == NULL.
			 */
			for (;;) {
				struct fsm_walk2_tuple *dst;

				dst = fsm_walk2_tuple_new(data, a, da, have_db ? b : NULL, db);
				if (dst == NULL) {
					return 0;
				}

				assert(dst->comb < data->new->statecount);

				if (!fsm_addedge_literal(data->new, qc, dst->comb, ea->symbol)) {
					return 0;
				}

				/*
				 * depth-first traversal of the graph, but only traverse
				 * if the state has not yet been visited
				 */
				if (!data->new->states[dst->comb]->tmp.visited) {
					if (!fsm_walk2_edges(data, a, b, dst)) {
						return 0;
					}
				}

				if (have_db) {
					continue;
				}

				/* if db is absent, fetch the next edge in B */
				if (!state_set_next(&dib, &db)) {
					/* if db is still absent, stop iterating over edges in B */
					break;
				}
				have_db = 1;
			}
		}
	}

only_b:

	/* fast exit if ONLYB cases aren't allowed */
	if (!have_qb || !(data->edgemask & FSM_WALK2_ONLYB)) {
		return 1;
	}

	/* take care of only B edges */
	for (eb = edge_set_first(b->states[qb]->edges, &ej); eb != NULL; eb = edge_set_next(&ej)) {
		struct state_iter dib;
		fsm_state_t db;

		/* if A has the edge, it's not an only B edge */
		if (have_qa && fsm_hasedge_literal(a, qa, eb->symbol)) {
			continue;
		}

		/*
		 * ONLYB loop is simpler because we only deal with
		 * states in the B graph (the A state is always NULL)
		 */
		for (state_set_reset(eb->sl, &dib); state_set_next(&dib, &db); ) {
			for (;;) {
				struct fsm_walk2_tuple *dst;

				dst = fsm_walk2_tuple_new(data, NULL, 0, b, db);
				if (dst == NULL) {
					return 0;
				}

				assert(dst->comb < data->new->statecount);

				if (!fsm_addedge_literal(data->new, qc, dst->comb, eb->symbol)) {
					return 0;
				}

				/*
				 * depth-first traversal of the graph, but only traverse
				 * if the state has not yet been visited
				 */
				if (!data->new->states[dst->comb]->tmp.visited) {
					if (!fsm_walk2_edges(data, a, b, dst)) {
						return 0;
					}
				}
			}
		}
	}

	return 1;
}

struct fsm *
fsm_walk2(const struct fsm *a, const struct fsm *b,
	unsigned edgemask, unsigned endmask)
{
	static const struct fsm_walk2_data zero;
	struct fsm_walk2_data data = zero;

	fsm_state_t sa, sb;
	struct fsm_walk2_tuple *tup0;
	struct fsm *new;
	int have_a, have_b;

	assert(a != NULL);
	assert(b != NULL);

	assert(fsm_all(a, fsm_isdfa));
	assert(fsm_all(b, fsm_isdfa));

	have_a = fsm_getstart(a, &sa);
	have_b = fsm_getstart(b, &sb);

	if (!have_a && !have_b) {
		/*
		 * if both A and B lack a start states,
		 * the result will be empty
		 */
		goto done;
	}

	if (!have_b) {
		if (endmask & FSM_WALK2_ONLYA) {
			/* must be a copy of A */
			return fsm_clone(a);
		}

		/*
		 * !have_b and combined states cannot be ONLYA,
		 * so the result will be empty
		 */
		goto done;
	}

	if (!have_a) {
		if (endmask & FSM_WALK2_ONLYB) {
			/* must be a copy of B */
			return fsm_clone(b);
		}

		/*
		 * !have_a and combined states cannot be ONLYB, so the
		 * result will be empty
		 */
		goto done;
	}

	data.edgemask = edgemask;
	data.endmask  = endmask;

	data.new = fsm_new(a->opt);
	if (data.new == NULL) {
		goto error;
	}

	data.states = tuple_set_create(data.new->opt->alloc, cmp_walk2_tuple);
	if (data.states == NULL) {
		goto error;
	}

	tup0 = fsm_walk2_tuple_new(&data, a, sa, b, sb);
	if (tup0 == NULL) {
		goto error;
	}

	assert(tup0->a == sa);
	assert(tup0->b == sb);
	assert(tup0->comb < data.new->statecount);
	assert(!data.new->states[tup0->comb]->tmp.visited); /* comb not yet been traversed */

	fsm_setstart(data.new, tup0->comb);
	if (!fsm_walk2_edges(&data, a, b, tup0)) {
		goto error;
	}

done:

	new = data.new;
	data.new = NULL; /* avoid freeing new FSM */

	fsm_clear_tmp(new);

	fsm_walk2_data_free(a, &data);

	return new;

error:

	fsm_walk2_data_free(a, &data);

	return NULL;
}

