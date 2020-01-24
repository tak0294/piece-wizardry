#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task_sys.h"
#include "malloc_mgr.h"
#include "piece.h"

/*************************************
 * ダミー関数.
 *************************************/
int dummy_update_task(Task* task)
{
    //printf("dummy update\n");
    return 0;
}

void dummy_draw_task(Task* task)
{
    //printf("dummy draw task.x=%d\n", task->x);
}




/*******************************************************
 * タスクリストの生成.
 *******************************************************/
TaskList* TaskSys_create_list()
{
    TaskList *list = malloc_ex(sizeof(TaskList));
    list->m_active = NULL;
    list->m_free   = NULL;

    return list;
}


/*******************************************************
 * タスクリストの初期化.
 *******************************************************/
void TaskSys_initialize_list(TaskList *list, int memory_size)
{
    list->g_buf = malloc_ex(memory_size);
    memset(list->g_buf, 0, memory_size);

    list->m_memory_size = memory_size;
    list->m_active = NULL;
    list->m_free   = list->g_buf;

    list->g_size  = 0;
    list->g_count = 0;
}


/*******************************************************
 * タスクの生成.
 *******************************************************/
Task* TaskSys_create_task(TaskList *list)
{
    Task *task,*next,*new_task;

    if(list->g_buf == NULL)	return NULL;	//タスクリスト未初期化.
    if(list->m_free+sizeof(Task) >= list->g_buf+list->m_memory_size)	return NULL;	//空き容量不足.

    list->g_size += sizeof(Task);
    list->g_count++;

    new_task = (Task*)(list->m_free);
    list->m_free += sizeof(Task);

    /***************
     * 初期設定.
     ***************/
    new_task->m_use = 1;
    new_task->update = dummy_update_task;
    new_task->draw   = dummy_draw_task;

    if(list->m_active == NULL)	//現在タスクリストが空.
    {
        list->m_active = (char*)new_task;

        new_task->prev = new_task;
        new_task->next = new_task;

        return new_task;
    }

    for(task = (Task*)(list->m_active);;task=next)
    {
        next = task->next;

        if(task == (Task*)(list->m_active))
        {
            list->m_active = (char*)new_task;

            new_task->prev = task->prev;
            new_task->next = task;
            break;
        }
    }


    new_task->prev->next = new_task;
    new_task->next->prev = new_task;

    return new_task;
}


/*******************************************************
 * タスク削除.
 *******************************************************/
void TaskSys_delete_task(TaskList* list, Task* task)
{
    if(task == NULL)	return;
    if(task->m_use == 0)	return;	//重複削除防止.
    task->m_use = 0;

    list->g_size -= sizeof(Task);
    list->g_count--;

    if(task == (Task*)(list->m_active))
    {
        if(task->next == (Task*)(list->m_active))
        {
            list->m_active = NULL;
            return;
        }
        else
        {
            list->m_active = (char*)(task->next);
        }
    }

    task->prev->next = task->next;
    task->next->prev = task->prev;
}

/*******************************************************
 * タスクのデフラグ.
 *******************************************************/
void TaskSys_defrag(TaskList* list)
{
    char* dest = list->g_buf;
    char* source;
    Task* task;
    int size;

    //使用中のタスクが無い場合はメモリを初期化し、
    //フリーメモリのポインタを先頭へ設定する.
    if(list->m_active == NULL)
    {
        list->m_free = list->g_buf;
        memset(list->g_buf, 0, list->m_memory_size);
        return;
    }

    //タスクが1つだけの場合は、先頭へ移動させて終了.
    task = (Task*)list->m_active;
    if(task->next == task)
    {
        size = sizeof(Task);
        memmove(list->g_buf, list->m_active, size);
        task = (Task*)list->g_buf;
        task->prev = task;
        task->next = task;

        list->m_active = list->g_buf;
        dest += sizeof(Task);
    }
    else
    {
        for(source=list->g_buf;source < list->m_free;source += sizeof(Task))
        {
            task = (Task*)source;
            size = sizeof(Task);
            if(task->m_use == 0) continue;

            memmove(dest, source, size);

            task = (Task*)dest;
            task->prev->next = task;
            task->next->prev = task;

            if(source == list->m_active)    list->m_active = dest;
            dest += size;
        }
    }

    memset(dest,0,list->m_free-dest);
    list->m_free = dest;
}


/*******************************************************
 * 全タスク更新.
 *******************************************************/
void TaskSys_update_task(TaskList* list)
{
    int res;
    Task *task, *next;
    for(task = (Task*)(list->m_active);list->m_active;task=next)
    {
        res = task->update(task);
        next = task->next;

        if(res != 0)
        {
            TaskSys_delete_task(list, task);
            if(next->next==(Task*)(list->m_active))	break;
        }
        else
            if(next==(Task*)(list->m_active))	break;
    }

    if(list->g_buf+list->m_memory_size-list->m_free < DEFRAG_SIZE)
    {
        TaskSys_defrag(list);
    }
}



/*******************************************************
 * 全タスク描画.
 *******************************************************/
void TaskSys_draw_task(TaskList* list)
{
    Task *task, *next;
    for(task = (Task*)(list->m_active);list->m_active;task=next)
    {
        task->draw(task);
        next = task->next;
        if(next==(Task*)(list->m_active))	break;
    }
}

