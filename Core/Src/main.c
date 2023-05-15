/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "stdio.h"
#include "led.h"
#include "key.h"
#include "Usart.h"
#include "system_config.h"
#include "interrupt.h"

int main(void)
{
  RCC_ClocksTypeDef rcc_clocks;
  uint16_t ch;
  
  System_Clock_Configuration();
  led_init();
  key_init();
  USART1_init();
  NVIC_Configuration();
  EXTI_Configuration();
  printf("\033[H\033[J");
  printf("Hello Cortex-M3! with printf\n");
  RCC_GetClocksFreq(&rcc_clocks);
  if(SysTick_Config(rcc_clocks.SYSCLK_Frequency/1000)){
    printf("max clock exceeded");
    while(1);
  }

  while (1)
  {
    printf("\n----------------\n");
    printf("Press menu key\n");
    printf("----------------\n");
    printf("0> System Information\n");
    printf("----------------\n");
    printf("1> LED Test\n");
    printf("2> KEY Test\n");
    printf("3> 10 sec Delay Test\n");
    printf("----------------\n");
    printf("x> quit\n\n");
    
    ch = USART_GetCharater(USART1);
    printf(" is selected\n\n");
    
    if((char)ch == 'x') break;
    
    switch((char)ch){
    case '0':
      System_Information();
      break;
    case '1':
      LED_Test();
      break;
    case '2':
      for(int i=0;i<500;i++){
        Key_Test();
        delay_10_milli_second();
      }
      break;
    case '3':
      DELAY_Test();
      break;
    }
  }
}
