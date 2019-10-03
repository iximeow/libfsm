/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <fsm/fsm.h>

#include <adt/set.h>
#include <adt/stateset.h>
#include <adt/edgeset.h>
#include <adt/xalloc.h>

#include "internal.h"

static int
fsm_state_cmpedges(const void *a, const void *b)
{
	const struct fsm_edge *ea, *eb;

	assert(a != NULL);
	assert(b != NULL);

	ea = a;
	eb = b;

	/* N.B. various edge iterations rely on the ordering of edges to be in
	 * ascending order.
	 */
	return (ea->symbol > eb->symbol) - (ea->symbol < eb->symbol);
}

int
fsm_addedge_epsilon(struct fsm *fsm,
	fsm_state_t from, fsm_state_t to)
{
	assert(fsm != NULL);
	assert(from < fsm->statecount);
	assert(to < fsm->statecount);

	if (fsm->states[from]->epsilons == NULL) {
		fsm->states[from]->epsilons = state_set_create(fsm->opt->alloc);
		if (fsm->states[from]->epsilons == NULL) {
			return 0;
		}
	}

	if (!state_set_add(fsm->states[from]->epsilons, to)) {
		return 0;
	}

	return 1;
}

int
fsm_addedge_any(struct fsm *fsm,
	fsm_state_t from, fsm_state_t to)
{
	int i;

	assert(fsm != NULL);
	assert(from < fsm->statecount);
	assert(to < fsm->statecount);

	for (i = 0; i <= UCHAR_MAX; i++) {
		if (!fsm_addedge_literal(fsm, from, to, (unsigned char) i)) {
			return 0;
		}
	}

	return 1;
}

int
fsm_addedge_literal(struct fsm *fsm,
	fsm_state_t from, fsm_state_t to,
	char c)
{
	struct fsm_edge *e, new;

	assert(fsm != NULL);
	assert(from < fsm->statecount);
	assert(to < fsm->statecount);

	if (fsm->states[from]->edges == NULL) {
		fsm->states[from]->edges = edge_set_create(fsm->opt->alloc, fsm_state_cmpedges);
		if (fsm->states[from]->edges == NULL) {
			return 0;
		}
	}

	new.symbol = c;
	e = edge_set_contains(fsm->states[from]->edges, &new);
	if (e == NULL) {
		e = malloc(sizeof *e);
		if (e == NULL) {
			return 0;
		}

		e->symbol = c;
		e->sl = state_set_create(fsm->opt->alloc);
		if (e->sl == NULL) {
			return 0;
		}

		if (!edge_set_add(fsm->states[from]->edges, e)) {
			return 0;
		}
	}

	if (!state_set_add(e->sl, to)) {
		return 0;
	}

	return 1;
}

struct fsm_edge *
fsm_hasedge_literal(const struct fsm *fsm, fsm_state_t state, char c)
{
	struct fsm_edge *e, search;

	assert(fsm != NULL);
	assert(state < fsm->statecount);

	if (fsm->states[state]->edges == NULL) {
		return NULL;
	}

	search.symbol = (unsigned char) c;
	e = edge_set_contains(fsm->states[state]->edges, &search);
	if (e == NULL || state_set_empty(e->sl)) {
		return NULL;
	}

	return e;
}

