#ifndef TASKSYS_H
#define TASKSYS_H

#define DEFRAG_SIZE 64

typedef struct Task_t
{
	char m_use;
	struct Task_t *next;
	struct Task_t *prev;
	int (*update)(struct Task_t*);
	void (*draw)(struct Task_t*);
	
	/*************
	 * ユーザー領域.
	 *************/
    char work[64];
    int frame;
} Task;

typedef struct TaskList_t
{
	int m_memory_size;
	char *m_active;
	char *m_free;
	char *g_buf;	//メモリ領域の先頭ポインタ.
	int g_size;		//タスクに割り当てているバイト数.
	int g_count;	//タスク数.
} TaskList;

extern char *m_active;	//最初に実行するタスクのポインタ.
extern char *m_free;	//未使用領域の先頭ポインタ.

extern TaskList* TaskSys_create_list();
extern void TaskSys_initialize_list(TaskList*, int);
extern Task* TaskSys_create_task(TaskList*);
extern void TaskSys_delete_task(TaskList*, Task*);
extern void TaskSys_update_task(TaskList*);
extern void TaskSys_draw_task(TaskList*);
extern void TaskSys_defrag(TaskList*);
#endif
