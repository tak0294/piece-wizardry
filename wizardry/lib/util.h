#ifndef UTIL_H
#define UTIL_H

typedef struct Point_t
{
	int x,y;
} Point;

extern void Util_initialize_rand();
extern int Util_random_int_range(int min, int max);
extern int Util_Max(int num1, int num2);
extern int Util_Min(int num1, int num2);
extern int Util_is_any_trigger(int pad_status);
extern int Util_dice(int count, int max);
extern void Util_random_direction(Point *p);
extern void Util_distance(Point *result, int x1, int y1, int x2, int y2);
extern void Util_distance_to_direction(Point *distance);

#endif