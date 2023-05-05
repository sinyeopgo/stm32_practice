/*
2023-04-27 STM32F103RBT6 sinyeop led source code
*/
#include "led.h"
#include "platform_config.h"

void led_init(){
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC->APB2ENR |= RCC_APB2Periph_GPIOC;  //GPIOC use
  
//  GPIO_Port_Init(GPIO_LED,LED_0,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
//  GPIO_Port_Init(GPIO_LED,LED_1,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
//  GPIO_Port_Init(GPIO_LED,LED_2,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
//  GPIO_Port_Init(GPIO_LED,LED_3,GPIO_Speed_10MHz,GPIO_Mode_Out_PP);
  GPIO_InitStructure.GPIO_Pin = LED_0 | LED_1 | LED_2 | LED_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  //output Mode & General purpose ouput push_pull, Max Speed 10MHz, 8¹ø 9¹ø 14¹ø 15¹ø ÇÉ
}
void LED_Test(){
  led_all_on();
  delay_int_count(725690);
  led_all_off();
  delay_int_count(725690);
}
void led0_on(){
  GPIO_LED->BSRR |= LED_0;
}

void led1_on(){
  GPIO_LED->BSRR |= LED_1;
}

void led2_on(){
  GPIO_LED->BSRR |= LED_2;
}

void led3_on(){
  GPIO_LED->BSRR |= LED_3;
}

void led0_off(){
  GPIO_LED->BRR |= LED_0;
}

void led1_off(){
  GPIO_LED->BRR |= LED_1;
}

void led2_off(){
  GPIO_LED->BRR |= LED_2;
}

void led3_off(){
  GPIO_LED->BRR |= LED_3;
}
void led_all_on(){
  GPIO_LED->BSRR |= LED_0 | LED_1 | LED_2 | LED_3;
}
void led_all_off(){
  GPIO_LED->BRR |= LED_0 | LED_1 | LED_2 | LED_3;
}