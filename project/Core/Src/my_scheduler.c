/*
 * scheduler.c
 *
 *  Created on: Nov 18, 2023
 *      Author: HP
 */

#include "my_scheduler.h"

#define NUMBER_OF_TASKS	40
struct {
	void (*pTask)();
	uint16_t delay;
	uint16_t period;
	uint8_t run;
} task[NUMBER_OF_TASKS];

struct task
{
    void (*pTask)();
    uint16_t counter;
    uint16_t period;
    struct task *next_task;
};
struct
{
    struct task *top;
    struct task *bottom;
    uint32_t time_length;
} stack_task;
struct task *dispatcher;
bool sch_add_task(void (*pTask)(), uint16_t delay, uint16_t period)
{
    struct task *my_task = (struct task *)malloc(sizeof(struct task));
    my_task->pTask = pTask;
    my_task->counter = delay*FREQ_OF_TIM/1000.0;
    my_task->period = period;
    my_task->next_task = 0;
    if (stack_task.top == 0)
    {
        stack_task.top = my_task;
        stack_task.bottom = stack_task.top;
        stack_task.time_length = stack_task.top->counter;
        return 1;
    }
    if (delay >= stack_task.time_length)
    {
        my_task->counter = delay - stack_task.time_length;
        stack_task.bottom->next_task = my_task;
        stack_task.bottom = stack_task.bottom->next_task;
        stack_task.time_length += my_task->counter;
        return 1;
    }
    struct task *pre = stack_task.top;
    struct task *cur = stack_task.top;
    while (cur && my_task->counter >= cur->counter)
    {
        my_task->counter = my_task->counter - cur->counter;
        pre = cur;
        cur = cur->next_task;
    }
    if (pre != cur)
    {
        pre->next_task = my_task;
        my_task->next_task = cur;
    }
    else
    {
        my_task->next_task = cur;
        stack_task.top = my_task;
    }
    cur->counter -= my_task->counter;
    return 1;
}
void sch_update(void)
{
    if (dispatcher == 0)
        return;
    if (dispatcher->counter > 0)
    {
        dispatcher->counter--;
    }
}
void sch_delete_task(void)
{
    if (dispatcher == 0)
    {
        return;
    }
    struct task *del_task = dispatcher;
    dispatcher = 0;
    free(del_task);
}

bool sch_dispatch(void)
{
    if (dispatcher == 0)
    {
        if (stack_task.top == 0)
            return 0;
        stack_task.time_length -= stack_task.top->counter;
        dispatcher = stack_task.top;
        stack_task.top = stack_task.top->next_task;
        if (stack_task.top == 0)
            stack_task.bottom = 0;
        dispatcher->next_task = 0;
        return 1;
    }
    if (dispatcher->counter == 0)
    {
        (*dispatcher->pTask)();
        if (dispatcher->period != 0)
        {
            sch_add_task(dispatcher->pTask, dispatcher->period, dispatcher->period);
        }
        sch_delete_task();
        return 1;
    }
    return 0;
}
