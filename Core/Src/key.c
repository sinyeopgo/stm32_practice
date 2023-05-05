/*
2023-04-27 STM32F103RBT6 sinyeop key source code
*/
#include "key.h"
#include "led.h"
#include "platform_config.h"

void key_init(){
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC->APB2ENR |= RCC_APB2Periph_GPIOB;  //GPIOB use
  
  //GPIO_Port_Init(GPIO_KEY,KEY_0,GPIO_Input_Mode,GPIO_Mode_IN_FLOATING);
  //GPIO_Port_Init(GPIO_KEY,KEY_1,GPIO_Input_Mode,GPIO_Mode_IN_FLOATING);
  //GPIO_Port_Init(GPIO_KEY,KEY_2,GPIO_Input_Mode,GPIO_Mode_IN_FLOATING); -> 2번 스위치 고장
  //GPIO_Port_Init(GPIO_KEY,KEY_3,GPIO_Input_Mode,GPIO_Mode_IN_FLOATING);
  GPIO_InitStructure.GPIO_Pin = KEY_0 | KEY_1 | KEY_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //input Mode & 외부 pull up/pull down, 8번 9번 12번 13번 핀
}

uint8_t switch_on(uint16_t pinNum){
  if((GPIO_KEY->IDR & pinNum) != (uint32_t)Bit_RESET) return (uint8_t)Bit_SET;
  else return (uint8_t)Bit_RESET;
}

void Key_Test(){
  if(switch_on(KEY_0) == Bit_SET)       led0_on();
  else                                                 led0_off();
  if(switch_on(KEY_1) == Bit_SET)       led1_on();
  else                                                 led1_off();
  //if(switch_on(KEY_2) == Bit_SET)       led2_on();
  //else                                                  led2_off();
  if(switch_on(KEY_3) == Bit_SET)       led3_on();
  else                                                 led3_off();
}