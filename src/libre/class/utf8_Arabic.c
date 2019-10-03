/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Arabic_fsm(const struct fsm_options *opt)
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

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xd8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xd9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xda)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[4], 0xdb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[5], 0xdd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], 0xe0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[7], 0xef)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[8], 0xf0)) { goto error; }
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[9], i)) { goto error; }
	}
	for (i = 0x86; i <= 0x8b; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[9], i)) { goto error; }
	}
	for (i = 0x8d; i <= 0x9a; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[1], s[9], 0x9c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[9], 0x9e)) { goto error; }
	for (i = 0xa0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[9], i)) { goto error; }
	}
	for (i = 0x81; i <= 0x8a; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[9], i)) { goto error; }
	}
	for (i = 0x96; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[9], i)) { goto error; }
	}
	for (i = 0xb1; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x9c; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[9], i)) { goto error; }
	}
	for (i = 0x9e; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[9], i)) { goto error; }
	}
	for (i = 0x90; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[6], s[12], 0xa2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[6], s[13], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[3], 0xae)) { goto error; }
	for (i = 0xb0; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[3], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[7], s[3], 0xba)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[5], 0xad)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[5], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[15], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[16], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[17], 0xb6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[18], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[19], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[7], s[20], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[10], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[8], s[11], 0x9e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[10], s[14], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[21], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[22], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[23], 0xba)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[11], s[24], 0xbb)) { goto error; }
	for (i = 0xa0; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[9], i)) { goto error; }
	}
	for (i = 0xb6; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[9], i)) { goto error; }
	}
	for (i = 0x94; i <= 0xa1; i++) {
		if (!fsm_addedge_literal(fsm, s[13], s[9], i)) { goto error; }
	}
	for (i = 0xa3; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[13], s[9], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[14], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x81; i++) {
		if (!fsm_addedge_literal(fsm, s[15], s[9], i)) { goto error; }
	}
	for (i = 0x93; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[15], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[16], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[17], s[9], i)) { goto error; }
	}
	for (i = 0x92; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[17], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x87; i++) {
		if (!fsm_addedge_literal(fsm, s[18], s[9], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[18], s[9], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[19], s[9], i)) { goto error; }
	}
	for (i = 0xb6; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[19], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[20], s[9], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[21], s[9], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[21], s[9], i)) { goto error; }
	}
	for (i = 0xa1; i <= 0xa2; i++) {
		if (!fsm_addedge_literal(fsm, s[21], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[21], s[9], 0xa4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[9], 0xa7)) { goto error; }
	for (i = 0xa9; i <= 0xb2; i++) {
		if (!fsm_addedge_literal(fsm, s[21], s[9], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xb7; i++) {
		if (!fsm_addedge_literal(fsm, s[21], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[21], s[9], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[21], s[9], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x87)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x8b)) { goto error; }
	for (i = 0x8d; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	for (i = 0x91; i <= 0x92; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x94)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x97)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0x9f)) { goto error; }
	for (i = 0xa1; i <= 0xa2; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0xa4)) { goto error; }
	for (i = 0xa7; i <= 0xaa; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	for (i = 0xac; i <= 0xb2; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xb7; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	for (i = 0xb9; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[9], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[22], s[9], 0xbe)) { goto error; }
	for (i = 0x80; i <= 0x89; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[9], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x9b; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[9], i)) { goto error; }
	}
	for (i = 0xa1; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[9], i)) { goto error; }
	}
	for (i = 0xa5; i <= 0xa9; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[9], i)) { goto error; }
	}
	for (i = 0xab; i <= 0xbb; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[9], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[24], s[9], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[9], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

