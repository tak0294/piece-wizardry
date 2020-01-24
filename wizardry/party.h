#ifndef PARTY_H
#define PARTY_H
#include "./lib/lib.h"
#include "chara_data.h"

typedef struct Party_t {
	unsigned char light_value;
	unsigned char identify_enemy_flag;
	char permanent_ac_bonus;
	unsigned char spell_cancel_flag;
	CharaData *party_member[6];
	unsigned char member_count;
	unsigned char x;
	unsigned char y;
	unsigned char floor;
	unsigned char direction;


} Party;

extern Party PARTY;
extern void Party_initialize();
extern BOOL Party_add(CharaData *c);
extern void Party_display_member();

#endif