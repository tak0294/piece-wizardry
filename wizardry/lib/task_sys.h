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
	 * ���[�U�[�̈�.
	 *************/
    char work[64];
    int frame;
} Task;

typedef struct TaskList_t
{
	int m_memory_size;
	char *m_active;
	char *m_free;
	char *g_buf;	//�������̈�̐擪�|�C���^.
	int g_size;		//�^�X�N�Ɋ��蓖�ĂĂ���o�C�g��.
	int g_count;	//�^�X�N��.
} TaskList;

extern char *m_active;	//�ŏ��Ɏ��s����^�X�N�̃|�C���^.
extern char *m_free;	//���g�p�̈�̐擪�|�C���^.

extern TaskList* TaskSys_create_list();
extern void TaskSys_initialize_list(TaskList*, int);
extern Task* TaskSys_create_task(TaskList*);
extern void TaskSys_delete_task(TaskList*, Task*);
extern void TaskSys_update_task(TaskList*);
extern void TaskSys_draw_task(TaskList*);
extern void TaskSys_defrag(TaskList*);
#endif
