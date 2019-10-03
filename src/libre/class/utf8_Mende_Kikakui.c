/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Mende_Kikakui_fsm(const struct fsm_options *opt)
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

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[2], 0x9e)) { goto error; }
	for (i = 0xa0; i <= 0xa2; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[2], s[4], 0xa3)) { goto error; }
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[5], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

