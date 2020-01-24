#ifndef ITEM_H
#define ITEM_H
#include "dice.h"

#define ITEM_TYPE_WEAPON 0x00
#define ITEM_TYPE_ARMOR 0x01
#define ITEM_TYPE_SHIELD 0x02
#define ITEM_TYPE_HELMET 0x03
#define ITEM_TYPE_ARM 0x04
#define ITEM_TYPE_TOOL 0x05
#define ITEM_TYPE_ACCESSORY 0x06

#define ITEM_SPOWER_STR 0x01
#define ITEM_SPOWER_NINJA 0x11
#define ITEM_SPOWER_HP 0x16
#define ITEM_SPOWER_HEAL_ALL 0x17


#define ITEM_ALIGNMENT_GOOD 0x01
#define ITEM_ALIGNMENT_NEUTRAL 0x02
#define ITEM_ALIGNMENT_EVIL 0x04
#define ITEM_ALIGNMENT_ALL 0x07




typedef struct ItemData_t{

    unsigned char id;                   //ITEM_ID.
	unsigned char unknown_name_length;	//不確定名_文字列長
	unsigned char unknown_name[16];
	unsigned char known_name_length;	//確定名_文字列長.
	unsigned char known_name[17];

	unsigned char item_type;
	// 0x00:武器
    // 0x01:鎧
    // 0x02:盾
    // 0x03:兜
    // 0x04:小手
    // 0x05:薬/巻物/イベントアイテム
    // 0x06:その他の装備品

    unsigned char alignment;		//アラインメント.
    // 0x02:中立, 0x04:悪, 0x07:全て

    unsigned char cursed;			//呪い 0x00 = 呪われていない, 0xFF = 呪われている.
    unsigned char special_power;	//スペシャルパワー.
    // 0x01:STR+1
    // 0x11:忍者に転職
    // 0x16:最大HP+1
    // 0x17:パーティーのHPフル
    //
    // SCROLL of PAIN: 0x00
    // SCROLL of AGONY: 0x00
    // RING of MOVEMENT: 0x00
    // RING of DISPELLING: 0x00
    // 全てのSTATUE/KEY/RIBBON: 0x00
    // その他: 0xFF

    unsigned char broken_rate;		//使用時・SP発動時に壊れる確立（256分率).
	unsigned char broken_item_id;	//壊れたときに変化するアイテムID.
	unsigned int buy_price;		//買値.
	unsigned char initial_stock_num;	//初期在庫 0xFF = 無限.
	unsigned char use_magic_id;		//使用時の効果（魔法ID). 0xFF = 使用不可.
	unsigned char equipment_job;	//装備可能な職業, 上位BitからNLSBTPMF.

	char healing;	//ヒーリング.
	char ac;		//装備時AC修正値.
	char str;		//装備時STR修正値.
	unsigned char min_attack_count;	//最低攻撃回数.
	DiceExpr damage_dice;

	unsigned char critical_flag;	//ARMOR of LORDS, SHURIKENのみ 0xFF ほかはすべて 0x00.

	unsigned short save_melee_attack;	//タイプ別打撃防御.
	// bit15: 竜
    // bit14: 神話
    // bit13: 巨人
    // bit12: 小人・忍者(該当モンスターなし)
    // bit11: 盗賊
    // bit10: 僧侶
    // bit9: 魔術師
    // bit8: 戦士
    // bit7: ?(タイプ15に対応。該当モンスターなし)
    // bit6: ?(タイプ14に対応。該当モンスターなし)
    // bit5: 魔法生物
    // bit4: 昆虫
    // bit3: 悪魔
    // bit2: 不死
    // bit1: 獣人
    // bit0: 動物

    unsigned char attribute_resistant;	//属性抵抗.
    // bit7: ?
    // bit6: 呪文
    // bit5: 石化
    // bit4: 吸収

    // bit3: 毒
    // bit2: 冷気
    // bit1: 火
    // bit0: 友好
    // WERDNA'S AMULET: 0xFE

    unsigned short double_damage_type;	//タイプ別倍打.
    // bit15: 竜
    // bit14: 神話
    // bit13: 巨人
    // bit12: 小人・忍者(該当モンスターなし)

    // bit11: 盗賊
    // bit10: 僧侶
    // bit9: 魔術師
    // bit8: 戦士
    
    // bit7: ?(タイプ15に対応。該当モンスターなし)
    // bit6: ?(タイプ14に対応。該当モンスターなし)
    // bit5: 魔法生物
    // bit4: 昆虫
    
    // bit3: 悪魔
    // bit2: 不死
    // bit1: 獣人
    // bit0: 動物

}ItemData;

typedef struct ItemGroup_t {
    unsigned char item_hit_rates[3];
    unsigned char item_id_length[3];
    unsigned char item_ids[3][30];
    unsigned int gold_range[2];
    unsigned char trap_bit;
} ItemGroup;

extern ItemData ITEM_MST[101];
extern ItemGroup ITEM_GRP_MST[30];
#endif