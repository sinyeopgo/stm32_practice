/*
2023-04-27 STM32F103RBT6 sinyeop platform_config
*/
#include "platform_config.h"

void delay_int_count(volatile unsigned int nTime){
  for(;nTime>0;nTime--);
}

//void GPIO_Port_Init(GPIO_TypeDef *GPIO_Port,uint16_t pinNum, GPIOSpeed_TypeDef speedValE, uint32_t modeE){
//  uint32_t tmpVal = modeE << 2 | speedValE;
//  uint32_t pinpos = 0x00;
//  //pin 0~7
//  if((pinNum & 0xFF) != 0){
//    for(pinpos=0x00;pinpos<0x08;pinpos++){
//      if(pinNum == (uint32_t)0x01 << pinpos){
//        GPIO_Port->CRL &= ~(0xF << (pinpos*4));
//        GPIO_Port->CRL |= tmpVal << (pinpos*4);
//        break;
//      }
//    }
//  }
//  else{
//    pinNum >>=8;
//    for(pinpos=0x00;pinpos<0x08;pinpos++){
//      if(pinNum == (uint32_t)0x01 << pinpos){
//        GPIO_Port->CRH &= ~(0xF << (pinpos*4));
//        GPIO_Port->CRH |= tmpVal << (pinpos*4);
//        break;
//      }
//    }
//    
//  }
//}

void GPIO_Init(GPIO_TypeDef *GPIO_Port, GPIO_InitTypeDef *GPIO_InitStruct){
  uint32_t currentmode = 0x00,currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg=0x00, pinmask = 0x00;
  
  /********************GPIO Mode Configuration************************/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F);
  
  /*Output Mode*/
  if((((uint32_t)GPIO_InitStruct->GPIO_Mode)&((uint32_t)0x10)) != 0x00){
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed;
  }
  
  /*-------------------------GPIO CRL Configuration---------------------------*/
  if((((uint32_t)GPIO_InitStruct->GPIO_Pin) & ((uint32_t)0x00FF)) != 0x00){
    tmpreg = GPIO_Port->CRL;
    for(pinpos = 0x00; pinpos < 0x08;pinpos++){
      pos = ((uint32_t)0x01) << pinpos;
      currentpin = (GPIO_InitStruct->GPIO_Pin)&pos;
      if(currentpin == pos){
        pos = pinpos*4;
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        tmpreg |= (currentmode << pos);
        if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD){
          GPIO_Port->BRR = ((uint32_t)0x01) << pinpos;
        }
        else if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU){
          GPIO_Port->BSRR = ((uint32_t)0x01) << pinpos;
        }
      }
    }
    GPIO_Port->CRL = tmpreg;
  }
  else if(GPIO_InitStruct->GPIO_Pin > 0x00FF){
    tmpreg = GPIO_Port->CRH;
    for(pinpos = 0x00; pinpos < 0x08;pinpos++){
      pos = ((uint32_t)0x01) << (pinpos+0x08);
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
      if(currentpin == pos){
        pos = pinpos*4;
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        tmpreg |= (currentmode << pos);
        if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD){
          GPIO_Port->BRR = ((uint32_t)0x01) << (pinpos+0x08);
        }
        else if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU){
          GPIO_Port->BSRR = ((uint32_t)0x01) << (pinpos+0x08);
        }
      }
    }
    GPIO_Port->CRH = tmpreg;
  }
}
//void GPIO_configuration(){
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  //Usart Configuration
//  /*Configure USARTx_Tx as alternate function push-pull*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_9; //usart1_tx pin
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  
//  /*Configure USARTx_Rx as alternate function push-pull*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_10; //usart1_rx pin
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  
//  //Key Configuration
//  /*Configure gpio as input : Key0, 1*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8 | GPIO_PIN_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  
//  //LED Configuration
//  /*Configure gpio as input : LED0, 1, 2, 3*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_8 | GPIO_PIN_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//}