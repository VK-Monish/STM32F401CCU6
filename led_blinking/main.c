/************************************************/
/*   NAME        : monish kumar.k               */
/*   DATE        :                              */
/*   DESCRIPTION : LED-BLINKING witu C13 pin    */
/************************************************/

volatile unsigned int *RCC_CR       = (volatile unsigned int *)0x40023800; //RCC_CR base address
volatile unsigned int *RCC_CFGR     = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR  = (volatile unsigned int *)0x40023830;

//portc
volatile unsigned int *GPIOC_MODER  = (volatile unsigned int *)0x40020800;
volatile unsigned int *GPIOC_ODR    = (volatile unsigned int *)0x40020814;

void rcc_config(void);
void gpioc_moder(void);
void led_blinking(void);

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
        *GPIOC_MODER  = *GPIOC_MODER | (1<<26); //General purpose input output mode
        *GPIOC_ODR    = *GPIOC_ODR | (1<<13); //GPIO_ODR port output data register,select for 13th bit this pin for portc
}

void led_blinking()
{
        if(*GPIOC_ODR & 1<<13)  //bitwase & AND gate using GPIOC_ODR 13 bit set and 13 bit set for 1
        {
                *GPIOC_ODR = *GPIOC_ODR & ~(1<<13); //clear the bit for pc13th pin
        }
        else
        {
                *GPIOC_ODR = *GPIOC_ODR | (1<<13); //set pc13th for 1,now led blink
        }
}
