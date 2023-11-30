/*
 * my_system.c
 *
 *  Created on: Nov 18, 2023
 *      Author: HP
 */

#include "my_system.h"

void led_blinking(void)
{
	HAL_GPIO_TogglePin(PORT_TESTING_LED, PIN_TESTING_LED);
}

void led_blinking1(void)
{
	HAL_GPIO_TogglePin(PORT_TESTING_LED1, PIN_TESTING_LED1);
}

void led_blinking2(void)
{
	HAL_GPIO_TogglePin(PORT_TESTING_LED2, PIN_TESTING_LED2);
}
void led_blinking3(void)
{
	HAL_GPIO_TogglePin(PORT_TESTING_LED3, PIN_TESTING_LED3);
}
void led_blinking4(void)
{
	HAL_GPIO_TogglePin(PORT_TESTING_LED4, PIN_TESTING_LED4);
}
void init(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
	button_init();
	// add periodical tasks
	sch_add_task(led_blinking, 0, 1000);
	sch_add_task(button_read, 0, 10);
	sch_add_task(led_blinking1, 0, 1500);
	sch_add_task(led_blinking2, 0, 2000);
	sch_add_task(led_blinking3, 0, 2500);
	// add one shot task after 5s
	sch_add_task(led_blinking4, 5000, 0);
}

void loop(void)
{
	sch_dispatch();
	HAL_GPIO_WritePin(PORT_BUTTON_LED, PIN_BUTTON_LED, is_button_long_pressed(0));
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim2.Instance)
	{
		sch_update();
	}
}
