#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_tim.h>
#include <misc.h>
volatile int sec=2;
volatile int count =0;


void TIM2_IRQHandler(void)										//Interrupt Request Handler
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))					//Check TIM2 Update interrupt status
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_All);					//Toggling bits if interrupt captured
		TIM_ClearITPendingBit(TIM2,  TIM_IT_Update);			//Clear pending interrupt bits for TIM2 Update type interrupt
	}
}
void clock_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
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
void tim_init()
{
	TIM_TimeBaseInitTypeDef tim1;
	tim1.TIM_CounterMode = TIM_CounterMode_Up;
	tim1.TIM_ClockDivision = TIM_CKD_DIV1;
	tim1.TIM_Period = 245;										//Period and prescaler set such that it overflows in 1 sec
	tim1.TIM_Prescaler = 0xFFFF;
	TIM_TimeBaseInit(TIM2,&tim1);
	TIM_Cmd(TIM2, ENABLE);
}
void NVIC_Config_TIM2INT()                                      // Used to config interrupts
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);				//Selecting form 5 sets of priority groups
	NVIC_InitTypeDef I1;
	I1.NVIC_IRQChannel = TIM2_IRQn;								//Intialize interrupt channel to TIM2
	I1.NVIC_IRQChannelCmd = ENABLE;								//Enable Channel
	I1.NVIC_IRQChannelPreemptionPriority = 0;					//Interrupt Priority
	//I1.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&I1);
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);					// Configuring type of TIM2 Interuupt. Here type is update(Overflow) type
}
int main(void)
{
	clock_init();
	gpio_init();
	tim_init();
	NVIC_Config_TIM2INT();

	GPIO_ResetBits(GPIOD, GPIO_Pin_All);
	while(1)
    {
		//GPIO_SetBits(GPIOD, GPIO_Pin_All);
    }
}
