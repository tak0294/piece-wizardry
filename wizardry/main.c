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
 * 変数.
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
 * 変数の初期化.
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
 * 初期化処理.
 **********************************************/
void pceAppInit(void)
{
	Util_initialize_rand();
	initialize_font();
	/************************************************
	 * 変数初期化.
	 ************************************************/
	initialize_variables();
	Battle_initialize();
	Battle_initialize_encount(1);							//エンカウント処理.

	game_mode = TITLE_MENU;
	
	pceLCDDispStop();
	pceLCDSetBuffer( vbuff );

	pceAppSetProcPeriod( 1000/30 );
	memset( vbuff, 0, 128*88 );
	
	pceLCDDispStart();
	pcePowerSetReport(PWR_RPTOFF);
}



/**********************************************
 * 毎フレーム更新処理.
 **********************************************/
void pceAppProc(int cnt)
{
	//画面初期化
	memset( vbuff, 0, 128*88 );
		
	/****************************
	 * ゲームモードで分岐.
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


