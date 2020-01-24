#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <piece.h>
#include "malloc_mgr.h"

int pnum = 0;
void* MallogMgr_ptr_arr[MAX_PTR] = { NULL };

void * malloc_ex(size_t s) {
	void * a;
	int i;
	if ( pnum >= MAX_PTR ) { /* 限界を超えていれば何もしない */
		return NULL;
	}
	a = pceHeapAlloc( s );
	if ( a != NULL ) {
		for ( i = 0; i < MAX_PTR; i ++ ) {
		if ( MallogMgr_ptr_arr[ i ] == NULL ) {
			MallogMgr_ptr_arr[ i ] = a;
			pnum ++;
			break;
			}
		}
	}
	return a;
}


void free_ex( void * p ) {
	int i;
	if ( pnum <= 0 ) {
		return;
	}

	for ( i = 0; i < MAX_PTR; i ++ ) {
	if ( MallogMgr_ptr_arr[ i ] == p ) {
		pceHeapFree( p );
		MallogMgr_ptr_arr[ i ] = NULL;
		pnum --;
		break;
		}
	}
}

void display_free_heap() {
	pceFontSetPos(0,0);
	pceFontPrintf("%d,%d", pnum, pceHeapGetMaxFreeSize());

}