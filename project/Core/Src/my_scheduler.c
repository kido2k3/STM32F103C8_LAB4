/*
 * scheduler.c
 *
 *  Created on: Nov 18, 2023
 *      Author: HP
 */

#include "my_scheduler.h"

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
    // struct task *bottom;
    // uint32_t time_length;
} stack_task;
// struct task *dispatcher;
bool sch_add_task(void (*pTask)(), uint16_t delay, uint16_t period)
{
    struct task *my_task = (struct task *)malloc(sizeof(struct task));
    my_task->pTask = pTask;
    my_task->counter = delay *FREQ_OF_TIM/1000;
    my_task->period = period;
    my_task->next_task = 0;
    if (stack_task.top == 0)
    {
        stack_task.top = my_task;
        // stack_task.bottom = stack_task.top;
        // stack_task.time_length = stack_task.top->counter;
        return 1;
    }
    // if (delay >= stack_task.time_length)
    // {
    //     my_task->counter = delay - stack_task.time_length;
    //     stack_task.bottom->next_task = my_task;
    //     stack_task.bottom = stack_task.bottom->next_task;
    //     stack_task.time_length += my_task->counter;
    //     return 1;
    // }
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
    if (cur)
        cur->counter -= my_task->counter;
    return 1;
}
void sch_update(void)
{
    if (stack_task.top == 0)
        return;
    if (stack_task.top->counter > 0)
    {
        stack_task.top->counter--;
    }
}
void sch_delete_task(struct task *del_task)
{
    if (del_task == 0)
    {
        return;
    }
    free(del_task);
}

bool sch_dispatch(void)
{
    if (stack_task.top == 0)
        return 0;
    if (stack_task.top->counter == 0)
    {
        (*stack_task.top->pTask)();
        struct task *temp = stack_task.top;
        stack_task.top = stack_task.top->next_task;
        temp->next_task = 0;
        if (temp->period != 0)
        {
            sch_add_task(temp->pTask, temp->period, temp->period);
        }
        sch_delete_task(temp);
        return 1;
    }
    return 0;
}
