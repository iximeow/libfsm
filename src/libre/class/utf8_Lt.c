/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Lt_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[6] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 6; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xc7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0xb2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[4], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[5], 0xbf)) { goto error; }
	for (i = 0x88; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[3], i)) { goto error; }
	}
	for (i = 0x98; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[3], i)) { goto error; }
	}
	for (i = 0xa8; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[4], s[3], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[3], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[3], 0xbc)) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[3], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

