/*
2023-04-27 STM32F103RBT6 sinyeop system_config source code
*/
#include "system_config.h"
#include "platform_config.h"
#include "Usart.h"
#include "stdio.h"

static _IO uint32_t StartUpCounter = 0;

void System_Clock_Configuration(){
  _IO uint32_t HSEStatus;
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
  
  do{
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  }while((HSEStatus == 0) && (StartUpCounter != HSEstartUp_TimeOut));
  
  FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
  
  //HCLK = SYSCLK
  RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
  //PLCK2 = HCLK
  RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
  //PCLK1 = HCLK
  RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
  
  //PLL configuration: PLLCLK = HSE * 6 = 72MHz
  RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL6);
  
  //Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  
  //Wait till PLL is ready
  while((RCC->CR & RCC_CR_PLLRDY) == 0);
  
  //Select PLL as system clock source
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
  
  //Wait till PLL is used as system clock source
  while((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08);
}

void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks){
  uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;
  
  /* Get SYSCLK source ----------------------- */
  tmp = RCC->CFGR & CFGR_SWS_Mask;
  
  switch(tmp){
  case 0x00:    /* HSI used as system clock */
    RCC_Clocks->SYSCLK_Frequency = HSI_Value;
    break;
  case 0x04:    /* HSE used as system clck */
    RCC_Clocks->SYSCLK_Frequency = HSE_Value;
    break;
  case 0x08:    /* PLL used as system clock */
    /* Get PLL clock source and multiplication factor */
    pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
    pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;
    
    pllmull = (pllmull >> 18) + 2;
    
    if(pllsource == 0x00){
      /* HSI oscillator clock divided by 2 selected as PLL clock entry */
      RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
    }
    else{
      /* HSE selected as PLL clock entry */
      if((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (uint32_t)Bit_RESET){
        RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
      }
      else{
        RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
      }
    }
    break;
  default :
    RCC_Clocks->SYSCLK_Frequency = HSI_Value;
    break;
  }
  
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
  
  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}
 
void System_Information(){
  RCC_ClocksTypeDef rcc_clocks;
  
  printf("StartUpCounter : %d\n", StartUpCounter);
  
  RCC_GetClocksFreq(&rcc_clocks);
  printf("SYSCLK_Frequency = %d\n", rcc_clocks.SYSCLK_Frequency);
  printf("HCLK_Frequency = %d\n", rcc_clocks.HCLK_Frequency);
  printf("PCLK1_Frequency = %d\n", rcc_clocks.PCLK1_Frequency);
  printf("PCLK2_Frequency = %d\n", rcc_clocks.PCLK2_Frequency);
  printf("ADCCLK_Frequency = %d\n", rcc_clocks.ADCCLK_Frequency);
}
