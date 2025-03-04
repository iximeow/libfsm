/*
 * Copyright 2018 Shannon Stewman
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>

#include <adt/hashset.h>

typedef int item_t;

#include "hashset.inc"

static int
cmp_int(const void *a, const void *b)
{
	const int *pa = * (const int * const *) a;
	const int *pb = * (const int * const *) b;

	if (*pa > *pb)      return +1;
	else if (*pa < *pb) return -1;
	else                return  0;
}

static unsigned long
hash_int(const void *a)
{
	return hashrec(a, sizeof * (const int *) a);
}

int main(void) {
	struct hashset *s = hashset_create(NULL, hash_int, cmp_int);
	struct hashset_iter iter;
	int *p;
	int a[3] = {1, 2, 3};
	int seen[3] = {0, 0, 0};
	int i;
	assert(hashset_add(s, &a[0]));
	assert(hashset_add(s, &a[1]));
	assert(hashset_add(s, &a[2]));

	for (p = hashset_first(s, &iter); p != NULL; p = hashset_next(&iter)) {
		assert(*p == 1 || *p == 2 || *p == 3);
		seen[*p - 1] = 1;
	}

	for (i = 0; i < 3; i++) {
		assert(seen[i]);
	}

	return 0;
}
