/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Bopomofo_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	fsm_state_t s[6] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 6; i++) {
		if (!fsm_addstate(fsm, &s[i])) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xcb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe3)) { goto error; }
	for (i = 0xaa; i <= 0xab; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[2], s[4], 0x84)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[5], 0x86)) { goto error; }
	for (i = 0x85; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[3], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[3], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[3], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

