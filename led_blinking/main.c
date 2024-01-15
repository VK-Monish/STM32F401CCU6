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
