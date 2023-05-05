/*
2023-04-27 STM32F103RBT6 sinyeop Usart header
*/
#ifndef USART_H
#define USART_H
#include "platform_config.h"
#include "stdio.h"

#define GPIO_USART1 GPIOA

#define USART_Tx_Pin GPIO_PIN_9
#define USART_Rx_Pin GPIO_PIN_10

//Word Length
#define USART_WordLength_8b  ((uint16_t)0x0000)
#define USART_WordLength_9b  ((uint16_t)0x1000)

//Stop Bits
#define USART_StopBits_1     ((uint16_t)0x0000)
#define USART_StopBits_0_5   ((uint16_t)0x1000)
#define USART_StopBits_2     ((uint16_t)0x2000)
#define USART_StopBits_1_5   ((uint16_t)0x3000)

//Parity
#define USART_Parity_No      ((uint16_t)0x0000)
#define USART_Parity_Even    ((uint16_t)0x0400)
#define USART_Parity_Odd     ((uint16_t)0x0600)

//Hardware Flow Control
#define USART_HardwareFlowControl_None          ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS           ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS           ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS       ((uint16_t)0x0300)

//Mode
#define USART_Mode_Rx           ((uint16_t)0x0004)
#define USART_Mode_Tx           ((uint16_t)0x0008)

//USART Enable
#define CR1_UE_Set              ((uint16_t)0x2000)

//Clock
#define HSI_Value               ((uint32_t)8000000)

//USART CR2 STOP Bits Mask
#define CR2_STOP_CLEAR_Mask     ((uint16_t)0xCFFF)  

//USART CR1 Mask
#define CR1_CLEAR_Mask          ((uint16_t)0xE9F3)

//USART CR3 Mask
#define CR3_CLEAR_Mask          ((uint16_t)0xFCFF)

//USART Status register TXE
#define USART_FLAG_TXE          ((uint16_t)0x0080)

//USART Status register TXE
#define USART_FLAG_RXNE         ((uint16_t)0x0020)

void USART1_init();
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint8_t USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void Serial_PutChar(uint8_t c);
void Serial_PutString(uint8_t *s);
int putchar(int ch);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
uint8_t USART_GetCharater(USART_TypeDef* usart_p);
void System_Information();
#endif