#ifndef BATTLE_MGR_H
#define BATTLE_MGR_H
#include "monster.h"
#include "chara_data.h"

#define BATTLE_COMMAND_FIGHT 0
#define BATTLE_COMMAND_PARRY 1
#define BATTLE_COMMAND_SPELL 2
#define BATTLE_COMMAND_DISPELL 3
#define BATTLE_COMMAND_USEITEM 4
#define BATTLE_COMMAND_RUN 5
#define BATTLE_COMMAND_TAKEBACK 6
#define BATTLE_COMMAND_DONE 128

#define BATTLE_CURSOR_NEXT 0
#define BATTLE_CURSOR_BACK 1

#define BATTLE_FIRST_ATTACK_NONE 0
#define BATTLE_FIRST_ATTACK_PARTY 1
#define BATTLE_FIRST_ATTACK_MONSTER 2

#define BATTLE_MODE_PLAYER_COMMAND_SELECT 0
#define BATTLE_MODE_PLAYER_ITEM_SELECT 1
#define BATTLE_MODE_PLAYER_MAGIC_SELECT 2
#define BATTLE_MODE_PLAYER_MONSTER_GROUP_SELECT 3
#define BATTLE_MODE_PLAYER_PARTY_MEMBER_SELECT 4
#define BATTLE_MODE_PLAYER_TURN 5
#define BATTLE_MODE_MONSTER_TURN 6

#define MESSAGE_ROW 10
#define MESSAGE_COL 256



extern MonsterData *Battle_monster_party[4][9];

extern unsigned char Battle_command_cursor;
extern unsigned char Battle_input_player_index;
extern unsigned char Battle_monster_id_in_group[4];
extern int Battle_member_hp[42];							// 味方/敵のHP.
extern int Battle_member_hp_max[42];						// 味方/敵の最大HP.
extern unsigned char Battle_member_lv[42];					// 味方/敵のLv (0xFFを超えたら0xFFに補正).
extern unsigned char Battle_monster_ac[36];					// 敵のAC.
extern unsigned char Battle_monster_status[4][9];			// 敵のステータス.
extern unsigned char Battle_monster_magic_lv_in_group[4];	// 敵グループのMAGE呪文LV
extern unsigned char Battle_monster_priest_lv_in_group[4];	// 敵グループのPRIEST呪文LV
extern unsigned char Battle_monster_alives_in_group[4];		// 敵グループの生存者数.
extern unsigned char Battle_main_enemy_id;					// メイン敵ID（画像を表示するモンスター）.


void Battle_debug_disp();

void Battle_update();

void Battle_display();
void Battle_display_enemy_party();
void Battle_initialize();
void Battle_initialize_encount(int floor);
void Battle_turn_initialize();
void Battle_display_player_commands();
BOOL Battle_is_contain_undead_enemy();
void Battle_set_command_list();
void Battle_set_player_index(int index);
void Battle_move_command_cursor(int direction);
void Battle_move_monster_group_cursor(int direction);
void Battle_move_item_cursor(int direction);
void Battle_move_player_party_cursor(int direction);

void Battle_calc_party_lv_sum();
void Battle_calc_monster_lv_sum();
void Battle_calc_party_alive_sum();
void Battle_calc_monster_alive_sum();
void Battle_update_main_monster_id();
void Battle_set_party_save_melee_attack_attr();
void Battle_set_party_hit_rates();
void Battle_set_party_critical_flag();
void Battle_set_party_healing_value();
void Battle_set_party_attack_count();
void Battle_set_party_attribute_resitant();
void Battle_set_party_status(int position, int status);
void Battle_decide_player_command();
void Battle_decide_player_use_item();

void Battle_set_action_order();
void Battle_tick_turn();
int Battle_get_next_turn_chara();
#endif