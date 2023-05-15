/*
2023-04-27 STM32F103RBT6 sinyeop interrupt header
*/
#include "platform_config.h"
#include "stdio.h"
#include "Usart.h"

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
 
#define SCS_BASE        (0xE000E000)  //System Control Space Base Address

#define SysTick_BASE    (SCS_BASE +  0x0010)    // SysTick Base Address
#define NVIC_BASE       (SCS_BASE +  0x0100)    //NVIC Base Address
#define SCB_BASE        (SCS_BASE +  0x0D00)    //System Control Block Base Address

#define SysTick         ((SysTick_Type *) SysTick_BASE)   //SysTick configuration struct
#define NVIC            ((NVIC_Type *) NVIC_BASE)         //NVIC configuration struct
#define SCB             ((SCB_Type *) SCB_BASE)           //SCB configuration struct

#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
 
#define SYSTICK_ENABLE              0                                          /* Config-Bit to start or stop the SysTick Timer                         */
#define SYSTICK_TICKINT             1                                          /* Config-Bit to enable or disable the SysTick interrupt                 */
#define SYSTICK_CLKSOURCE           2                                          /* Clocksource has the offset 2 in SysTick Control and Status Register   */
#define SYSTICK_MAXCOUNT            ((1 << 24) - 1)                            /* SysTick MaxCount                                                      */
 
#define __NVIC_PRIO_BITS            4                                          /*!< STM32 uses 4 Bits for the Priority Levels    */
#define AIRCR_VECTKEY_MASK          (0xFFFF8707)
#define NVIC_PriorityGroup_0        ((uint32_t)0x700)

#define GPIO_PortSourceGPIOA        ((uint8_t)0x00)
#define GPIO_PortSourceGPIOB        ((uint8_t)0x01)
#define GPIO_PortSourceGPIOC        ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD        ((uint8_t)0x03)

#define GPIO_PinSource0             ((uint8_t)0x00)
#define GPIO_PinSource1             ((uint8_t)0x01)
#define GPIO_PinSource2             ((uint8_t)0x02)
#define GPIO_PinSource3             ((uint8_t)0x03)
#define GPIO_PinSource4             ((uint8_t)0x04)
#define GPIO_PinSource5             ((uint8_t)0x05)
#define GPIO_PinSource6             ((uint8_t)0x06)
#define GPIO_PinSource7             ((uint8_t)0x07)
#define GPIO_PinSource8             ((uint8_t)0x08)
#define GPIO_PinSource9             ((uint8_t)0x09)
#define GPIO_PinSource10            ((uint8_t)0x0A)
#define GPIO_PinSource12            ((uint8_t)0x0C)
#define GPIO_PinSource13            ((uint8_t)0x0D)
#define GPIO_PinSource14            ((uint8_t)0x0E)
#define GPIO_PinSource15            ((uint8_t)0x0F)

#define GPIO_PORTSOURCE_KEY        GPIO_PortSourceGPIOB

#define GPIO_PINSOURCE_KEY8        GPIO_PinSource8
#define GPIO_PINSOURCE_KEY9        GPIO_PinSource9
#define GPIO_PINSOURCE_KEY12       GPIO_PinSource12
#define GPIO_PINSOURCE_KEY13       GPIO_PinSource13

#define EXTI_Line8                 ((uint32_t)0x00100)
#define EXTI_Line9                 ((uint32_t)0x00200)
#define EXTI_Line12                ((uint32_t)0x01000)
#define EXTI_Line13                ((uint32_t)0x02000)

#define GPIO_EXTI_Line_KEY8        EXTI_Line8              
#define GPIO_EXTI_Line_KEY9        EXTI_Line9
#define GPIO_EXTI_Line_KEY12       EXTI_Line12             
#define GPIO_EXTI_Line_KEY13       EXTI_Line13

#define AFIO_BASE               (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE               (APB2PERIPH_BASE + 0x0400)
#define AFIO                    ((AFIO_TypeDef *) AFIO_BASE)
#define EXTI                    ((EXTI_TypeDef *) EXTI_BASE)
 
 
/*------------SCB Type-------------*/
typedef struct {
  __I  uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
  _IO uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
  _IO uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  _IO uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
  _IO uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  _IO uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  _IO uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  _IO uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  _IO uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  _IO uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
  _IO uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  _IO uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
  _IO uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
  _IO uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  __I  uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  __I  uint32_t AFR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
       uint32_t RESERVED0[5];
  _IO uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
}SCB_Type;
 
/* ----- SysTick_Type ---- */
typedef struct{
  _IO uint32_t CTRL;                         /*!< SysTick Control and Status Register */
  _IO uint32_t LOAD;                         /*!< SysTick Reload Value Register       */
  _IO uint32_t VAL;                          /*!< SysTick Current Value Register      */
  __I  uint32_t CALIB;                        /*!< SysTick Calibration Register        */
} SysTick_Type;
 
 
/* ----- IRQn_Type ----- */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */
 
/******  STM32 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
  RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  USBWakeUp_IRQn              = 42      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */  
} IRQn_Type;
 
/* -------------- NVIC_Type ----------------- */
typedef struct
{
  _IO uint32_t ISER[8];                      /*!< Interrupt Set Enable Register            */
       uint32_t RESERVED0[24];
  _IO uint32_t ICER[8];                      /*!< Interrupt Clear Enable Register          */
       uint32_t RSERVED1[24];
  _IO uint32_t ISPR[8];                      /*!< Interrupt Set Pending Register           */
       uint32_t RESERVED2[24];
  _IO uint32_t ICPR[8];                      /*!< Interrupt Clear Pending Register         */
       uint32_t RESERVED3[24];
  _IO uint32_t IABR[8];                      /*!< Interrupt Active bit Register            */
       uint32_t RESERVED4[56];
  _IO uint8_t  IP[240];                      /*!< Interrupt Priority Register, 8Bit wide   */
       uint32_t RESERVED5[644];
  _IO  uint32_t STIR;                         /*!< Software Trigger Interrupt Register      */
}  NVIC_Type;
 
/* ------------ FunctionalState --------------- */
typedef enum
{
    DISABLE = 0,
    ENABLE = !DISABLE
} FunctionalState;
 
/* ---------- NVIC_InitTypeDef ----------*/
typedef struct
{
  uint8_t NVIC_IRQChannel; 
  uint8_t NVIC_IRQChannelPreemptionPriority; 
  uint8_t NVIC_IRQChannelSubPriority; 
  FunctionalState NVIC_IRQChannelCmd; 
} NVIC_InitTypeDef;

/* ---------- AFIO_TypeDef ----------*/
typedef struct
{
  _IO uint32_t EVCR;
  _IO uint32_t MAPR;
  _IO uint32_t EXTICR[4];
} AFIO_TypeDef;
 
 
/* ---------- EXTI_TypeDef ----------*/
typedef struct
{
  _IO uint32_t IMR;
  _IO uint32_t EMR;
  _IO uint32_t RTSR;
  _IO uint32_t FTSR;
  _IO uint32_t SWIER;
  _IO uint32_t PR;
} EXTI_TypeDef;
 
/* ---------- EXTIMode_TypeDef ----------*/
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;
 
/* ---------- EXTITrigger_TypeDef ----------*/
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;
 
/* ---------- EXTI_InitTypeDef ----------*/
typedef struct
{
  uint32_t EXTI_Line;
  EXTIMode_TypeDef EXTI_Mode;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
}EXTI_InitTypeDef;
 
/* ------------- Function ----------------- */
void NVIC_Configuration(void);
void NVIC_SetPriority(IRQn_Type, uint32_t);
uint32_t SysTick_Config(uint32_t);
void NVIC_PriorityGroupConfig(uint32_t);
void NVIC_Init(NVIC_InitTypeDef*);
void EXTI_Configuration(void);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
uint8_t EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void SysTick_Handler(void);
void Delay(_IO uint32_t);
void TimingDelay_Decrement(void);
void delay_1_second(void);
void delay_100_milli_second(void);
void delay_10_milli_second(void);
void DELAY_Test(void);
 
#endif /* _INTERRUPT_H_ */
