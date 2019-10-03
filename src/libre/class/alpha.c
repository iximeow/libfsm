/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
class_alpha_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	fsm_state_t s[2] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (!fsm_addstate(fsm, &s[i])) {
			goto error;
		}
	}

	for (i = 0x00; i <= 0x40; i++) {
		if (!fsm_addedge_literal(fsm, s[0], s[0], i)) { goto error; }
	}
	for (i = 0x5b; i <= 0x60; i++) {
		if (!fsm_addedge_literal(fsm, s[0], s[0], i)) { goto error; }
	}
	for (i = 0x7b; i <= 0xff; i++) {
		if (!fsm_addedge_literal(fsm, s[0], s[0], i)) { goto error; }
	}
	for (i = 0x41; i <= 0x5a; i++) { /* 'A' .. 'Z' */
		if (!fsm_addedge_literal(fsm, s[0], s[1], i)) { goto error; }
	}
	for (i = 0x61; i <= 0x7a; i++) { /* 'a' .. 'z' */
		if (!fsm_addedge_literal(fsm, s[0], s[1], i)) { goto error; }
	}
	if (!fsm_addedge_any(fsm, s[1], s[1])) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[1], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

