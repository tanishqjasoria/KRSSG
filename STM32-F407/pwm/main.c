#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_tim.h>
void gpio_config_AF()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;
	GP1.GPIO_Mode = GPIO_Mode_AF;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_UP;
	GP1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_Init(GPIOD ,&GP1 );

}
void timer_baseint()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef tim1;
	tim1.TIM_CounterMode = TIM_CounterMode_Up;
	tim1.TIM_ClockDivision = TIM_CKD_DIV1;
	tim1.TIM_Period = 3000;
	tim1.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM4,&tim1);
}
void oc_setup(int duty)
{

	TIM_OCInitTypeDef oc1;
	oc1.TIM_OutputState=TIM_OutputState_Enable;
	oc1.TIM_OCMode = TIM_OCMode_PWM2;
	oc1.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc1.TIM_Pulse = duty*30;
	TIM_OC1Init(TIM4, &oc1);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

}
int main(void)
{

	gpio_config_AF();
	timer_baseint();
	oc_setup(0);
	TIM_Cmd(TIM4, ENABLE);
	int i=0;
	int j=0;
    while(1)
    {
    	for(i=0; i<=100; i++)
    	{
    		oc_setup(i);
    		for(j=0;j<=10000;j++);
    	}
    }
}
