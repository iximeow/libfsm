/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Cuneiform_fsm(const struct fsm_options *opt)
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

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[2], 0x92)) { goto error; }
	for (i = 0x80; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[2], s[3], 0x90)) { goto error; }
	for (i = 0x92; i <= 0x94; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[2], s[4], 0x8e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[5], 0x91)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[6], 0x95)) { goto error; }
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[7], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[7], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[7], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[7], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

