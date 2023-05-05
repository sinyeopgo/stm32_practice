/*
2023-04-27 STM32F103RBT6 sinyeop key header
*/
#ifndef KEY_H
#define KEY_H
#include "platform_config.h"

#define GPIO_KEY GPIOB

#define KEY_0 GPIO_PIN_8
#define KEY_1 GPIO_PIN_9
#define KEY_2 GPIO_PIN_12
#define KEY_3 GPIO_PIN_13

void key_init();
uint8_t switch_on(uint16_t pinNum);
void Key_Test();
#endif