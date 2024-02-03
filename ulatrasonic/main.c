/******************************************************/
/*   NAME        : MONISH KUMAR.K                     */
/*   DATE        :                                    */
/*   DESCRIPTION : INTRFACING WITH ULTRASONIC sensor  */
/******************************************************/

#include "header.h"
#include "sub.c"

void rcc_config()
{
  //Clear 16 bit RCC clock control register (RCC_CR);
  *RCC_CR = *RCC_CR & (~0x00010000);

  //Set 16 bit RCC clock control register (RCC_CR); for seting external clock
  *RCC_CR = *RCC_CR | (1<<16);

  //Check HSERDY: for wheather the flag is seted or not
  while((*RCC_CR & (1<<17)) == 0);

  //Clear 1 and 2 bit RCC clock configuration register (RCC_CFGR);
  *RCC_CFGR = *RCC_CFGR & (~0x00000003);

  //Set 1 bit RCC clock configuration register (RCC_CFGR); for seting HSE oscillator is selected as system clock
  *RCC_CFGR = *RCC_CFGR | (1<<0);

  //Check SW0: for wheather the SWS is used as system clock 
  while(!(*RCC_CFGR & 0x00000004)==4);

  //Set 0 bit for accesing port A 
  *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);
}

void sys1()
{
  //(STK_LOAD) -> SysTick reload value register
  //To set how many cycle want to run
  *STK_LOAD = 12500000;

  //STK_CTRL ->SysTick control and status register
  //To enable the clock source and counter 
  *STK_CTRL = *STK_CTRL | (0x00000005);

  //Check COUNT FLAG until 1
  while(!(*STK_CTRL & (1<<16)));
}

void sys()
{
  //(STK_LOAD) -> SysTick reload value register
  //To set how many cycle want to run
  *STK_LOAD = 275;

  //STK_CTRL ->SysTick control and status register
  //To enable the clock source and counter 
  *STK_CTRL = *STK_CTRL | (0x00000005);

  //Check COUNT FLAG until 1
  while(!(*STK_CTRL & (1<<16)));
}
 
void gpio_moder()
{
   
  //Set moder for output mode 
  *GPIOA_MODER = *GPIOA_MODER | (1<<8);

  //Set moder for output mode 
  *GPIOA_MODER = *GPIOA_MODER | (1<<10);            

  //set pupdr for pull down state
  *GPIOA_PUPDR = *GPIOA_PUPDR | (1<<1);
} 

void inter()
{
  *GPIOA_ODR  = *GPIOA_ODR & (0<<5);
  while(1)
  {
    *GPIOA_ODR = *GPIOA_ODR | (1<<4);
    sys();
    *GPIOA_ODR = *GPIOA_ODR & (0<<4);

    if(*GPIOA_IDR & (1<<0) == 1)
    {
      *GPIOA_ODR  = *GPIOA_ODR | (1<<5);
      for(int i=0; i<2; i++)
      {
	sys1();
      }
      inter(); 
    }
  }
}

int main()
{
  rcc_config();
  gpio_moder();
  inter();
}
