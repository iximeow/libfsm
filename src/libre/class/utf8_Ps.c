/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Ps_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	fsm_state_t s[25] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 25; i++) {
		if (!fsm_addstate(fsm, &s[i])) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], '(')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '[')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '{')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[4], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[5], 0xe3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], 0xef)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[18], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[24], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[7], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[8], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[9], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[10], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[11], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[12], 0x9f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[13], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[14], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[15], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[16], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[17], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[19], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[20], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[21], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[22], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[23], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[1], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[1], 0x9e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[1], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[1], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[9], s[1], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[10], s[1], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[10], s[1], 0x8a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[10], s[1], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xae)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xb0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xb2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[1], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[12], s[1], 0xae)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x83)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x87)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x8f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x91)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x93)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x95)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[1], 0x97)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[1], 0x98)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[1], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[1], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[1], 0xa2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[1], 0xa4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[1], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[1], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[16], s[1], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x8a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x8e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x94)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x96)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x98)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[1], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[1], 0xba)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[1], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[1], 0xbf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0x97)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[1], 0xbf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x83)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x87)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[1], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[1], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[1], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[23], s[1], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[23], s[1], 0x9f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[23], s[1], 0xa2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[24], s[1], 0x9b)) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[1], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

