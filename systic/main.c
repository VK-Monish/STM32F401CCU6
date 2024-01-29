/************************************************/
/*   NAME        : monish kumar.k               */
/*   DATE        : 27/01/2024                   */
/*   DESCRIPTION : systic  timer                */
/************************************************/

volatile unsigned int *RCC_CR       = (volatile unsigned int *)0x40023800;//RCC_CR base address
volatile unsigned int *RCC_CFGR     = (volatile unsigned int *)0x40023808;//selecting internal clock or external clock
volatile unsigned int *RCC_AHB1ENR  = (volatile unsigned int *)0x40023830; 

//portc
volatile unsigned int *GPIOC_MODER  = (volatile unsigned int *)0x40020800;
volatile unsigned int *GPIOC_ODR    = (volatile unsigned int *)0x40020814;

volatile unsigned int *STK_CTRL     = (volatile unsigned int *)0xE000E010;
volatile unsigned int *STK_LOAD     = (volatile unsigned int *)0xE000E014;

void rcc_config(void);
void gpioc_moder(void);
void led_blinking(void);
void systic_timer(void);

void systic_timer()
{
  *STK_LOAD = 275;
  *STK_CTRL = *STK_CTRL | (0x00000005);
  while(!(*STK_CTRL & (1<<16)));
}

int main()
{
        rcc_config();
        gpioc_moder();
        while(1)
        {
                led_blinking();
        }
}

void rcc_config()
{
        *RCC_CR   = *RCC_CR & (~0x00010000); //clock control register RCC_CR,16 bit select for HCE pin enable, HCE for high speed external
        *RCC_CR   = *RCC_CR | (1<<16); //16 bit set for 1 
        while((*RCC_CR & 1<<17)==0); //HSE clock ready flag,0: HSE oscillator not, ready status register 
        *RCC_CFGR = *RCC_CFGR & (~0X00000003); //system clock source ,select for 1 bit and 2 bit, clock configuration register CFGR
        *RCC_CFGR = *RCC_CFGR | (1<<0); //01: HSE oscillator selected as system clock
        while(!(*RCC_CFGR & 0X00000004)==4); //control AHB clock division factor
        *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<2); //Bit 2 GPIOCEN: IO port C clock enable,RCC_AHB1ENR peripheral clock enable register
}

void gpioc_moder()
{
        *GPIOC_MODER  = *GPIOC_MODER | (1<<28); //General purpose input output mode
}

void led_blinking()
{
  *GPIOC_ODR = *GPIOC_ODR | (1<<14);
    systic_timer();
  *GPIOC_ODR = *GPIOC_ODR & (0<<14);
    systic_timer();
}
