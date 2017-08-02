#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_tim.h>
void clock_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//ENABLE GPIOD CLock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ENABLE TIM2 Clock
}
void gpio_init()
{
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;
	GP1.GPIO_Mode = GPIO_Mode_OUT;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_UP;
	GP1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD ,&GP1 );
}
void tim2_init()
{
	TIM_TimeBaseInitTypeDef tim1;
	tim1.TIM_CounterMode = TIM_CounterMode_Up;				//Counter counting would be from 0 - Period and then back to 0
	tim1.TIM_ClockDivision = TIM_CKD_DIV1;					//??
	tim1.TIM_Period = 0xFFFF;								//Period = Max value of counter i.e.,65535
	tim1.TIM_Prescaler = 0xFFFF;							//PreScaler set to 65536
	TIM_TimeBaseInit(TIM2,&tim1);							//TIM2 intitalization with values in tim1
	TIM_Cmd(TIM2, ENABLE);									//Enables the TIM2 peripheral.
}
int main(void)
{


	GPIO_ResetBits(GPIOD, GPIO_Pin_All);					//Set output GPIOD to LOW

    while(1)
    {
    	TIM_SetCounter(TIM2, 0);							//Counter of TIM2 set to 0
    	while(TIM_GetCounter(TIM2) <= 256);					//Counting counter from 0 - 256
    	GPIO_ToggleBits(GPIOD, GPIO_Pin_All);				//Toggling bits form high->low or low->high
    }
}
