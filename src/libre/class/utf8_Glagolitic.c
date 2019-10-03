/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Glagolitic_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	fsm_state_t s[8] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 8; i++) {
		if (!fsm_addstate(fsm, &s[i])) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0xb0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[4], 0xb1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[6], 0x9e)) { goto error; }
	for (i = 0x80; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x9e; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[6], s[7], 0x80)) { goto error; }
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x88; i <= 0x98; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x9b; i <= 0xa1; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0xa3; i <= 0xa4; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xaa; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[5], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

