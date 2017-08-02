#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_syscfg.h>




void EXTI0_IRQHandler(void)
{
	GPIO_ToggleBits(GPIOD, GPIO_Pin_All);
	EXTI_ClearITPendingBit(EXTI_Line0);
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//GPIO
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;
	GP1.GPIO_Mode = GPIO_Mode_OUT;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_UP;
	GP1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD ,&GP1 );

	GPIO_InitTypeDef GP2;
	GP2.GPIO_Pin = GPIO_Pin_0;
	GP2.GPIO_Mode = GPIO_Mode_IN;
	GP2.GPIO_OType = GPIO_OType_PP;
	GP2.GPIO_PuPd = GPIO_PuPd_DOWN;
	GP2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA ,&GP2 );

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	EXTI_InitTypeDef ext1;
	ext1.EXTI_Line = EXTI_Line0;
	ext1.EXTI_Mode = EXTI_Mode_Interrupt;
	ext1.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	ext1.EXTI_LineCmd = ENABLE;
	EXTI_Init(&ext1);

	NVIC_InitTypeDef I1;
	I1.NVIC_IRQChannel = EXTI0_IRQn;
	I1.NVIC_IRQChannelCmd = ENABLE;
	I1.NVIC_IRQChannelPreemptionPriority = 0;
	I1.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&I1);


	GPIO_SetBits(GPIOD, GPIO_Pin_All);



	while(1)
    {
		//GPIO_SetBits(GPIOD, GPIO_Pin_All);
    }
}
