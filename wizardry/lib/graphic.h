#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "piece.h"

void drawBitmap(PIECE_BMP *bmp, int dx, int dy, int sx, int sy, int w, int h);
void loadBitmap(unsigned char bmp[], PIECE_BMP *res);
void drawWindow(int x, int y, int w, int h, int fillColor);

extern PIECE_BMP pINV1;

#endif
