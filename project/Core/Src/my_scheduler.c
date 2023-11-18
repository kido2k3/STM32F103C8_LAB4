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

bool sch_delete_task(uint16_t id);

bool sch_add_task(void (*pTask)(), uint16_t delay, uint16_t period) {
	uint16_t i = 0;
	while (i < NUMBER_OF_TASKS && task[i].pTask) {
		i++;
	}
	if (i == NUMBER_OF_TASKS)
		return 0;
	task[i].pTask = pTask;
	task[i].delay = delay * FREQ_OF_TIM / 1000.0;
	task[i].period = period * FREQ_OF_TIM / 1000.0;
	task[i].run = 0;
	return 1;
}
void sch_update(void) {
	for (uint16_t i = 0; i < NUMBER_OF_TASKS; i++) {
		if (task[i].pTask) {
			if (task[i].delay > 0) {
				task[i].delay--;
			} else {
				task[i].run++;
				if (task[i].period) {
					task[i].delay = task[i].period;
				}
			}
		}
	}
}

void sch_dispatch(void) {
	for (uint8_t i = 0; i < NUMBER_OF_TASKS; i++) {
		if (task[i].run && task[i].pTask) {
			(*task[i].pTask)();
			task[i].run--;
			if (task[i].period == 0) {
				sch_delete_task(i);
			}
		}

	}
}
bool sch_delete_task(uint16_t id) {
	if (id >= NUMBER_OF_TASKS)
		return 0;
	task[id].pTask = 0;
	return 1;
}
