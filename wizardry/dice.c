#include "dice.h"
#include "./lib/lib.h"

int Dice_lot(DiceExpr* dice)
{
	int res = 0;
	int ii;
	for(ii=0;ii<dice->amount;ii++)
	{
		res += Util_random_int_range(1, dice->surface_amount);
	}
	
	return res + dice->add_val;
}