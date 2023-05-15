/*
2023-04-27 STM32F103RBT6 sinyeop system_config header
*/
#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H
#include "platform_config.h"

#define FLASH_R_BASE    (AHBPERIPH_BASE + 0x2000) //Flash registers base address
#define FLASH           ((FLASH_TypeDef *) FLASH_R_BASE)

#define RCC_CR_HSEON    ((uint32_t)0x00010000)  //External High Speed Clock enable
#define RCC_CR_HSERDY   ((uint32_t)0x00020000)  //External High SPeed Clock ready flag
#define HSEstartUp_TimeOut      ((uint16_t)0x0500)

#define FLASH_ACR_LATENCY_2     ((uint8_t)0x02)

#define RCC_CFGR_HPRE_DIV1      ((uint32_t)0x00000000)
#define RCC_CFGR_PPRE2_DIV1     ((uint32_t)0x00000000)
#define RCC_CFGR_PPRE1_DIV2     ((uint32_t)0x00000400)

#define RCC_CFGR_PLLSRC_HSE     ((uint32_t)0x00010000)
// HSE clock selected as PLL entry clock source
#define RCC_CFGR_PLLMULL6       ((uint32_t)0x00100000)  //PLL input clock*6
 
#define RCC_CR_PLLON            ((uint32_t)0x01000000)  //PLL enable
#define RCC_CR_PLLRDY           ((uint32_t)0x02000000)  //PLL clock ready flag
 
#define RCC_CFGR_SW_PLL         ((uint32_t)0x00000002)  //PLL selected as system clock
#define RCC_CFGR_SWS            ((uint32_t)0x0000000C)

/* CFGR Mask */
#define CFGR_SWS_Mask           ((uint32_t)0x0000000C)
#define CFGR_PLLMull_Mask       ((uint32_t)0x003C0000)
#define CFGR_PLLSRC_Mask        ((uint32_t)0x00010000)
#define CFGR_PLLXTPRE_Mask      ((uint32_t)0x00020000)
#define CFGR_PPRE1_Set_Mask     ((uint32_t)0x00000700)
#define CFGR_PPRE2_Set_Mask     ((uint32_t)0x00003800)
#define CFGR_ADCPRE_Set_Mask    ((uint32_t)0x00000C00)

//external cristal Hz
#define HSE_Value               ((uint32_t)12000000)
//internal cristal Hz
#define HSI_Value               ((uint32_t)8000000)

static __I uint8_t APBAHBPrescTable[16] = {0,0,0,0,1,2,3,4,1,2,3,4,6,7,8,9};
static __I uint8_t ADCPrescTable[4] = {2,4,6,8};

typedef struct
{
  _IO uint32_t ACR;
  _IO uint32_t KEYR;
  _IO uint32_t OPTKEYR;
  _IO uint32_t SR;
  _IO uint32_t CR;
  _IO uint32_t AR;
  _IO uint32_t RESERVED;
  _IO uint32_t OBR;
  _IO uint32_t WRPR;
#ifdef STM32F10X_XL
  uint32_t RESERVED1[8]; 
  _IO uint32_t KEYR2;
  uint32_t RESERVED2;   
  _IO uint32_t SR2;
  _IO uint32_t CR2;
  _IO uint32_t AR2; 
#endif /* STM32F10X_XL */  
} FLASH_TypeDef;

/*----------RCC_ClocksTypeDef-----------*/
//prescaler
typedef struct{
  uint32_t SYSCLK_Frequency;    /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;      /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t PCLK1_Frequency;     /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t PCLK2_Frequency;     /*!< returns PCLK2 clock frequency expressed in Hz */
  uint32_t ADCCLK_Frequency;    /*!< returns ADCCLK clock frequency expressed in Hz */
}RCC_ClocksTypeDef;

void System_Clock_Configuration();
void RCC_GetClocksFreq(RCC_ClocksTypeDef*);
void System_Information(void);
#endif