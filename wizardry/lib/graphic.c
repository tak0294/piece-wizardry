#include <stdlib.h>
#include <stdio.h>
#include "graphic.h"
DRAW_OBJECT D_OBJS;


void drawBitmap(PIECE_BMP *bmp, int dx, int dy, int sx, int sy, int w, int h)
{
	pceLCDSetObject(&D_OBJS, bmp, dx, dy, sx, sy, w, h, DRW_NOMAL);
	pceLCDDrawObject(D_OBJS);
}

void loadBitmap(unsigned char bmp[], PIECE_BMP *res)
{
	PBMP_FILEHEADER pbhead;
	memcpy(&pbhead, bmp, sizeof(PBMP_FILEHEADER));
	
	res->header = pbhead;
	res->buf    = bmp+sizeof(PBMP_FILEHEADER);
	res->mask   = bmp+sizeof(PBMP_FILEHEADER) + (res->header.h*res->header.w)/4;
}

void drawWindow(int x, int y, int w, int h, int fillColor) {
	pceLCDPaint(fillColor,x,y,w,h);
	pceLCDLine(3,x,y,x+w,y);
	pceLCDLine(3,x,y+h,x+w,y+h);
	pceLCDLine(3,x,y,x,y+h);
	pceLCDLine(3,x+w,y,x+w,y+h);
}