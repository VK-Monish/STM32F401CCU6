/******************************************************/
/*   NAME        : MONISH KUMAR.K                     */
/*   DATE        : 28/01/2024                         */
/*   DESCRIPTION : INTERFACING WITH PIR SENSOR        */
/******************************************************/
#include "header.h"
#include "sub.c"
int main()
{
  rcc_config();
  gpio_moder();
  while(1)
  {
    pir_config();
  }
}
void systic_timer()
{

}

void delay()
{
  for(int i=0; i<1000000; i++);
}
void rcc_config()
{
  *RCC_CR      = *RCC_CR & (~0X00010000);
  *RCC_CR      = *RCC_CR | (1<<16);
  while((*RCC_CR & 1<<17)==0);
  *RCC_CFGR    = *RCC_CFGR & (~0X00000003);
  *RCC_CFGR    = *RCC_CFGR | (1<<0);
  while((*RCC_CFGR & 0X00000004)==0);
  *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);
}
void gpio_moder()
{
   *GPIOA_MODER = *GPIOA_MODER | (1<<8);
   *GPIOA_PUPDR = *GPIOA_PUPDR | (1<<3);
}
void pir_config()
{
  if(*GPIOA_IDR & (1<<1) == 2 )
  {
    *GPIOA_ODR = *GPIOA_ODR | (1<<4);
  }
  else
  {
    *GPIOA_ODR = *GPIOA_ODR & (0<<4);
  }
}	
