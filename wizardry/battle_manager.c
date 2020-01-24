#include "./lib/lib.h"
#include "battle_manager.h"
#include "chara_data.h"
#include "party.h"
#include "item.h"
#include "monster.h"

MonsterData *Battle_monster_party[4][9];
unsigned char Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
unsigned char Battle_monster_group_cursor;
unsigned char Battle_party_member_cursor;
unsigned char Battle_item_magic_cursor;
unsigned char Battle_message_heap[MESSAGE_ROW][MESSAGE_COL] = {{0}};
unsigned char Battle_message_length;
unsigned char Battle_message_index;

char Battle_monster_group_count[4];
int Battle_party_lv_sum;		// PT���ŃX�e�[�^�X�ُ�ɂ������Ă��Ȃ��҂�LV���v
int Battle_monster_lv_sum;		// �X�e�[�^�X�ُ�ɂ������Ă��Ȃ��G��LV���v
int Battle_party_alive_sum;		// PT�����Ґ�
unsigned char Battle_monster_alives_in_group[4];		// �G�O���[�v�̐����Ґ�
unsigned char Battle_monster_magic_lv_in_group[4];	// �G�O���[�v��MAGE����LV
unsigned char Battle_monster_priest_lv_in_group[4];	// �G�O���[�v��PRIEST����LV
unsigned char Battle_main_enemy_id;					// ���C���GID�i�摜��\�����郂���X�^�[�j.
unsigned char Battle_monster_id_in_group[4];			// �G�O���[�v�̃����X�^�[ID.
int Battle_party_save_melee_attack_flag[6];			// PT�L�����̃^�C�v�ʑŌ��h��t���O
		 char Battle_party_hit_rates[6];			// PT�L�����̖�����.
unsigned char Battle_party_critical_flag[6];		// PT�L�����̃N���e�B�J���t���O.
         char Battle_party_healing_value[6];		// PT�L�����̃q�[�����O.
unsigned char Battle_party_attack_count[6];			// PT�L�����̍U����.
unsigned char Battle_party_attribute_resistant[6];	// PT�L�����̑�����R.
unsigned char Battle_party_status[6];				// PT�L�����̃X�e�[�^�X.
unsigned char Battle_monster_status[4][9];			// �G�̃X�e�[�^�X.
int Battle_member_hp[42];							// ����/�G��HP.
int Battle_member_hp_max[42];						// ����/�G�̍ő�HP.
unsigned char Battle_member_lv[42];					// ����/�G��Lv (0xFF�𒴂�����0xFF�ɕ␳).
unsigned char Battle_action_id[42];					// �퓬���̍s��ID.
unsigned char Battle_action_order[42];				// �퓬���̍s������.
unsigned char Battle_monster_ac[36];				// �G��AC.
unsigned char Battle_party_attack_group[6];			// PT�L�����N�^�̍U���ΏۃO���[�v�ԍ�.
unsigned char Battle_party_luck1[6];				// �^���l1.
unsigned char Battle_party_luck2[6];				// �^���l2.
unsigned char Battle_party_luck3[6];				// �^���l3.
unsigned char Battle_party_luck4[6];				// �^���l4.
unsigned char Battle_party_luck5[6];				// �^���l5.
		  int Battle_party_double_attack_type[6];	// �p�[�e�B�̃^�C�v�ʔ{��.
unsigned char Battle_party_is_drained[6];			// PT�L�������h���C�����󂯂����ǂ����̃t���O.
		  int Battle_party_lv[6];					// PT�L�����̃��x��.
unsigned char Battle_party_poison_value[6];			// PT�L������POISON�l.

unsigned char Battle_command_list[7];
unsigned char Battle_command_length;
unsigned char Battle_command_names[7][10] = {
	"FIGHT",
	"PARRY",
	"SPELL",
	"DISPELL",
	"USE ITEM",
	"RUN",
	"BACK",
};

unsigned char Battle_first_attack_party;	// �搧�p�[�e�B 0=none, 1=party, 2=monster.
unsigned char Battle_player_possible_item_ids[8];
unsigned char Battle_player_use_item_id[6];
unsigned char Battle_player_item_magic_target[6];
int Battle_current_turn_chara_index = 0;

// �O�����J�ϐ�.
unsigned char Battle_command_cursor;
unsigned char Battle_input_player_index;

// debug.
int debug_val1;
int debug_val2;


/*****************
 * �f�o�b�O�\��.
 *****************/
void Battle_debug_disp() {
	int ii,jj;
	jj = 1;
	pceFontSetType(2);
	pceFontSetPos(0, 10);
	//pceFontPrintf("%d, %d, %d", Battle_party_lv_sum, Battle_monster_lv_sum, Battle_party_alive_sum);
	pceFontPrintf("%d, %d, %d", Battle_current_turn_chara_index, debug_val1, debug_val2);
	for(ii=0;ii<6;ii++) {
		pceFontSetPos(0, 10 + ii*6);
		// pceFontPrintf("%d, %d(%d)", ii, Battle_member_hp[ii+6], Battle_member_hp_max[ii+6]);
		// pceFontPrintf("%d", Battle_party_hit_rates[ii]);
		// pceFontPrintf("%d", debug_val1);
	}
}


/******************************************************************************************************
 * �퓬�N���X�S�̏�����.
 ******************************************************************************************************/
void Battle_initialize() {
	int ii;
	for(ii=0;ii<42;ii++) {
		Battle_action_id[ii] 	 = 0;
		Battle_action_order[ii]  = 0;
		Battle_member_hp[ii] 	 = 0;
		Battle_member_hp_max[ii] = 0;
	}

	Battle_command_cursor 	= 0;
	Battle_party_lv_sum 	= 0;
}




/******************************************************************************************************
 * �^�[��������.
 ******************************************************************************************************/
void Battle_turn_initialize() {
	int ii;
	for(ii=0;ii<42;ii++) {
		Battle_action_id[ii] 	= 0;
		Battle_action_order[ii] = 0;
	}

	for(ii=0;ii<6;ii++) {
		Battle_player_use_item_id[ii] = 0xFF;
	}
	Battle_input_player_index = 0;

	Battle_calc_party_lv_sum();			// �p�[�e�BLV�̍��v
	Battle_calc_monster_lv_sum();		// �����X�^�[LV�̍��v
	Battle_calc_party_alive_sum();		// �p�[�e�B�������̍��v
	Battle_calc_monster_alive_sum();	// �����X�^�[�������̍��v
	Battle_update_main_monster_id();	// ���C�������X�^�[ID�̍X�V.
	Battle_set_command_list();			// �R�}���h���X�g�쐬.
	Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
}


void Battle_update_main_monster_id() {
	int ii;
	for(ii=0;ii<4;ii++) {
		// �퓬�O���[�v�̓G�����C���G.
		if(Battle_monster_alives_in_group[ii] > 0) {
			Battle_main_enemy_id = Battle_monster_id_in_group[ii];
			break;
		}
	}
}

/*************************************************************************************************
 * PT�L�����̃^�C�v�ʑŌ��h��t���O����.
 *************************************************************************************************/
void Battle_set_party_save_melee_attack_attr() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_save_melee_attack_flag[ii] = Chara_get_save_melee_attack_flag(PARTY.party_member[ii]);
	}
}

void Battle_set_party_hit_rates() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_hit_rates[ii] = Chara_get_hit_rate(PARTY.party_member[ii]);
	}
}

/*************************************************************************************************
 * �p�[�e�B�����o�[�̃X�e�[�^�X�ُ�łȂ������o�[��LV���v.
 *************************************************************************************************/
void Battle_calc_party_lv_sum() {
	int ii;

	// LV���v������.
	Battle_party_lv_sum = 0;
	for(ii=0;ii<PARTY.member_count;ii++) {
		if(PARTY.party_member[ii]->status == STATUS_OK) {
			Battle_party_lv_sum += PARTY.party_member[ii]->lv;
		}
	}
}

/*************************************************************************************************
 * �p�[�e�B�����o�[�̐����Ґ����Z�o.
 *************************************************************************************************/
void Battle_calc_party_alive_sum() {
	int ii;

	//�����Ґ�������.
	Battle_party_alive_sum = 0;
	for(ii=0;ii<PARTY.member_count;ii++) {
		if(PARTY.party_member[ii]->status < STATUS_PARALY) {
			Battle_party_alive_sum++;
		}
	}
}

/*************************************************************************************************
 * PT�L�����N�^�[�̃N���e�B�J���t���O.
 *************************************************************************************************/
void Battle_set_party_critical_flag() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_critical_flag[ii] = Chara_get_critical_flag(PARTY.party_member[ii]);
	}	
}

/*************************************************************************************************
 * PT�L�����N�^�[�̃q�[�����O�l.
 *************************************************************************************************/
void Battle_set_party_healing_value() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_healing_value[ii] = Chara_get_healing_value(PARTY.party_member[ii]);
	}	
}

/*************************************************************************************************
 * PT�L�����N�^�[�̍U����.
 *************************************************************************************************/
void Battle_set_party_attack_count() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_attack_count[ii] = Chara_get_attack_count(PARTY.party_member[ii]);
	}	
}

/*************************************************************************************************
 * PT�L�����N�^�[�̑�����R�l.
 *************************************************************************************************/
void Battle_set_party_attribute_resitant() {
	int ii;
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_party_attribute_resistant[ii] = Chara_get_attribute_resistant(PARTY.party_member[ii]);
	}	
}

/*************************************************************************************************
 * PT�L�����N�^�[�̃X�e�[�^�X�ݒ�.
 *************************************************************************************************/
void Battle_set_party_status(int position, int status) {
	if(position > PARTY.member_count) {
		return;
	}
	Battle_party_status[position] = status;
}

/**************************************************************************************************
 * �����X�^�[�̃X�e�[�^�X�ُ�łȂ������o�[LV�̍��v.
 *************************************************************************************************/
void Battle_calc_monster_lv_sum() {
	int ii,jj;

	// LV���v������.
	Battle_monster_lv_sum = 0;
	for(ii=0;ii<4;ii++) {
		for(jj=0;jj<9;jj++) {
			if(Battle_monster_status[ii][jj] == STATUS_OK) {
				Battle_monster_lv_sum += Battle_member_lv[ii*9 + jj];
			}
		}
	}
}

/*************************************************************************************************
 * �G�O���[�v�̐����Ґ����Z�o.
 *************************************************************************************************/
 void Battle_calc_monster_alive_sum() {
 	int ii,jj;

	for(ii=0;ii<4;ii++) {
		Battle_monster_alives_in_group[ii] = 0;

		for(jj=0;jj<9;jj++) {
			if(Battle_monster_status[ii][jj] < STATUS_DEAD) {
				Battle_monster_alives_in_group[ii]++;
			}
		}
	}	
 }


/*************************************************************************************************
 * �퓬������.
 *************************************************************************************************/
void Battle_initialize_encount(int floor) {

	int ii,jj;
	MonsterGroup *g = Monster_lotGroup(floor);
	Battle_input_player_index = 0;
	
	Battle_command_cursor 		= 0;	// �v���C���[�R�}���h�I�����J�[�\��.
	Battle_item_magic_cursor 	= 0;	// �A�C�e���A�����I�����J�[�\��.
	Battle_party_member_cursor 	= 0;	// �p�[�e�B�����o�[�I���J�[�\��.
	Battle_monster_group_cursor = 0;	// �����X�^�[�O���[�v�I���J�[�\��.

	Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;

	// �搧�p�[�e�B�̌���.
	Battle_first_attack_party = BATTLE_FIRST_ATTACK_NONE;

	// �����X�^�[�̏�ԏ�����.
	for(ii=0;ii<4;ii++) {
		for(jj=0;jj<9;jj++) {
			Battle_monster_status[ii][jj] = 0xFF;
		}
	}

	// �����X�^�[������������.
	for(ii=0;ii<4;ii++) {
		Battle_monster_alives_in_group[ii] = 0;
	}

	// �����X�^�[���I����.
	Monster_clearParty(Battle_monster_party);
	Monster_lotMonster(g, Battle_monster_party, Battle_monster_group_count, floor);

	// �p�[�e�B�����o�[�X�e�[�^�X������.
	for(ii=0;ii<6;ii++) {
		Battle_party_status[ii] = STATUS_OK;
	}
	
	// �v���C���[����HP������.
	for(ii=0;ii<PARTY.member_count;ii++) {
		Battle_member_hp[ii] 	 = PARTY.party_member[ii]->hp_max;
		Battle_member_hp_max[ii] = PARTY.party_member[ii]->hp_max;
		Battle_party_status[ii]  = PARTY.party_member[ii]->status;
		Battle_member_lv[ii]	 = PARTY.party_member[ii]->lv;
	}


	// �퓬�J�n���̂ݏ��������K�v�ȏ���.
	Battle_set_party_save_melee_attack_attr();	//�@PT�L�����̃^�C�v�ʑŌ��h��t���O����.
	Battle_set_party_hit_rates();				// PT�L�����̖����͌���.
	Battle_set_party_critical_flag();			// PT�L�����̃N���e�B�J���t���O.
	Battle_set_party_healing_value();			// PT�L�����̃q�[�����O�l.
	Battle_set_party_attack_count();			// PT�L�����̍U����.


	Battle_set_player_index(Battle_input_player_index);		//�R�}���h�I���v���C���[�w��.
	Battle_turn_initialize();								//�^�[��������.

}

/************************************************************************************************
 * �G�O���[�v�ɃA���f�b�h�����X�^�[���܂ނ��ǂ���.
 ************************************************************************************************/
BOOL Battle_is_contain_undead_enemy() {
	int ii;
	for(ii=0;ii<4;ii++) {
		MonsterData *monster = &MONSTER_MST[Battle_monster_id_in_group[ii]];
		if(monster->monster_type == MONSTER_TYPE_UNDEAD) {
			return TRUE;
		}
	}

	return FALSE;
}

/************************************************************************************************
 * ���͂��󂯕t����v���C���[�C���f�b�N�X���X�V����.
 ************************************************************************************************/
void Battle_set_player_index(int index) {

	/********************************************************************************************
	 * �v���C���[�̓��͂����ׂčς񂾂�A�s���������肵�A�����X�^�[�̍s��������.
	 ********************************************************************************************/
	if(index > PARTY.member_count-1) {
		Battle_input_player_index = PARTY.member_count-1;
		// �s������ݒ�.
		Battle_set_action_order();
		// �퓬�^�[����i�߂�.
		Battle_tick_turn();
		return;
	}

	Battle_input_player_index = index;
	Battle_command_cursor = 0;
	Battle_party_member_cursor = 0;
	Battle_monster_group_cursor = 0;
	Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
	Battle_set_command_list();
}

/************************************************************************************************
 * �v���C���[�O���[�v�̃J�[�\���ړ�.
 ************************************************************************************************/
void Battle_move_player_party_cursor(int direction) {

	if(direction == BATTLE_CURSOR_NEXT) {
		// �O���[�v�̍ő吔�𒴂���ꍇ�͉������Ȃ�.
		if(Battle_party_member_cursor+1 > PARTY.member_count-1) {
			return;
		}
		Battle_party_member_cursor++;
	}else{
		if(Battle_party_member_cursor-1 < 0) {
			Battle_party_member_cursor = 0;
		}else{
			Battle_party_member_cursor--;
		}
	}
}

/************************************************************************************************
 * �����X�^�[�O���[�v�̃J�[�\���ړ�.
 ************************************************************************************************/
void Battle_move_monster_group_cursor(int direction) {
	int ii;

	if(direction == BATTLE_CURSOR_NEXT) {
		
		// �O���[�v�̍ő吔�𒴂���ꍇ�͉������Ȃ�.
		if(Battle_monster_group_cursor+1 > 4) {
			return;
		}

		for(ii=Battle_monster_group_cursor+1;ii<4;ii++) {
			if(Battle_monster_alives_in_group[ii] > 0) {
				Battle_monster_group_cursor = ii;
				break;
			}
		}
	}else{
		if(Battle_monster_group_cursor-1 < 0) {
			Battle_monster_group_cursor = 0;
		}else{
			Battle_monster_group_cursor--;
		}
	}
}


/************************************************************************************************
 * �R�}���h�̃J�[�\���ړ�.
 ************************************************************************************************/
void Battle_move_command_cursor(int direction) {
	if(direction == BATTLE_CURSOR_NEXT) {
		Battle_command_cursor++;
		if(Battle_command_cursor > Battle_command_length-1) {
			Battle_command_cursor = Battle_command_length-1;
		}
	}else{
		if(Battle_command_cursor-1 < 0) {
			Battle_command_cursor = 0;
		}else{
			Battle_command_cursor--;
		}
	}
}

/************************************************************************************************
 * �A�C�e���̃J�[�\���ړ�.
 ************************************************************************************************/
void Battle_move_item_cursor(int direction) {
	if(direction == BATTLE_CURSOR_NEXT) {
		unsigned char unequiped_count = Chara_count_unequiped_item(PARTY.party_member[Battle_input_player_index]);
		if(Battle_item_magic_cursor+1 > unequiped_count - 1) {
			return;
		}
		Battle_item_magic_cursor++;
	}else{
		if(Battle_item_magic_cursor-1 < 0) {
			Battle_item_magic_cursor = 0;
		}else{
			Battle_item_magic_cursor--;
		}
	}
}

/****************
 * �R�}���h�I�������쐬����.
 ****************/
void Battle_set_command_list() {
	CharaData *chara = PARTY.party_member[Battle_input_player_index];
	Battle_command_length = 0;

	// �O�q,��q�̊�{�R�}���h.
	if(Battle_input_player_index < 3) {
		Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_FIGHT;
	}else{
		Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_PARRY;
	}

	// ����,�A�C�e���g�p�A���S.
	Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_USEITEM;
	Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_RUN;

	// ���@�n�E��.
	if(chara->job == JOB_PRI || chara->job == JOB_MAG || chara->job == JOB_SAM || chara->job == JOB_BIS) {
		Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_SPELL;
	}

	// �A���f�b�h������Ƃ��̂ݑm����DISPELL�\
	if(Battle_is_contain_undead_enemy() &&  (chara->job == JOB_PRI || chara->job == JOB_BIS)) {
		Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_DISPELL;
	}

	// �O�q�̂ݖh��R�}���h�ǉ�.
	if(Battle_input_player_index < 3) {
		Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_PARRY;
	}

	// �I����蒼��.
	Battle_command_list[Battle_command_length++] = BATTLE_COMMAND_TAKEBACK;

}

/**************************************************************
 * �v���C���[�̎g�p����A�C�e������.
 **************************************************************/
void Battle_decide_player_use_item() {

	// �g�p����A�C�e��ID������.
	Battle_player_use_item_id[Battle_input_player_index] = Battle_player_possible_item_ids[Battle_item_magic_cursor];

	// �g�p�Ώۂ̑I����.
	Battle_mode = BATTLE_MODE_PLAYER_PARTY_MEMBER_SELECT;
	// ���̐l��.
	// Battle_set_player_index(++Battle_input_player_index);	
}



/**************************************************************
 * �v���C���[�̍s���I��������.
 **************************************************************/
void Battle_decide_player_command() {
	int ii;

	//�I�����ꂽ�R�}���h�ɂ���ď�������.
	switch(Battle_command_list[Battle_command_cursor]) {

		case BATTLE_COMMAND_PARRY:
		{
			Battle_action_id[Battle_input_player_index] = BATTLE_COMMAND_PARRY;
			Battle_set_player_index(++Battle_input_player_index);
		}
		break;


		case BATTLE_COMMAND_FIGHT:
		{
			int cnt = 0;

			// �Y���v���C���[�̍s��ID��FIGHT�ɐݒ�.
			Battle_action_id[Battle_input_player_index] = BATTLE_COMMAND_FIGHT;

			for(ii=0;ii<4;ii++) {
				if(Battle_monster_alives_in_group[ii] > 0) {
					cnt++;
				}
			}

			if(cnt == 1) {
				//���������X�^�[�O���[�v��1�����Ȃ��ꍇ�͎����I��.
				Battle_party_attack_group[Battle_input_player_index] = 0;
				Battle_set_player_index(++Battle_input_player_index);
			}else{
				//���������X�^�[�O���[�v����������ꍇ�͑ΏۑI�����[�h�ֈڍs.
				Battle_mode = BATTLE_MODE_PLAYER_MONSTER_GROUP_SELECT;
			}

		}
		break;


		case BATTLE_COMMAND_USEITEM:
		{
			int ii = 0;
			int itemCnt = 0;
			for(ii=0;ii<PARTY.party_member[Battle_input_player_index]->item_count;ii++) {
				ItemData *item = &ITEM_MST[PARTY.party_member[Battle_input_player_index]->item_ids[ii]];
				// �������A�C�e���͏��O.
				if((PARTY.party_member[Battle_input_player_index]->item_status[ii] & ITEM_STATUS_EQUIP) > 0) {
					continue;
				}

				Battle_player_possible_item_ids[itemCnt] = item->id;

				itemCnt++;
			}

			// �Y���v���C���[�̍s��ID��USEITEM�ɐݒ�.
			Battle_action_id[Battle_input_player_index] = BATTLE_COMMAND_USEITEM;
			Battle_mode = BATTLE_MODE_PLAYER_ITEM_SELECT;
		}
		break;


		case BATTLE_COMMAND_RUN:
		break;


		case BATTLE_COMMAND_DISPELL:
		break;


		case BATTLE_COMMAND_SPELL:
		break;


		case BATTLE_COMMAND_TAKEBACK:
		break;
	}
}


/****************
 * �v���C���[�̍s���I�����\��.
 ****************/
void Battle_display_player_commands() {
	CharaData *chara = PARTY.party_member[Battle_input_player_index];
	char *cursor[7] = {" ", " ", " ", " ", " ", " ", " "};
	int ii;

	pceFontSetType(2 + 128);
	drawWindow(2,20,34,8, 0);
	pceFontSetPos(4,22);
	pceFontPrintf("%s", chara->name);

	cursor[Battle_command_cursor] = ">";

	// �E�ƊԂŋ��ʂ̃R�}���h.	
	drawWindow(2,28,122,16, 0);
	pceFontSetPos(6, 30);
	pceFontPrintf("%s%s %s%s %s%s", cursor[0], Battle_command_names[Battle_command_list[0]],
									cursor[1], Battle_command_names[Battle_command_list[1]],
									cursor[2], Battle_command_names[Battle_command_list[2]]);

	// �E�ƊԂňقȂ�R�}���h.
	for(ii=3;ii<Battle_command_length;ii++) {
		pceFontSetPos(6+((ii-3)*28), 38);
		pceFontPrintf("%s%s", cursor[ii], Battle_command_names[Battle_command_list[ii]]);
	}
}

/****************
 * �G�p�[�e�B���\��.
 ****************/
void Battle_display_enemy_party() {
	int ii,jj;
	char cursor[] = " ";
	pceFontSetType(2 + 128);

	for(ii=0;ii<4;ii++) {
		for(jj=0;jj<9;jj++) {
			if(Battle_monster_party[ii] && Battle_monster_party[ii][jj]) {

				if(Battle_mode == BATTLE_MODE_PLAYER_MONSTER_GROUP_SELECT) {
					if(ii==Battle_monster_group_cursor) {
						strcpy(cursor, ">");
					}else{
						strcpy(cursor, " ");
					}
				}

				pceFontSetPos(40, 2 + ii*6);
				pceFontPrintf("%s(%d)%s", cursor, Battle_monster_group_count[ii], Battle_monster_party[ii][jj]->known_name);
				break;
			}
		}
	}
}


/**************************************************************
 * �o�g������.
 **************************************************************/
void Battle_update() {

	// Battle_mode�ɂ���ď����킯.
	switch(Battle_mode) {

		case BATTLE_MODE_PLAYER_TURN:
		case BATTLE_MODE_MONSTER_TURN:

			if(pcePadGet() & TRG_A) {
				Battle_message_index++;
				if(Battle_message_index > Battle_message_length) {
					Battle_tick_turn();
				}
			}

		break;

		case BATTLE_MODE_PLAYER_COMMAND_SELECT:
			if(pcePadGet() & TRG_A) {
				// Battle_set_player_index(++Battle_input_player_index);
				Battle_decide_player_command();
			}

			if(pcePadGet() & TRG_B) {
				Battle_initialize_encount(1);
			}

			if(pcePadGet() & TRG_DN || pcePadGet() & TRG_RI) {
				// Battle_command_cursor += 1;
				Battle_move_command_cursor(BATTLE_CURSOR_NEXT);
			}
			if(pcePadGet() & TRG_UP || pcePadGet() & TRG_LF) {
				// Battle_command_cursor -= 1;
				Battle_move_command_cursor(BATTLE_CURSOR_BACK);
			}
		break;

		case BATTLE_MODE_PLAYER_MAGIC_SELECT:
		break;

		case BATTLE_MODE_PLAYER_ITEM_SELECT:
			if(pcePadGet() & TRG_DN || pcePadGet() & TRG_RI) {
				Battle_move_item_cursor(BATTLE_CURSOR_NEXT);
			}
			if(pcePadGet() & TRG_UP || pcePadGet() & TRG_LF) {
				Battle_move_item_cursor(BATTLE_CURSOR_BACK);
			}
			if(pcePadGet() & TRG_B) {
				Battle_item_magic_cursor = 0;
				Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
			}

			// �g�p����A�C�e���̌���.
			if(pcePadGet() & TRG_A) {
				Battle_decide_player_use_item();
			}

		break;

		case BATTLE_MODE_PLAYER_PARTY_MEMBER_SELECT:

			if(pcePadGet() & TRG_UP || pcePadGet() & TRG_LF) {
				Battle_move_player_party_cursor(BATTLE_CURSOR_BACK);
			}

			if(pcePadGet() & TRG_DN || pcePadGet() & TRG_RI) {
				Battle_move_player_party_cursor(BATTLE_CURSOR_NEXT);
			}

			if(pcePadGet() & TRG_A) {
				Battle_player_item_magic_target[Battle_input_player_index] = Battle_party_member_cursor;
				Battle_set_player_index(++Battle_input_player_index);
			}

		break;

		case BATTLE_MODE_PLAYER_MONSTER_GROUP_SELECT:
			if(pcePadGet() & TRG_DN || pcePadGet() & TRG_RI) {
				Battle_move_monster_group_cursor(BATTLE_CURSOR_NEXT);
			}
			if(pcePadGet() & TRG_UP || pcePadGet() & TRG_LF) {
				Battle_move_monster_group_cursor(BATTLE_CURSOR_BACK);
			}
			if(pcePadGet() & TRG_B) {
				Battle_monster_group_cursor = 0;
				Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
			}
			if(pcePadGet() & TRG_A) {
				Battle_party_attack_group[Battle_input_player_index] = Battle_monster_group_cursor;
				Battle_monster_group_cursor = 0;
				Battle_set_player_index(++Battle_input_player_index);
				Battle_mode = BATTLE_MODE_PLAYER_COMMAND_SELECT;
			}

		break;
	}

}

/*******************
 * �o�g����ʕ\��.
 *******************/
void Battle_display() {
	Battle_display_enemy_party();

	if(Battle_mode != BATTLE_MODE_PLAYER_TURN && Battle_mode != BATTLE_MODE_MONSTER_TURN) {
		Battle_display_player_commands();
	}else{
		pceFontSetType(2 + 128);
		pceFontSetPos(12, 40);
		// pceFontPrintf("%s", &Battle_message_heap[0]);
		// strcpy(Battle_message_heap[0], "����������");
		drawWindow(0, 24, 127, 26, 0);
		drawBitmapFont(Battle_message_heap[Battle_message_index], 2, 26);
	}

	// Battle_mode�ɂ���ď����킯.
	switch(Battle_mode) {
		case BATTLE_MODE_PLAYER_COMMAND_SELECT:
		break;

		case BATTLE_MODE_PLAYER_MAGIC_SELECT:
		break;

		case BATTLE_MODE_PLAYER_ITEM_SELECT:
		{
			int ii;
			int itemLength = Chara_count_unequiped_item(PARTY.party_member[Battle_input_player_index]);

			char cursor[] = " ";
			drawWindow(12,2,100,80,0);
			pceFontSetType(2 + 128);

			for(ii=0;ii<itemLength;ii++) {
				ItemData *item = &ITEM_MST[Battle_player_possible_item_ids[ii]];

				if(ii==Battle_item_magic_cursor) {
					strcpy(cursor, ">");
				}else{
					strcpy(cursor, " ");
				}
				pceFontSetPos(20,8+ii*8);
				pceFontPrintf("%s%s",cursor, item->known_name);
			}
		}
		break;

		case BATTLE_MODE_PLAYER_PARTY_MEMBER_SELECT:
		{
			char cursor[] = ">";
			pceFontSetType(2 + 128);
			pceFontSetPos(4, 52 + 6 * Battle_party_member_cursor);
			pceFontPrintf("%s", cursor);

		}
		break;

		case BATTLE_MODE_PLAYER_MONSTER_GROUP_SELECT:
		break;	
	}
}

/********************************************
 * �s�����ݒ�.
 ********************************************/
void Battle_set_action_order() {
	int ii,jj;
	int rnd_value;
	CharaData *chara;

	/**********************************
	 * �p�[�e�B�����o�[�̍s��������.
	 **********************************/
	for(ii=0;ii<PARTY.member_count;ii++) {
		int agi_bonus = 0;
		chara = PARTY.party_member[ii];
		rnd_value = Util_random_int_range(0, 9);
		if(chara->agility >= 15) {
			agi_bonus = 14 - chara->agility;
		}else if(chara->agility >= 8) {
			agi_bonus = 0;
		}else if(chara->agility >= 6) {
			agi_bonus = 1;
		}else if(chara->agility >= 4) {
			agi_bonus = 2;
		}else{
			agi_bonus = 3;
		}
		rnd_value += agi_bonus;
		if(rnd_value < 0) {
			rnd_value = 0;
		}
		if(rnd_value > 9) {
			rnd_value = 9;
		}
		Battle_action_order[ii] = rnd_value;
	}


	/**********************************
	 * �����X�^�[�̍s��������
	 **********************************/
	for(ii=0;ii<4;ii++) {
		if(Battle_monster_alives_in_group[ii] > 0) {
			for(jj=0;jj<Battle_monster_alives_in_group[ii];jj++) {
				rnd_value = Util_random_int_range(2,9);
				Battle_action_order[(ii*9) + jj + 6] = rnd_value;
			}
		}
	}
}

/********************************************
 * �����X�^�[�̍s���ݒ�.
 ********************************************/
void Battle_exec_monster_turn() {

	int target_player_index, ii;
	int active_group = (Battle_current_turn_chara_index - 6) / 9;
	int active_index = (Battle_current_turn_chara_index - 6) - (active_group * 9);
	int damage_val = 0, hit_count = 0;
	char damage_text[5];
	char hit_count_text[5];

	MonsterData *active_monster = Battle_monster_party[active_group][active_index];
debug_val1 = active_group;
debug_val2 = active_index;

	// �U���Ώۂ�����.
	target_player_index = -1;
	while(target_player_index == -1) {
		int tmp = Util_random_int_range(0, PARTY.member_count);
		if(PARTY.party_member[tmp]->status == STATUS_OK) {
			target_player_index = tmp;
		}
	}

	Battle_action_id[Battle_current_turn_chara_index] = BATTLE_COMMAND_FIGHT;






	switch(Battle_action_id[Battle_current_turn_chara_index]) {
		case BATTLE_COMMAND_FIGHT:
			strcat(Battle_message_heap[0], active_monster->known_name);
			strcat(Battle_message_heap[0], " �� ");
			strcat(Battle_message_heap[0], PARTY.party_member[target_player_index]->name);
			strcat(Battle_message_heap[0], "���Ђ�������");
		{
			int a = 19 + 0 - PARTY.party_member[target_player_index]->ac - Battle_member_lv[Battle_current_turn_chara_index];
			int b = a - active_monster->ac;
			int dice_index = 0;
			int hit_decition_value = 0;
			int hit_rate = 0;
			debug_val1 = a;
			debug_val2 = b;
			if(b >= 19) {
				hit_decition_value = 19;
			}else if(b >= 0) {
				hit_decition_value = b;
			}else if(b >= -36) {
				hit_decition_value = 0;
			}else{
				if(a < 0) {
					hit_decition_value = 0;
				}else{
					hit_decition_value = 19;
				}
			}
			hit_rate = 255 * ((19 - hit_decition_value)/20.0);

			for(ii=0;ii<active_monster->attack_count;ii++) {
				if(Util_random_int_range(0, 255) < hit_rate) {
					damage_val += Dice_lot(&active_monster->damage_dice[dice_index]);
					dice_index++;
					hit_count++;
				}
			}
			
			if(hit_count > 0) {
				sprintf(damage_text,    "%d", damage_val);
				sprintf(hit_count_text, "%d", hit_count);
				strcat(Battle_message_heap[1], hit_count_text);
				strcat(Battle_message_heap[1], "���� ������");
				strcat(Battle_message_heap[1], PARTY.party_member[target_player_index]->name);
				strcat(Battle_message_heap[1], " �� ");
				strcat(Battle_message_heap[1], damage_text);
				strcat(Battle_message_heap[1], "�̃_���[�W");				
			}else{
				strcat(Battle_message_heap[1], PARTY.party_member[target_player_index]->name);
				strcat(Battle_message_heap[1], "�� ���킵��");
			}
			Battle_message_length++;
		}
		break;
	}

	Battle_action_id[Battle_current_turn_chara_index] |= BATTLE_COMMAND_DONE;
}


/*******************************************
 * �v���C���[�^�[������.
 *******************************************/
void Battle_exec_player_turn() {

	// �v���C���[�̍s���ɂ���ď�������.
	strcat(Battle_message_heap[0], PARTY.party_member[Battle_current_turn_chara_index]->name);
	switch(Battle_action_id[Battle_current_turn_chara_index]) {
		case BATTLE_COMMAND_FIGHT:
		{
			int ii;
			int target_group = Battle_party_attack_group[Battle_current_turn_chara_index];
			MonsterData *target_monster = 0;
			int hit_decition_value, hit_rate, hit_count, str_bonus, damage_val;
			ItemData *equiped_weapon;
			DiceExpr damage_dice;
			char damage_text[5];
			char hit_count_text[5];

			// �U���Ώۂ̃O���[�v�̐�������0�Ȃ�X�L�b�v����.
			if(Battle_monster_alives_in_group[target_group] == 0) {
				Battle_action_id[Battle_current_turn_chara_index] |= BATTLE_COMMAND_DONE;
				Battle_tick_turn();
				break;
			}

			// �U���Ώۂ̃O���[�v�ŁA�������Ă���擪�ɂ�����̂��Ώ�.
			for(ii=0;ii<9;ii++) {
				if(Battle_monster_status[target_group][ii] != 0xFF && 
				   Battle_monster_status[target_group][ii] != STATUS_DEAD) {
					target_monster = Battle_monster_party[target_group][ii];
					break;
				}
			}

			strcat(Battle_message_heap[0], " �� ");
			strcat(Battle_message_heap[0], target_monster->known_name);
			strcat(Battle_message_heap[0], "�� �Ȃ��肩������");

			hit_decition_value = 19 + target_group - target_monster->ac - Battle_party_hit_rates[Battle_current_turn_chara_index];
			if(hit_decition_value < 0) {
				hit_decition_value = 0;
			}
			if(hit_decition_value > 19) {
				hit_decition_value = 19;
			}

			equiped_weapon = Chara_get_equiped_weapon(PARTY.party_member[Battle_current_turn_chara_index]);
			if(PARTY.party_member[Battle_current_turn_chara_index]->str >= 16) {
				str_bonus = PARTY.party_member[Battle_current_turn_chara_index]->str - 15;
			}else{
				str_bonus = 0;
			}

			if(equiped_weapon) {
				damage_dice.amount = equiped_weapon->damage_dice.amount;
				damage_dice.surface_amount = equiped_weapon->damage_dice.surface_amount;
				damage_dice.add_val = equiped_weapon->damage_dice.add_val + str_bonus;

			}else{
				damage_dice.amount = 2;
				damage_dice.surface_amount = 2;
				damage_dice.add_val = str_bonus;
			}

			damage_val = 0;
			hit_count = 0;
			for(ii=0;ii<Battle_party_attack_count[Battle_current_turn_chara_index];ii++) {
				hit_rate = 255 * ((19 - hit_decition_value)/20.0);

				if(Util_random_int_range(0, 255) < hit_rate) {
					damage_val += Dice_lot(&damage_dice);
					hit_count++;
				}
			}

			if(hit_count > 0) {
				sprintf(damage_text,    "%d", damage_val);
				sprintf(hit_count_text, "%d", hit_count);

				strcat(Battle_message_heap[1], hit_count_text);
				strcat(Battle_message_heap[1], "���� ������");
				strcat(Battle_message_heap[1], target_monster->known_name);
				strcat(Battle_message_heap[1], " �� ");				
				strcat(Battle_message_heap[1], damage_text);
				strcat(Battle_message_heap[1], "�̃_���[�W");				
			}else{
				strcat(Battle_message_heap[1], target_monster->known_name);
				strcat(Battle_message_heap[1], "�� ���킵��");
			}

			Battle_message_length++;

			// �s���I���t���O.
			Battle_action_id[Battle_current_turn_chara_index] |= BATTLE_COMMAND_DONE;


		}
		break;

		case BATTLE_COMMAND_USEITEM:
		break;

		case BATTLE_COMMAND_DISPELL:
		break;

		case BATTLE_COMMAND_SPELL:
		break;

		case BATTLE_COMMAND_PARRY:
			Battle_action_id[Battle_current_turn_chara_index] |= BATTLE_COMMAND_DONE;
			Battle_tick_turn();
		break;
	}
	// strcat(Battle_message_heap[0], " �� ����������������������������������������������������������������");

}


void Battle_tick_turn() {
	int turn_chara_index;
	int ii,jj;

	for(ii=0;ii<MESSAGE_ROW;ii++) {
		for(jj=0;jj<MESSAGE_COL;jj++) {
			Battle_message_heap[ii][jj] = 0;
		}
	}

	// ���b�Z�[�W������.
	Battle_message_length = 0;
	Battle_message_index = 0;

	// �^�[���s���Ώۂ̃L�����N�^�[Index�����肷��.
	turn_chara_index = Battle_get_next_turn_chara();

	// 0xFF���A���Ă�����S���s���I��.
	if(turn_chara_index == 0xFF) {
		Battle_turn_initialize();
		return;
	}

	if(turn_chara_index < 6) {
		// index < 6 �Ȃ�p�[�e�B�̍s��.
		Battle_mode = BATTLE_MODE_PLAYER_TURN;
		Battle_exec_player_turn();
	}else{
		// index >= 6 �Ȃ烂���X�^�[�̍s��.
		Battle_mode = BATTLE_MODE_MONSTER_TURN;
		Battle_exec_monster_turn();
	}
}


int Battle_get_next_turn_chara() {
	int ii,jj,index;
	for(ii=1;ii<=9;ii++) {
		for(jj=0;jj<42;jj++) {
			if(Battle_action_order[jj] == ii && ((Battle_action_id[jj] & BATTLE_COMMAND_DONE) == 0)) {
				Battle_current_turn_chara_index = jj;
				return jj;
			}
		}
	}

	return 0xFF;
}



