/*
 * Copyright 2018 Scott Vokes
 *
 * See LICENCE for the full copyright terms.
 */

#include <stddef.h>

#include "../../class.h"
#include "../../class_lookup.h"

class_constructor *
re_class_like(const char *name)
{
	(void) name;

	/* no character classes in this dialect */
	return NULL;
}
