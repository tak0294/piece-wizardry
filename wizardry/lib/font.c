#include "font.h"
#include "graphic.h"

static PIECE_BMP FONT_BMP;

/**************************************************
 * 0x8140‚©‚ç—^‚¦‚ç‚ê‚½•¶Žš‚Ü‚Å‚Ì‹——£‚ðŽæ“¾‚·‚é
 **************************************************/
int calcBitmapPosition(const char *str, int index)
{
    unsigned char c = str[index];
    int left,right;

    if ( (c>=0x81 && c<=0x9f) || (c>=0xe0 && c<=0xfc))
    {
        left = c<<8;
        c = str[index+1];

        if (c>=0x40 && c<=0xfc)
        {
            right = left | c;
            //printf("%d", right);

            if(right >= 0x8440)
                return (right - 0x8440) + 16*36;
            else if(right >= 0x8340)
            	if(right >= 0x837F)
	                return (right - 0x8340) + 16*24 - 3 - 5;
	            else
	            	return (right - 0x8340) + 16*24 - 3 - 4;
            else if(right >= 0x8240)
                if(right >= 0x8280)
                    return (right - 0x8240) + 16*12 - 4;
                else
                    return (right - 0x8240) + 16*12 - 3;
			else if(right >= 0x817F)
				return (right - 0x8140);
            else
                return (right - 0x8140)+1;

        }
    }

    return -1;
}


void initialize_font()
{
	loadBitmap(MISAKI_GOTHIC_TP_SLIM, &FONT_BMP);
}

int drawBitmapFont(const char *text, int x, int y)
{
    int sx,sy,distance,index,dx,indexAddedFlag;
	
	dx = x;
	
    index = 0;
    while(1)
    {
		indexAddedFlag = 0;
		
		//‰üs”»’è.
		if(text[index] == 0x24)
		{
			index += 1;
			dx = x;
			y += 8;
			continue;
		}

		//x‚Í‚Ý‚¾‚µ”»’è.
		if(dx + 8 > 128) {
			y += 8;
			dx = x;
			continue;
		}

		//ƒXƒy[ƒX”»’è.
		if(text[index] == 0x20) {
			index++;
			dx += 4;
			continue;
		}

		//”¼Šp”’l”»’è.
		if(text[index] >= 0x30 && text[index] <= 0x39)
		{
			distance = (94*2)+(16)+(text[index]-0x30);
			index += 1;
			indexAddedFlag = 1;
		}
		//”¼Šp‰pŽš”»’è.
		else if(text[index] >= 0x41 && text[index] <= 0x5A) {
			distance = 188 + 33 + (text[index]-0x41);
			index += 1;
			indexAddedFlag = 1;			
		}
		//”¼Šp‰pŽš”»’è(lower case).
		else if(text[index] >= 0x61 && text[index] <= 0x7A) {
			distance = 188 + 65 + (text[index]-0x61);
			index += 1;
			indexAddedFlag = 1;			
		}
		else
		{
			distance = calcBitmapPosition(text, index);
		}
        if(distance == -1)  break;

        sx = (distance%94-1)*8;
        sy = (int)distance/94*8;

        drawBitmap(&FONT_BMP, /*x+index*4*/dx, y, sx, sy,8,8);
		
		dx += 8;
		
		if(!indexAddedFlag)
			index += 2;
    }
	
	return y;
}
