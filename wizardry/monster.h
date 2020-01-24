#ifndef MONSTER_H
#define MONSTER_H

#include "dice.h"

#define MONSTER_TYPE_FIGHTER 0x00
#define MONSTER_TYPE_MAGE 0x01
#define MONSTER_TYPE_PRIEST 0x02
#define MONSTER_TYPE_THIEF 0x03
#define MONSTER_TYPE_HOBBIT 0x04
#define MONSTER_TYPE_GIANT 0x05
#define MONSTER_TYPE_MYTH 0x06
#define MONSTER_TYPE_DRAGON 0x07
#define MONSTER_TYPE_ANIMAL 0x08
#define MONSTER_TYPE_BEAST 0x09
#define MONSTER_TYPE_UNDEAD 0x0A
#define MONSTER_TYPE_DEMON 0x0B
#define MONSTER_TYPE_INSECT 0x0C
#define MONSTER_TYPE_MAGICAL_CREATURE 0x0D


typedef struct MonsterData_t {
	unsigned char id;
	unsigned char unknown_name_length;		//不確定名単数形 文字列長.
	unsigned char unknown_name[15];			//不確定名単数形.
	unsigned char unknown_names_length;		//不確定名複数形 文字列長.
	unsigned char unknown_names[15];		//不確定名複数形.

	unsigned char known_name_length;		//確定名単数形 文字列長.
	unsigned char known_name[15];			//確定名単数形.
	unsigned char known_names_length;		//確定名複数形 文字列長.
	unsigned char known_names[15];			//確定名複数形.

	unsigned char monster_type;
	// 0x00:戦士, 0x01:魔術師, 0x02:僧侶, 0x03:盗賊, 0x04:小人・忍者(存在しない),
    // 0x05:巨人, 0x06:神話, 0x07:竜, 0x08:動物, 0x09:獣人,
    // 0x0A:不死, 0x0B:悪魔, 0x0C:昆虫, 0x0D:魔法生物

	DiceExpr encount_dice;				//出現数ダイス
	DiceExpr hp_dice;					//ＨＰダイス（ダイス個数 = モンスターＬＶとなる).
	
	short ac;
	unsigned char attack_count;
	DiceExpr damage_dice[6];			//攻撃ごとのダメージダイス.

	unsigned char energy_drain_lv;		//エナドレＬＶ.
	unsigned char healing;				//ヒーリング.

	unsigned char item_table_fix;		//アイテムテーブル（玄室).
	unsigned char item_table_wanderer;	//アイテムテーブル（徘徊).
	
	unsigned char back_monster_id;		//後続モンスターＩＤ.
	unsigned char back_monster_rate;	//後続モンスター出現確立（２５６文率）.

	unsigned char mage_lv;				//MAGE呪文LV.
	unsigned char priest_lv;			//PRIEST呪文LV.

	unsigned char breath_attr;			//ブレス属性.
	unsigned char magic_reflect_rate;	//呪文無効化率（256分率）.
	unsigned char attribute_resistant;	//属性抵抗.
	unsigned char special_attack_weak_point_flag;	//弱点・特殊攻撃フラグ.
	// bit7: 常に0
    // bit6: 仲間を呼ぶ
    // bit5: 逃走する
    // bit4: 弱点:眠
    // bit3: 特殊:首
    // bit2: 特殊:麻
    // bit1: 特殊:毒
    // bit0: 特殊:石

    int exp;

}MonsterData;

typedef struct MonsterGroup_t {
	/* data */
	unsigned char group_hit_rate;
	unsigned char group_count;	// 2
	unsigned char hit_rates[5];	// {65,35}
	unsigned char id_length[5];	// {5,3}
	unsigned char ids[5][10];	// {{1,2,3,4,5}, {2,3,4}}
	unsigned char floor;		// 1

}MonsterGroup;

MonsterGroup* Monster_lotGroup(const char floor_num);
void Monster_lotMonster(const MonsterGroup* group, MonsterData* party[4][9], char* encount_num, int floor);
void Monster_clearParty(MonsterData* party[4][9]);

extern MonsterData MONSTER_MST[101];
extern MonsterGroup MONSTER_GRP_MST[30];
#endif