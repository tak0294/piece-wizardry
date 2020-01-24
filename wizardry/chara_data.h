#ifndef CHARA_DATA_H
#define CHARA_DATA_H

#include "item.h"

#define JOB_FIG 0
#define JOB_MAG 1
#define JOB_PRI 2
#define JOB_THI 3
#define JOB_BIS 4
#define JOB_SAM 5
#define JOB_LOR 6
#define JOB_NIN 7

#define STATUS_OK 0
#define STATUS_ASLEEP 1
#define STATUS_AFRAID 2
#define STATUS_PARALY 3
#define STATUS_STONED 4
#define STATUS_DEAD 5
#define STATUS_ASHED 6
#define STATUS_LOST 7

#define ITEM_STATUS_EQUIP 128
#define ITEM_STATUS_CURSE 64
#define ITEM_STATUS_UNKNOWN 32

/*****
 * struct for character data.
 */
typedef struct CharaData_t {
	unsigned char id;
	unsigned char name[8];
	unsigned char race_type;	// 0:HUMAN, 1:ELF, 2:DWARF, 3:GNOME, 4:HOBBIT.
	unsigned char job;			// 0:FIG, 1:MAG, 2:PRI, 3:THI, 4:BIS, 5:SAM, 6:LOR, 7:NIN.
	unsigned char alignment;	// 1:GOOD, 2:NEUTRAL, 4:EVIL.
	/** status **/
	unsigned char str;
	unsigned char iq;
	unsigned char piety;
	unsigned char vitality;
	unsigned char agility;
	unsigned char luck;

	int gold;
	int exp;

	unsigned short hp;
	unsigned short hp_max;
	unsigned short lv;

	unsigned char status;		// 0:OK, 1:ASLEEP, 2:AFRAID, 3:PARALY, 4:STONED, 5:DEAD, 6:ASHED, 7:LOST.
	short age;
	int week_count;				// 0x34で+1歳.

	char ac;

	unsigned char mage_mp[7];		//MAGE系呪文MP.
	unsigned char priest_mp[7];		//PRIEST系呪文MP.
	unsigned char mage_mp_max[7];	//MAGE系呪文最大MP.
	unsigned char priest_mp_max[7];	//PRIEST系呪文最大MP.

	unsigned char learned_magic[7];	//習得呪文（呪文ＩＤ順のビットセット).

	unsigned char item_status[8];	//アイテムステータスビット.
	// bit7: 装備
    // bit6: 呪い
    // bit5: 不確定名
    // bit4: 
    // bit3: 
    // bit2: 
    // bit1: 
    // bit0: 

	unsigned char item_ids[8];	//所持アイテムＩＤ.
	unsigned char item_count;	//所持アイテム数.
	unsigned char x;		//x座標.
	unsigned char y;		//y座標.
	unsigned char floor;	//階層.
	unsigned char poison_value;	//ＰＯＩＳＯＮ値.

} CharaData;

extern char CLASS_NAME[8][4];
extern char ALIGN_NAME[5][2];
extern CharaData TRAINING_GROUND[20];

CharaData* Player_initialize_player();
int Chara_get_save_melee_attack_flag(CharaData *chara);
char Chara_get_hit_rate(CharaData *chara);
unsigned char Chara_get_critical_flag(CharaData *chara);
char Chara_get_healing_value(CharaData *chara);
unsigned char Chara_get_attack_count(CharaData *chara);
unsigned char Chara_get_attribute_resistant(CharaData *chara);
unsigned char Chara_count_unequiped_item(CharaData *chara);
ItemData* Chara_get_equiped_weapon(CharaData *chara);
#endif