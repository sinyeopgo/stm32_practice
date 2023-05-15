/*
2023-04-27 STM32F103RBT6 sinyeop platform_config
*/
#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H
#include <stdint.h>

//**********GPIO PIN NUMBER**********
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

//**********RCC APB2Periph**********
#define RCC_APB2Periph_AFIO     ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA     ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOB     ((uint32_t)0x00000008)
#define RCC_APB2Periph_GPIOC     ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD     ((uint32_t)0x00000020)
#define RCC_APB2Periph_GPIOE     ((uint32_t)0x00000040)
#define RCC_APB2Periph_GPIOF     ((uint32_t)0x00000080)
#define RCC_APB2Periph_GPIOG     ((uint32_t)0x00000100)
#define RCC_APB2Periph_ADC1     ((uint32_t)0x00000200)
#define RCC_APB2Periph_ADC2     ((uint32_t)0x00000400)
#define RCC_APB2Periph_TIM1     ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1     ((uint32_t)0x00001000)
#define RCC_APB2Periph_TIM8     ((uint32_t)0x00002000)
#define RCC_APB2Periph_USART1     ((uint32_t)0x00004000)
#define RCC_APB2Periph_ADC3     ((uint32_t)0x00008000)

/* HCLK_Frequency */
#define CFGR_HPRE_Set_Mask      ((uint32_t)0x000000F0)
#ifdef __cplusplus
#define  __I     volatile
#else
#define  __I     volatile const
#endif  //CFGR_HPRE_Set_Mask

//**********RCC_TypeDef**********
#define _IO     volatile
 
typedef struct{
  _IO uint32_t CR;
  _IO uint32_t CFGR;
  _IO uint32_t CIR;
  _IO uint32_t APB2RSTR;
  _IO uint32_t APB1RSTR;
  _IO uint32_t AHBENR;
  _IO uint32_t APB2ENR;
  _IO uint32_t APB1ENR;
  _IO uint32_t BDCR;
  _IO uint32_t CSR;
#ifdef STM32F10X_CL
  _IO uint32_t AHBRSTR;
  _IO uint32_t CFGR2;
#endif //STM32F10X_CL
}RCC_TypeDef;
 
//**********GPIO_Typedef**********
typedef struct{
  _IO uint32_t CRL;
  _IO uint32_t CRH;
  _IO uint32_t IDR;
  _IO uint32_t ODR;
  _IO uint32_t BSRR;
  _IO uint32_t BRR;
  _IO uint32_t LCKR;
}GPIO_TypeDef;
 
//**********Peripheral Memory**********
#define PERIPH_BASE     ((uint32_t)0x40000000)  //SRAM base address in the bit-band region
 
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x20000)
 
#define RCC_BASE        (AHBPERIPH_BASE + 0x1000)
 
#define RCC             ((RCC_TypeDef*) RCC_BASE)
 
#define GPIOA_BASE      (APB2PERIPH_BASE + 0x800)
#define GPIOB_BASE      (APB2PERIPH_BASE + 0xC00)
#define GPIOC_BASE      (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE      (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE      (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE      (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE      (APB2PERIPH_BASE + 0x2000)
 
#define GPIOA           ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB           ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC           ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD           ((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE           ((GPIO_TypeDef*)GPIOE_BASE)
#define GPIOF           ((GPIO_TypeDef*)GPIOF_BASE)
#define GPIOG           ((GPIO_TypeDef*)GPIOG_BASE)

//**********CNF**********
typedef enum{   //Speed, input/Output
  GPIO_Input_Mode = 0,
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;

//typedef enum{
//  GPIO_Mode_Out_PP = 0x00,
//  GPIO_Mode_Out_OD = 0x01,
//  GPIO_Mode_AF_PP = 0x10,
//  GPIO_Mode_AF_OD = 0x11
//}GPIOMode_Output_TypeDef;
// 
//typedef enum{
//  GPIO_Mode_AIN         = 0x00,
//  GPIO_Mode_IN_FLOATING = 0x01,
//  GPIO_Mode_IPDPU       = 0x10
//}GPIOMode_Input_TypeDef;

typedef enum{
  GPIO_Mode_AIN         = 0x00,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD         = 0x28,
  GPIO_Mode_IPU         = 0x48,
  GPIO_Mode_Out_PP      = 0x10,
  GPIO_Mode_Out_OD      = 0x14,
  GPIO_Mode_AF_PP       = 0x18,
  GPIO_Mode_AF_OD       = 0x1C
}GPIOMode_TypeDef;

typedef struct{
  uint16_t GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;

typedef enum{
  Bit_RESET = 0,
  Bit_SET
}BitAction;

void delay_int_count(volatile unsigned int nTime);
//void GPIO_Port_Init(GPIO_TypeDef *GPIO_Port,uint16_t pinNum, GPIOSpeed_TypeDef speedValE, uint32_t modeE);
void GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_InitTypeDef* GPIO_InitStruct);
//void GPIO_configuration();
#endif