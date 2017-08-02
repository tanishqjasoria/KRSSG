#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
//#include <stm32f4xx_tim.h>
void clock_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		//ENABLE GPIOD Clock
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
void gpio_init()
{
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;                				//Settings for All Pins
	GP1.GPIO_Mode = GPIO_Mode_OUT;								//Set Pin Mode to output
	GP1.GPIO_OType = GPIO_OType_PP;								//Push-Pull - Can be both high and low
	GP1.GPIO_PuPd = GPIO_PuPd_DOWN;								//Pull Down
	GP1.GPIO_Speed = GPIO_Speed_100MHz;							//Speed of GPIO 100MHz
	GPIO_Init(GPIOD ,&GP1 );									//Initializing GPIOD with above settings
}
int main(void)
{
	clock_init();
	gpio_init();
    while(1)
    {
    	GPIO_SetBits(GPIOD, GPIO_Pin_All);						//Setting all pins to High
    }
}
