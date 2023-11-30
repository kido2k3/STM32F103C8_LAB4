/*
 * my_define.h
 *
 *  Created on: Nov 18, 2023
 *      Author: HP
 */

#ifndef INC_MY_DEFINE_H_
#define INC_MY_DEFINE_H_

#include "main.h"

#define FREQ_OF_TIM 100.0

#define PORT_TESTING_LED GPIOC
#define PIN_TESTING_LED GPIO_PIN_13

#define PORT_TESTING_LED1 GPIOB
#define PIN_TESTING_LED1 GPIO_PIN_0

#define PORT_TESTING_LED2 GPIOB
#define PIN_TESTING_LED2 GPIO_PIN_1

#define PORT_TESTING_LED3 GPIOB
#define PIN_TESTING_LED3 GPIO_PIN_2

#define PORT_TESTING_LED4 GPIOB
#define PIN_TESTING_LED4 GPIO_PIN_10

#define PORT_BUTTON1 GPIOA
#define PIN_BUTTON1 GPIO_PIN_6

#define PORT_BUTTON_LED GPIOA
#define PIN_BUTTON_LED GPIO_PIN_4

typedef uint8_t bool;
#endif /* INC_MY_DEFINE_H_ */
