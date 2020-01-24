#ifndef MALLOC_MGR_H
#define MALLOC_MGR_H

#define MAX_PTR 1000
extern int pnum;
extern void* MallogMgr_ptr_arr[MAX_PTR];

void* malloc_ex(size_t s);
void free_ex(void* p);
void display_free_heap();

#endif