#include "./lib/lib.h"
#include "chara_data.h"
#include "party.h"

Party PARTY;

void Party_initialize() {
	int ii;

	PARTY.light_value 			= 0;
	PARTY.identify_enemy_flag 	= 0;
	PARTY.permanent_ac_bonus 	= 0;
	PARTY.spell_cancel_flag     = 0;
	for(ii=0;ii<6;ii++) {
		PARTY.party_member[ii] = 0;
	}
	PARTY.member_count = 0;
	PARTY.x = 0;
	PARTY.y = 0;
	PARTY.floor = 0;
	PARTY.direction = 0;

}

BOOL Party_check_already_in(CharaData *c) {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		if(PARTY.party_member[ii] == c) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Party_add(CharaData *c) {
	if(Party_check_already_in(c)) {
		return FALSE;
	}

	if(PARTY.member_count < 6) {
		PARTY.party_member[PARTY.member_count] = c;
		PARTY.member_count+=1;
	}
	return FALSE;
}

void Party_display_member() {
	int y = 46;
	int ii;
	pceFontSetType(2 + 128);
	pceFontSetPos(0,y);
	pceFontPrintf("# CHAR NAME CLASS AC HITS STATUS");

	y+=6;
	for(ii=0;ii<PARTY.member_count;ii++) {
		pceFontSetPos(0,y);
		pceFontPrintf("%d %-8s  %s-%s %2d %4d  %4d", (ii+1), 
													PARTY.party_member[ii]->name,
													ALIGN_NAME[PARTY.party_member[ii]->alignment],
													CLASS_NAME[PARTY.party_member[ii]->job],
													PARTY.party_member[ii]->ac,
													PARTY.party_member[ii]->hp,
													PARTY.party_member[ii]->hp_max);
		y+=6;		
	}

}