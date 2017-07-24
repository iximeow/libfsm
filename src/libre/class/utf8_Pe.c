/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Pe_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[23] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 23; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[4], 0xe3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[5], 0xef)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], ')')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], ']')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], '}')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[8], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[7], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[15], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[16], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[17], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[18], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[19], 0x9f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[20], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[21], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[22], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[9], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[10], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[11], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[12], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[13], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[14], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[6], 0x9c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[6], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[6], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x8f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x91)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x95)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x97)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[6], 0x9b)) { goto error; }
	for (i = 0x9e; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[6], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[10], s[6], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0x98)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0xb6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0xba)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[6], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x84)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x9c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[6], 0x9e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[6], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[6], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[6], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[6], 0xa0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[6], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[6], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[6], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[16], s[6], 0x8e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[6], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[6], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[6], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xad)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xb1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xb3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[6], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0xad)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[6], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x84)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x8a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x8e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x92)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x94)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x96)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[6], 0x98)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[6], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[6], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[6], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[6], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[6], 0xa5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[6], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[6], 0xa9)) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[6], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

