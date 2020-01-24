#include "./lib/lib.h"
#include "chara_data.h"
#include "item.h"

//0:FIG, 1:MAG, 2:PRI, 3:THI, 4:BIS, 5:SAM, 6:LOR, 7:NIN.
char CLASS_NAME[8][4] = {
	"FIG",
	"MAG",
	"PRI",
	"THI",
	"BIS",
	"SAM",
	"LOR",
	"NIN",
};

char ALIGN_NAME[5][2] = {
	"",		//
	"G",	//1
	"N",	//2
	"",		//
	"E",	//4
};

CharaData* Player_initialize_player() {
	CharaData *p = malloc_ex(sizeof(CharaData));
	return p;
}

CharaData TRAINING_GROUND[20] = {
	{0,"FIGHTER1",0,0,1,11,8,7,8,8,9,150,0,12,12,1,0,16,0,4,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,128,128,0,0,0,0,0},{1,8,11,53,0,0,0,0},4,0,0,0,0},
	{1,"FIGHTER2",0,0,1,11,8,7,8,8,9,150,0,10,10,1,0,16,0,4,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,128,128,0,0,0,0,0},{1,8,11,53,0,0,0,0},4,0,0,0,0},
	{2,"PRIEST1", 0,2,1,8,8,11,8,8,9,150,0,8,8,1,0,16,0,10,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,128,128,0,0,0,0,0},{3,8,11,53,0,0,0,0},4,0,0,0,0},
	{3,"THIEF1",  4,3,2,7,7,7,9,11,15,150,0,6,6,1,0,16,0,10,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,128,128,0,0,0,0,0},{6,7,11,53,0,0,0,0},4,0,0,0,0},
	{4,"WIZARD1", 0,1,1,8,11,7,8,8,9,150,0,4,4,1,0,15,0,10,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,0,0,0,0,0,0,0},{9,53,0,0,0,0,0,0},2,0,0,0,0},
	{5,"WIZARD2", 0,1,1,8,11,7,8,8,9,150,0,4,4,1,0,14,0,10,{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{128,0,0,0,0,0,0,0},{9,53,0,0,0,0,0,0},2,0,0,0,0},
};


/**************************************
 * PTキャラのタイプ別打撃防御フラグ.
 **************************************/
int Chara_get_save_melee_attack_flag(CharaData *chara) {
	int resistant_flag = 0;
	int ii;
	if(chara->item_count == 0) {
		return resistant_flag;
	}

	for(ii=0;ii<chara->item_count;ii++) {
		if((chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
			ItemData *item = &ITEM_MST[chara->item_ids[ii]];
			resistant_flag |= item->save_melee_attack;			
		}
	}

	return resistant_flag;
}


/**************************************
 * PTキャラの命中力.
 **************************************/
char Chara_get_hit_rate(CharaData *chara) {
	int lv_bonus, str_bonus, equipement_st, ii;
	unsigned short chara_lv;
	chara_lv = chara->lv;
	if(chara_lv > 0xFF) {
		chara_lv = 0xFF;
	}
	//LVボーナス.
	if(chara->job == JOB_MAG || chara->job == JOB_THI || chara->job == JOB_BIS) {
		lv_bonus = chara_lv / 5;
	}else{
		lv_bonus = chara_lv / 3 + 2;
	}

	//strボーナス.
	if(chara->str >= 16) {
		str_bonus = chara->str - 15;
	}else if(chara->str >= 6) {
		str_bonus = 0;
	}else{
		str_bonus = chara->str - 6;
	}

	equipement_st = 0;
	for(ii=0;ii<chara->item_count;ii++) {

		// 装備中か？.
		if((chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
			ItemData *item = &ITEM_MST[chara->item_ids[ii]];
			// alignmentが一致するか？.
			if(item->alignment != ITEM_ALIGNMENT_ALL && chara->alignment != item->alignment) {
				equipement_st += -1;
			}else{
				equipement_st += item->str;
			}
		}
	}

	return lv_bonus + str_bonus + equipement_st;
}






/******************************************
 * PTキャラのクリティカルフラグ.
 ******************************************/
unsigned char Chara_get_critical_flag(CharaData *chara) {
	int ii;

	if(chara->job == JOB_NIN) {
		return 1;
	}

	for(ii=0;ii<chara->item_count;ii++) {

		// 装備中か？.
		if((chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
			ItemData *item = &ITEM_MST[chara->item_ids[ii]];
			// alignmentが一致するか？.
			if(item->alignment != ITEM_ALIGNMENT_ALL && chara->alignment != item->alignment) {
				return 0;
			}else{
				return item->critical_flag != 0x00;
			}
		}
	}

	return 0;
}


/******************************************
 * PTキャラのヒーリング値.
 ******************************************/
char Chara_get_healing_value(CharaData *chara) {
	int ii,healing_value;
	healing_value = 0;
	for(ii=0;ii<chara->item_count;ii++) {

		// 装備中か？.
		if((chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
			ItemData *item = &ITEM_MST[chara->item_ids[ii]];
			healing_value += item->healing;
		}
	}

	return healing_value;
}


/******************************************
 * PTキャラの攻撃回数.
 ******************************************/
unsigned char Chara_get_attack_count(CharaData *chara) {
	int ii,attack_count,weapon_attack_count;
	attack_count = 0;
	weapon_attack_count = 0;
	for(ii=0;ii<chara->item_count;ii++) {

		// 武器でかつ装備中か?
		if((chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
			ItemData *item = &ITEM_MST[chara->item_ids[ii]];
			if(item->item_type == ITEM_TYPE_WEAPON) {
				weapon_attack_count += item->min_attack_count;
			}
		}
	}

	if(chara->job == JOB_MAG || chara->job == JOB_PRI || chara->job == JOB_THI || chara->job == JOB_BIS) {
		attack_count = Util_Max(1, weapon_attack_count);
	}else if(chara->job == JOB_FIG || chara->job == JOB_SAM || chara->job == JOB_LOR) {
		attack_count = Util_Max(chara->lv/5+1, weapon_attack_count);
	}else{
		attack_count = Util_Max(chara->lv/5+2, weapon_attack_count);
	}

	return attack_count;
}

/******************************************
 * PTキャラの属性抵抗値.
 ******************************************/
unsigned char Chara_get_attribute_resistant(CharaData *chara) {
	int ii;
	unsigned char resistant_flag = 0;

	for(ii=0;ii<chara->item_count;ii++) {
		ItemData *item = &ITEM_MST[chara->item_ids[ii]];
		resistant_flag |= item->attribute_resistant;
	}

	return resistant_flag;
}


unsigned char Chara_count_unequiped_item(CharaData *chara) {
	int ii;
	unsigned char itemCnt = 0;

	for(ii=0;ii<chara->item_count;ii++) {
		if( (chara->item_status[ii] & ITEM_STATUS_EQUIP) == 0) {
			itemCnt++;
		}
	}

	return itemCnt;
}

ItemData* Chara_get_equiped_weapon(CharaData *chara) {
	ItemData *item;
	int ii;

	for(ii=0;ii<chara->item_count;ii++) {
		if( (chara->item_status[ii] & ITEM_STATUS_EQUIP) > 0 ){
			item = &ITEM_MST[chara->item_ids[ii]];
			if(item->item_type == ITEM_TYPE_WEAPON) {
				return item;
			}
		}
	}

	return 0;
}