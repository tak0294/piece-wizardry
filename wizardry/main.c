#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <piece.h>
#include "./lib/lib.h"

#include "chara_data.h"
#include "item.h"
#include "monster.h"
#include "battle_manager.h"
#include "party.h"


unsigned char vbuff[128*88];

/***************************
 * �ϐ�.
 ***************************/
int errno;
int frame;
int game_mode;

extern unsigned char TITLE[];
extern unsigned char MONS1[];
extern unsigned char BATTLE[];
PIECE_BMP pbTitle;
PIECE_BMP pbMonster;

enum GAMEMODE
{
	TITLE_MENU,
	READY,
	GAME,
	WAIT_CLEAR_ROW,
	GAMEOVER,
	EXPLOSION
};

/*********************************
 * �ϐ��̏�����.
 *********************************/
void initialize_variables()
{
	frame = 0;
	loadBitmap(TITLE, &pbTitle);
	loadBitmap(BATTLE, &pbMonster);

	Party_add(&TRAINING_GROUND[0]);
	Party_add(&TRAINING_GROUND[1]);
	Party_add(&TRAINING_GROUND[2]);
	Party_add(&TRAINING_GROUND[4]);
	Party_add(&TRAINING_GROUND[5]);
	Party_add(&TRAINING_GROUND[3]);

}


/**********************************************
 * ����������.
 **********************************************/
void pceAppInit(void)
{
	Util_initialize_rand();
	initialize_font();
	/************************************************
	 * �ϐ�������.
	 ************************************************/
	initialize_variables();
	Battle_initialize();
	Battle_initialize_encount(1);							//�G���J�E���g����.

	game_mode = TITLE_MENU;
	
	pceLCDDispStop();
	pceLCDSetBuffer( vbuff );

	pceAppSetProcPeriod( 1000/30 );
	memset( vbuff, 0, 128*88 );
	
	pceLCDDispStart();
	pcePowerSetReport(PWR_RPTOFF);
}



/**********************************************
 * ���t���[���X�V����.
 **********************************************/
void pceAppProc(int cnt)
{
	//��ʏ�����
	memset( vbuff, 0, 128*88 );
		
	/****************************
	 * �Q�[�����[�h�ŕ���.
	 ****************************/
	if(game_mode == TITLE_MENU)
	{
		

		if(pbMonster.buf) {
			drawBitmap(&pbMonster, 0, 0, 0, 0, 128, 88);
		}

		Battle_update();
		Party_display_member();
		Battle_display();
		Battle_debug_disp();

	}

	//pceFontSetPos(100, 80);
	//pceFontPrintf("%d", pceHeapGetMaxFreeSize());
	display_free_heap();
	pceLCDTrans();
	
	frame++;
}

void pceAppExit( void )
{
}


