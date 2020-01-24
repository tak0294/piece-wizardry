#ifndef DICE_H
#define DICE_H

typedef struct DiceExpr_t {
	unsigned char amount;
	unsigned char surface_amount;
	unsigned char add_val;
}DiceExpr;

int Dice_lot(DiceExpr* dice);

#endif