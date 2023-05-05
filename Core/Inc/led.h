/*
2023-04-27 STM32F103RBT6 sinyeop led header
*/
#ifndef LED_H
#define LED_H
#include "platform_config.h"

#define GPIO_LED GPIOC

#define LED_0 GPIO_PIN_14
#define LED_1 GPIO_PIN_15
#define LED_2 GPIO_PIN_8
#define LED_3 GPIO_PIN_9

void LED_Test();
void led_init();
void led0_on();
void led1_on();
void led2_on();
void led3_on();
void led0_off();
void led1_off();
void led2_off();
void led3_off();
void led_all_on();
void led_all_off();
#endif