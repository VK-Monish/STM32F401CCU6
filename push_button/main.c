#include "header.h" 
#include "sub.c"

void delay()
{
  for(int i=0; i<1000000; i++);
}

void rcc_config()
{
  *RCC_CR = *RCC_CR & (~0X00010000);
  *RCC_CR = *RCC_CR | (1<<16);
  while((*RCC_CR & 1<<17==0));
  *RCC_CFGR = *RCC_CFGR & (~0x00000003);
  *RCC_CFGR = *RCC_CFGR | (1<<0);
  while(!(*RCC_CFGR & 0X00000004)==4);
  *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);
}

void gpio_moder()
{
  *GPIOA_MODER = *GPIOA_MODER | (1<<8);
  *GPIOA_PUPDR = *GPIOA_PUPDR | (1<<1);
}

void button_config()
{
  if(*GPIOA_IDR & (0X00000001) == 1)
  {
    *GPIOA_ODR = *GPIOA_ODR | (1<<4);
    delay();
  }
  else
  {
    *GPIOA_ODR = *GPIOA_ODR & (0<<4);
    delay();
  }
}

int main()
{
  rcc_config();
  gpio_moder();
  while(1)
  {
    button_config();
  }
}
