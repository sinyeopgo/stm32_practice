/*
2023-04-27 STM32F103RBT6 sinyeop interrupt source code
*/
#include "interrupt.h"

static volatile uint32_t TimingDelay;
 
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset){ 
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}
 
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 
   /* Enable the EXTI0 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   /* Enable the EXTI1 Interrupt */
//   NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
//   /* Enable the EXTI2 Interrupt */
//   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
//   /* Enable the EXTI3 Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}
 
uint32_t SysTick_Config(uint32_t ticks){
  if(ticks > SYSTICK_MAXCOUNT) return 1; /*Reload value impossible */
  
  SysTick->LOAD = (ticks & SYSTICK_MAXCOUNT) - 1; /* set reload register */
  NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); /* set Priority for Cortex-M0 System Interrupts */
  SysTick->VAL = 0x00; /* Load the SysTick Counter Value */
  SysTick->CTRL = (1 << SYSTICK_CLKSOURCE) | (1 << SYSTICK_ENABLE) | (1 << SYSTICK_TICKINT); /* Enable Systick IRQ and SysTick Timer */
  return 0; /* Function successful */
}

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup){
  /*Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value*/
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}
 
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority){
  if(IRQn < 0){
    SCB->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF);}      /* set Priority for Cortex-M3 System Interrupt */
  else {
    NVIC->IP[(uint32_t)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF);}                /* set Priority for device specific Interrupt */
}

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct){
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;
 
    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

void EXTI_Configuration(void)
{ 
  
  RCC->APB2ENR |= RCC_APB2Periph_AFIO;
  
    EXTI_InitTypeDef EXTI_InitStructure;
 
    /* Configure gpio as input : Key0 */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY8);
    /* Configure EXTI Line to generate an interrupt */
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY8;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Configure gpio as input : Key1 */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY9);
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY9;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Configure gpio as input : Key2 */
//    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY12);
//    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY12;
//    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
    
    /* Configure gpio as input : Key3 */
    GPIO_EXTILineConfig(GPIO_PORTSOURCE_KEY, GPIO_PINSOURCE_KEY13);
    EXTI_InitStructure.EXTI_Line    = GPIO_EXTI_Line_KEY13;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}
 
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  uint32_t tmp = 0x00;
  
  tmp = ((uint32_t)0x0F) << (0x04 * (GPIO_PinSource & (uint8_t)0x03));
  AFIO->EXTICR[GPIO_PinSource >> 0x02] &= ~tmp;
  AFIO->EXTICR[GPIO_PinSource >> 0x02] |= (((uint32_t)GPIO_PortSource) << (0x04 * (GPIO_PinSource & (uint8_t)0x03)));
}
 
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;
     
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;
    
    tmp = (uint32_t)EXTI_BASE;
    tmp += EXTI_InitStruct->EXTI_Mode;
 
    *(_IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
 
    /* Clear Rising Falling edge configuration */
    EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;
    
    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;
 
      *(_IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp = (uint32_t)EXTI_BASE;
    tmp += EXTI_InitStruct->EXTI_Mode;
 
    /* Disable the selected external lines */
    *(_IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}
 
uint8_t EXTI_GetITStatus(uint32_t EXTI_Line)
{
  uint8_t bitstatus = 0x00;
  uint32_t enablestatus = 0;
  
  enablestatus =  EXTI->IMR & EXTI_Line;
  if (((EXTI->PR & EXTI_Line) != (uint32_t)0x00) && (enablestatus != (uint32_t)0x00))
  {
    bitstatus = 0x01;
  }
  else
  {
    bitstatus = 0x00;
  }
  return bitstatus;
}
 
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  EXTI->PR = EXTI_Line;
}

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY8) != (uint8_t)0x00) {
        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY8);
        printf("key 0 Press\n");
    }
    if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY9) != (uint8_t)0x00) {
        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY9);
        printf("key 1 Press\n");
    }
}
void EXTI15_10_IRQHandler(void){
//  if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY12) != (uint8_t)0x00) {
//        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY12);
//        printf("key 2 Press\n");
//    }
    if(EXTI_GetITStatus(GPIO_EXTI_Line_KEY13) != (uint8_t)0x00) {
        EXTI_ClearITPendingBit(GPIO_EXTI_Line_KEY13);
        printf("key 3 Press\n");
    }
}
void SysTick_Handler(void){
  TimingDelay_Decrement();
}
 
void Delay(_IO uint32_t nTime){
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}
 
void TimingDelay_Decrement(void){
  if(TimingDelay != 0x00)
    TimingDelay--;
}
 
void delay_1_second(void){
  Delay(1000);
}
 
void delay_100_milli_second(void){
  Delay(100);
}

void delay_10_milli_second(void){
  Delay(10);
}
 
void DELAY_Test(void){
  uint32_t i;
  
  for(i=0; i<10 ;i++){
    delay_1_second();
  }
  
  printf("DELAY_Test done!!\n");
}
