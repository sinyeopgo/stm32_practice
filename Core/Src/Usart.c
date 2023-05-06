/*
2023-04-27 STM32F103RBT6 sinyeop usart source code
*/
#include "Usart.h"

void USART1_init(){
  RCC->APB2ENR |= RCC_APB2Periph_GPIOA;
  RCC->APB2ENR |= RCC_APB2Periph_USART1;
  
  GPIO_InitTypeDef GPIO_InitStructure;
    
  //Usart Configuration
  /*Configure USARTx_Tx as alternate function push-pull*/
  GPIO_InitStructure.GPIO_Pin = USART_Tx_Pin; //usart1_tx pin
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIO_USART1, &GPIO_InitStructure);
  
    /*Configure USARTx_Rx as alternate function push-pull*/
  GPIO_InitStructure.GPIO_Pin = USART_Rx_Pin; //usart1_rx pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_USART1, &GPIO_InitStructure);
  
  /*USARTx configuration------------------------*/
  /*USARTx configured as follow:
  - BaudRate = 115200 baud
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitTypeDef USART_InitStructure;
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  
  // Configure the USARTx
  USART_Init(USART1, &USART_InitStructure);
  
  // Enable the USART1
  USART1->CR1 |= CR1_UE_Set;
}

void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct){
  uint32_t tmpreg = 0x00, apbclock = 72000000;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  
  //----------------------USART CR2 Configuration----------------------
  tmpreg = USARTx->CR2;
  // Clear STOP[13:12] bits
  tmpreg &= CR2_STOP_CLEAR_Mask;
  // Configure the USART Stop Bits, Clock, CPOL, CPHA and Last Bits
  // Set STOP[13:12] bits according to USART_StopBits value
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  // Write to USART CR2
  USARTx->CR2 = (uint16_t)tmpreg;
  
  
  //--------------------USART CR1 Configuration-----------------------
  tmpreg = USARTx->CR1;
  // Clear M,PCE,PS,TE and RE bits
  tmpreg &= CR1_CLEAR_Mask;
  // Configure the USART Word Length, Parity and mode------------------
  // Set the M bits according to USART_WordLength value
  // Set PCE and PS bits according to USART_Parity value
  // Set TE and RE bits according to USART_Mode value
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity | USART_InitStruct->USART_Mode;
  // Write to USART CR1
  USARTx->CR1 = (uint16_t)tmpreg;
  
  
  //---------------------USART CR3 Configuration------------------------
  tmpreg = USARTx->CR3;
  // Clear CTSE and RTSE bits
  tmpreg &= CR3_CLEAR_Mask;
  // Configure the USART HFC----------------------------
  // Set CTSE and RTSE bits according to USART_HardwareFlowControl value
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  // Write to USART CR3
  USARTx->CR3 = (uint16_t)tmpreg;
  
  
  //---------------------USART BRR Configuration--------------------------
  // Configure the USART Baud Rate ------------------------------------
  // Determine the integer part
  integerdivider = ((0x19 * apbclock) / (0x04 * (USART_InitStruct->USART_BaudRate)));
  tmpreg = (integerdivider / 0x64) << 0x04;
  // Determine the fractional part
  fractionaldivider = integerdivider - (0x64 * (tmpreg >> 0x04));
  tmpreg |= ((((fractionaldivider * 0x10) + 0x32) / 0x64)) & ((uint8_t)0x0F);
  // Write to USART BRR
  USARTx->BRR = (uint16_t)tmpreg;
}
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data){
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

uint8_t USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG){
  
  if((USARTx->SR & USART_FLAG) != (uint16_t)0x00)      return (uint16_t)0x01;
  else                                                 return (uint16_t)0x00;
}

void Serial_PutChar(uint8_t c){
  USART_SendData(USART1, c);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == ((uint16_t)0x00));
}

void Serial_PutString(uint8_t *s){
  while(*s !='\0'){
    Serial_PutChar(*s);
    s++;
  }
}

int putchar(int ch){
  if(ch == '\n'){
    USART_SendData(USART1, '\r');
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)0x00);
    USART_SendData(USART1,'\n');
  } else{
    USART_SendData(USART1, (uint8_t)ch);
  }
  /*Loop until the end of transmission*/
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == (uint16_t)0x00);
  return ch;
}

uint16_t USART_ReceiveData(USART_TypeDef* USARTx){
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

uint8_t USART_GetCharater(USART_TypeDef* usart_p){
  uint8_t data;
  
  while(USART_GetFlagStatus(usart_p, USART_FLAG_RXNE) == (uint16_t)0x00);
  
  data = USART_ReceiveData(usart_p);
  
  //output data to terminal
  USART_SendData(usart_p,data);
  while(USART_GetFlagStatus(usart_p, USART_FLAG_TXE) == (uint16_t)0x00);
  
  if(data == '\r') return (int)('\n');
  else             return data;
}
//void System_Information(){
//  printf("USART1->BRR : 0x%08X\n",USART1->BRR);
//}