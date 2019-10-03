/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Sinhala_fsm(const struct fsm_options *opt)
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

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[3], 0xb6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[4], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[6], 0x91)) { goto error; }
	for (i = 0x82; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0x9a; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	for (i = 0xb3; i <= 0xbb; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[3], s[5], 0xbd)) { goto error; }
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[4], s[5], 0x8a)) { goto error; }
	for (i = 0x8f; i <= 0x94; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[4], s[5], 0x96)) { goto error; }
	for (i = 0x98; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0xb2; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[6], s[7], 0x87)) { goto error; }
	for (i = 0xa1; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[5], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

