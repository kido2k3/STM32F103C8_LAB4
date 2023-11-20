/*
 * my_system.c
 *
 *  Created on: Nov 18, 2023
 *      Author: HP
 */

#include "my_system.h"

void led_blinking(void){
	HAL_GPIO_TogglePin(PORT_TESTING_LED, PIN_TESTING_LED);
}

void led_blinking2(void){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}
void init(void){
	HAL_TIM_Base_Start_IT(&htim2);
	sch_add_task(led_blinking, 0, 3000);
	sch_add_task(led_blinking2, 0, 5000);
}

void loop(void){
	sch_dispatch();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == htim2.Instance){
		sch_update();
	}
}
