#include <stdlib.h>
#include "piece.h"
#include "util.h"

void Util_initialize_rand() {
	PCETIME	ptime;
	int random_v;
	pceTimeGet(&ptime);
	random_v = ptime.s100 * 1000;
    srand(random_v);
}

int Util_random_int_range(int min, int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int Util_Max(int num1, int num2)
{
	if(num1 > num2)
		return num1;
	else
		return num2;
}

int Util_Min(int num1, int num2)
{
	if(num1 < num2)
		return num1;
	else
		return num2;
}

int Util_is_any_trigger(int pad_status)
{
	
	if(pad_status & TRG_RI ||
	   pad_status & TRG_LF ||
	   pad_status & TRG_DN ||
	   pad_status & TRG_UP ||
	   pad_status & TRG_B ||
	   pad_status & TRG_A ||
	   pad_status & TRG_D ||
	   pad_status & TRG_C)
	{
		return 1;
	}
	
	return 0;
	   
}

int Util_dice(int count, int max)
{
	int res = 0;
	int ii;
	for(ii=0;ii<count;ii++)
	{
		res += Util_random_int_range(1, max);
	}
	
	return res;
}

void Util_random_direction(Point *p)
{
	int moveX = 0;
	int moveY = 0;
	int rand = Util_random_int_range(1,4);
	if(rand == 1)
	{
		moveY = -1;
	}
	else if(rand == 2)
	{
		moveX = 1;
	}
	else if(rand == 3)
	{
		moveY = 1;
	}
	else
	{
		moveX = -1;
	}
	
	p->x = moveX;
	p->y = moveY;
}

void Util_distance(Point *result, int x1, int y1, int x2, int y2)
{
	//return new Point((char2.m_mapX - char1.m_mapX), (char2.m_mapY - char1.m_mapY));
	result->x = (x2-x1);
	result->y = (y2-y1);
}

void Util_distance_to_direction(Point *distance)
{
	if(distance->x > 0)	distance->x = 1;
	if(distance->x < 0) distance->x = -1;
	if(distance->y > 0)	distance->y = 1;
	if(distance->y < 0) distance->y = -1;
}