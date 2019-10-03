/*
 * Copyright 2019 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <fsm/fsm.h>

#include <adt/alloc.h>
#include <adt/stateset.h>

#define SET_INITIAL 8

struct state_set {
	const struct fsm_alloc *alloc;
	fsm_state_t *a;
	size_t i;
	size_t n;
};

static int
state_set_cmpval(fsm_state_t a, fsm_state_t b)
{
	return (a > b) - (a < b);
}

int
state_set_cmp(const struct state_set *a, const struct state_set *b)
{
	assert(a != NULL);
	assert(a->a != NULL);
	assert(b != NULL);
	assert(b->a != NULL);

	if (a->i != b->i) {
		return a->i - b->i;
	}

	return memcmp(a->a, b->a, a->i * sizeof *a->a);
}

/*
 * Return where an item would be, if it were inserted
 */
static size_t
state_set_search(const struct state_set *set, fsm_state_t state)
{
	size_t start, end;
	size_t mid;

	assert(set != NULL);

	start = mid = 0;
	end = set->i;

	while (start < end) {
		int r;
		mid = start + (end - start) / 2;
		r = state_set_cmpval(state, set->a[mid]);
		if (r < 0) {
			end = mid;
		} else if (r > 0) {
			start = mid + 1;
		} else {
			return mid;
		}
	}

	return mid;
}

struct state_set *
state_set_create(const struct fsm_alloc *a)
{
	struct state_set *set;

	set = f_malloc(a, sizeof *set);
	if (set == NULL) {
		return NULL;
	}

	set->a = f_malloc(a, SET_INITIAL * sizeof *set->a);
	if (set->a == NULL) {
		return NULL;
	}

	set->alloc = a;
	set->i = 0;
	set->n = SET_INITIAL;

	return set;
}

void
state_set_free(struct state_set *set)
{
	if (set == NULL) {
		return;
	}

	assert(set->a != NULL);

	free(set->a);
	free(set);
}

int
state_set_add(struct state_set *set, fsm_state_t state)
{
	size_t i;

	assert(set != NULL);

	i = 0;

	/*
	 * If the item already exists in the set, return success.
	 */
	if (!state_set_empty(set)) {
		i = state_set_search(set, state);
		if (state_set_cmpval(state, set->a[i]) == 0) {
			return state;
		}
	}

	if (set->i) {
		/* We're at capacity. Get more */
		if (set->i == set->n) {
			fsm_state_t *new;

			new = f_realloc(set->alloc, set->a, (sizeof *set->a) * (set->n * 2));
			if (new == NULL) {
				return 0;
			}

			set->a = new;
			set->n *= 2;
		}

		if (state_set_cmpval(state, set->a[i]) > 0) {
			i++;
		}

		memmove(&set->a[i + 1], &set->a[i], (set->i - i) * (sizeof *set->a));
		set->a[i] = state;
		set->i++;
	} else {
		set->a[0] = state;
		set->i = 1;
	}

	assert(state_set_contains(set, state));

	return 1;
}

void
state_set_remove(struct state_set *set, fsm_state_t state)
{
	size_t i;

	if (state_set_empty(set)) {
		return;
	}

	i = state_set_search(set, state);
	if (state_set_cmpval(state, set->a[i]) == 0) {
		if (i < set->i) {
			memmove(&set->a[i], &set->a[i + 1], (set->i - i - 1) * (sizeof *set->a));
		}

		set->i--;
	}

	assert(!state_set_contains(set, state));
}

int
state_set_empty(const struct state_set *set)
{
	if (set == NULL) {
		return 1;
	}

	return set->i == 0;
}

fsm_state_t
state_set_only(const struct state_set *set)
{
	assert(set != NULL);
	assert(set->n >= 1);
	assert(set->i == 1);

	return set->a[0];
}

int
state_set_contains(const struct state_set *set, fsm_state_t state)
{
	size_t i;

	if (state_set_empty(set)) {
		return 0;
	}

	i = state_set_search(set, state);
	if (state_set_cmpval(state, set->a[i]) == 0) {
		return 1;
	}

	return 0;
}

size_t
state_set_count(const struct state_set *set)
{
	if (set == NULL) {
		return 0;
	}

	assert(set->a != NULL);

	return set->i;
}

void
state_set_reset(struct state_set *set, struct state_iter *it)
{
	it->i = 0;
	it->set = set;
}

int
state_set_next(struct state_iter *it, fsm_state_t *state)
{
	assert(it != NULL);
	assert(state != NULL);

	if (it->set == NULL) {
		return 0;
	}

	if (it->i >= it->set->i) {
		return 0;
	}

	*state = it->set->a[it->i];

	it->i++;

	return 1;
}

int
state_set_hasnext(struct state_iter *it)
{
	assert(it != NULL);

	return it->set && it->i + 1 < it->set->i;
}

const fsm_state_t *
state_set_array(const struct state_set *set)
{
	assert(set != NULL);

	if (set == NULL) {
		return NULL;
	}

	return set->a;
}

void
state_set_rebase(struct state_set *set, fsm_state_t base)
{
	size_t i;

	if (set == NULL) {
		return;
	}

	for (i = 0; i < set->i; i++) {
		set->a[i] += base;
	}
}

void
state_set_replace(struct state_set *set, fsm_state_t old, fsm_state_t new)
{
	size_t i;

	if (set == NULL) {
		return;
	}

	for (i = 0; i < set->i; i++) {
		if (set->a[i] == old) {
			set->a[i] = new;
		}
	}
}

