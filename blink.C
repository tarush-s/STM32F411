#include"main.h"
#include"stm32f411xe.h"
void blink(void);
void ports(void);
void systick_init(void);
void DelayMillis(void);
void DelayMs(unsigned long t);
int main()
{
	systick_init();
	ports();
	while(1)
	{
		blink();

	}
}
void ports()
{
	//enable clk for port c
	RCC->AHB1ENR|=(1<<2);
	// set PC13 as output
	GPIOC->MODER|=(1<<26);
	GPIOC->MODER&=~(1<<27);
}
void blink()
{
	GPIOC->BSRR|=(1<<29);
	DelayMs(100);
	GPIOC->BSRR|=(1<<13);
	DelayMs(100);
}
void systick_init(void) // INITIALISING SYSTICK -> ARM MPU TIMER
{
	// RESET VALUES FOR EACH REGISTER (PRESENT BY DEFAULT)
	SysTick -> CTRL = 0; // CTRL -> CONTROL AND STATUS REGISTER
	SysTick -> LOAD = 0x00FFFFFF; // LOAD -> RELOAD VALUE REGISTER
	SysTick -> VAL = 0; // VAL -> CURRENT VALUE REGISTER

  // NEW DESIRED VALUE
	SysTick -> CTRL |= 5; // 5 = 0b101 | 0th BIT = ENABLE -> HIGH | 2nd BIT = CLK_SOURCE -> HIGH => CLOCK SOURCE = AHB
}
void DelayMillis(void) // DELAY FOR EXACTLY 1 MILI-SECOND
{
	SysTick -> LOAD = 0x11940; // Ox11940 = 72000 (Decimal)
	SysTick -> VAL = 0; // STARTING FROM 0
	while((SysTick -> CTRL & 0x00010000) == 0); // CHECKS THE "COUNT FLAG" BIT | 1ms TO EXIT THIS LOOP
}
void DelayMs(unsigned long t) // FUCNTION TO REPEAT THE "DelayMillis()" FUNCTION BY DESIRED NUMBER OF TIMES
{
	for(; t > 0; t--)
		{
			DelayMillis();
		}
}
