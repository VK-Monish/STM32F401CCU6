volatile unsigned int *RCC_CR      = (volatile unsigned int *)0x40023800;
volatile unsigned int *RCC_CFGR    = (volatile unsigned int *)0x40023808;
volatile unsigned int *RCC_AHB1ENR = (volatile unsigned int *)0x40023830;

//choose port a and b
volatile unsigned int *GPIOA_MODER = (volatile unsigned int *)0X40020000;
volatile unsigned int *GPIOA_ODR   = (volatile unsigned int *)0x40020014;

volatile unsigned int *GPIOB_MODER = (volatile unsigned int *)0x40020400;
volatile unsigned int *GPIOB_ODR   = (volatile unsigned int *)0x40020414;

void rcc_config(void);
void gpiob_moder(void);
void led_blinking(void);
void delay(void);
void led_blinking1(void);

void delay()
{
  int k;
  for(k=0; k<100000; k++);
}

int main()
{
  int i;
  rcc_config();
  gpiob_moder();
  for(i=0; i<1000; i++)
  {
    led_blinking();
    delay();
    led_blinking1();
    delay();
  }
}

void rcc_config()
{
  *RCC_CR = *RCC_CR & (~0X00010000);
  *RCC_CR = *RCC_CR | (1<<16);
  while((*RCC_CR & 1<<17)==0);
  *RCC_CFGR = *RCC_CFGR & (~0X00000003);
  *RCC_CFGR = *RCC_CFGR | (1<<0);
  while((*RCC_CFGR & 0X00000004)==0);
  *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<0);
  *RCC_AHB1ENR = *RCC_AHB1ENR | (1<<1);
}

void gpiob_moder()
{
  int i;
  for(i=0; i<15; i++)
  {
    *GPIOA_MODER = *GPIOA_MODER | (1<<i);
    if(i==6)
    {
      *GPIOB_MODER = *GPIOB_MODER | (1<<24);
    }
    else if(i==8)
    {
      *GPIOB_MODER = *GPIOB_MODER | (1<<26);
    }
    else
    {
      *GPIOB_MODER = *GPIOB_MODER | (1<<i);
    }
    i++;
  }
}

void led_blinking()
{
  int i;
  for(i=7; i>=0; i--)
  { 
     *GPIOA_ODR   = *GPIOA_ODR   | (1<<i);
     if(i==3)
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<12);
      }
      else if(i==4)
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<13);
      }
      else
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<i);
      }
      delay();
  }
  for(i=0; i<=13; i++)
  {
    *GPIOB_ODR = *GPIOB_ODR & (1<<i);
    *GPIOA_ODR = *GPIOA_ODR & (1<<i);
  }
  delay();
}
void led_blinking1()
{
  int i;
   for(i=0; i<=7; i++)
   { 
      *GPIOA_ODR   = *GPIOA_ODR   | (1<<i);
      if(i==3)
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<12);
      }
      else if(i==4)
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<13);
      }
      else
      {
	*GPIOB_ODR   = *GPIOB_ODR   | (1<<i);
      }
      delay();
   }
  for(i=0; i<=13; i++)
  {
    *GPIOB_ODR = *GPIOB_ODR & (1<<i);
    *GPIOA_ODR = *GPIOA_ODR & (1<<i);
  }
  delay();
}
