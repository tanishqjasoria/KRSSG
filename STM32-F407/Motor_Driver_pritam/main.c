#include<stm32f4xx.h>
#include<stm32f4xx_exti.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_rcc.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_syscfg.h>
#include<misc.h>

#define Period 2000
#define pwm_value 1000

void Hall_Input()		//PA1, PA2,PA3
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef H1,H2,H3;
	H1.GPIO_Mode=GPIO_Mode_IN;
	H1.GPIO_OType=GPIO_OType_PP;
	H1.GPIO_Pin=GPIO_Pin_1;
	H1.GPIO_PuPd=GPIO_PuPd_DOWN;
	H1.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &H1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

	H2.GPIO_Mode=GPIO_Mode_IN;
	H2.GPIO_OType=GPIO_OType_PP;
	H2.GPIO_Pin=GPIO_Pin_2;
	H2.GPIO_PuPd=GPIO_PuPd_DOWN;
	H2.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &H2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

	H3.GPIO_Mode=GPIO_Mode_IN;
	H3.GPIO_OType=GPIO_OType_PP;
	H3.GPIO_Pin=GPIO_Pin_3;
	H3.GPIO_PuPd=GPIO_PuPd_DOWN;
	H3.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &H3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
}

void Interrupt()
{
	EXTI_InitTypeDef Ext1;
	Ext1.EXTI_Line=EXTI_Line1;
	Ext1.EXTI_LineCmd=ENABLE;
	Ext1.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext1.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&Ext1);
	NVIC_InitTypeDef nvic1;
	nvic1.NVIC_IRQChannel=EXTI1_IRQn;
	nvic1.NVIC_IRQChannelCmd=ENABLE;
	nvic1.NVIC_IRQChannelPreemptionPriority=0;
	nvic1.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic1);

	EXTI_InitTypeDef Ext2;
	Ext2.EXTI_Line=EXTI_Line2;
	Ext2.EXTI_LineCmd=ENABLE;
	Ext2.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext2.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&Ext2);
	NVIC_InitTypeDef nvic2;
	nvic2.NVIC_IRQChannel=EXTI2_IRQn;
	nvic2.NVIC_IRQChannelCmd=ENABLE;
	nvic2.NVIC_IRQChannelPreemptionPriority=0;
	nvic2.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic2);

	EXTI_InitTypeDef Ext3;
	Ext3.EXTI_Line=EXTI_Line3;
	Ext3.EXTI_LineCmd=ENABLE;
	Ext3.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext3.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&Ext3);
	NVIC_InitTypeDef nvic3;
	nvic3.NVIC_IRQChannel=EXTI3_IRQn;
	nvic3.NVIC_IRQChannelCmd=ENABLE;
	nvic3.NVIC_IRQChannelPreemptionPriority=0;
	nvic3.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic3);
}
void Out_pin()		//PD13,PD14,PD15,PC6,PC7,PC8
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef SR1,SK1,SR2,SK2,SR3,SK3;
	SR1.GPIO_Pin =GPIO_Pin_13;
	SR1.GPIO_Mode= GPIO_Mode_AF;
	SR1.GPIO_Speed = GPIO_Speed_100MHz;
	SR1.GPIO_OType=GPIO_OType_PP;
	SR1.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD , &SR1);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

	SK1.GPIO_Pin =GPIO_Pin_14;
	SK1.GPIO_Mode= GPIO_Mode_AF;
	SK1.GPIO_Speed = GPIO_Speed_100MHz;
	SK1.GPIO_OType=GPIO_OType_PP;
	SK1.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD , &SK1);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);

    SR2.GPIO_Pin =GPIO_Pin_15;
	SR2.GPIO_Mode= GPIO_Mode_AF;
	SR2.GPIO_Speed = GPIO_Speed_100MHz;
	SR2.GPIO_OType=GPIO_OType_PP;
	SR2.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD , &SR2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);

	SK2.GPIO_Pin =GPIO_Pin_6;
	SK2.GPIO_Mode= GPIO_Mode_AF;
	SK2.GPIO_Speed = GPIO_Speed_100MHz;
	SK2.GPIO_OType=GPIO_OType_PP;
	SK2.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC , &SK2);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);

	SR3.GPIO_Pin =GPIO_Pin_7;
	SR3.GPIO_Mode= GPIO_Mode_AF;
	SR3.GPIO_Speed = GPIO_Speed_100MHz;
	SR3.GPIO_OType=GPIO_OType_PP;
	SR3.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC , &SR3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);

	SK3.GPIO_Pin =GPIO_Pin_8;
	SK3.GPIO_Mode= GPIO_Mode_AF;
	SK3.GPIO_Speed = GPIO_Speed_100MHz;
	SK3.GPIO_OType=GPIO_OType_PP;
	SK3.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC , &SK3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
}
void PWM_timers()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseInitTypeDef tim4;
	tim4.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
	tim4.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
	tim4.TIM_Period=Period;//The Top Value That is loaded to the Auto reload register.//the default value.
	tim4.TIM_Prescaler=42;//Prescaler is 16 bit.
    tim4.TIM_RepetitionCounter=0;// For Timer 1 and 8.
    TIM_TimeBaseInit(TIM4,&tim4);

    TIM_OCInitTypeDef timer_outd;
    timer_outd.TIM_OCMode=TIM_OCMode_PWM1;
    timer_outd.TIM_OCPolarity=TIM_OCPolarity_High;
    timer_outd.TIM_OutputState=TIM_OutputState_Enable;
    timer_outd.TIM_Pulse=0;

    TIM_OC2Init(TIM4,&timer_outd);
    TIM_OC3Init(TIM4,&timer_outd);
    TIM_OC4Init(TIM4,&timer_outd);

    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//enable the corresponding preload register by setting the
    //OCxPE bit in the TIMx_CCMRx register
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM4,ENABLE);//setting the ARPE bit in the TIMx_CR1 register.
    TIM_Cmd(TIM4,ENABLE);//Starting the clock
    TIM_SetCounter(TIM4,0);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseInitTypeDef tim3;
    tim3.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
    tim3.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
    tim3.TIM_Period=Period;//The Top Value That is loaded to the Auto reload register.//the default value.
    tim3.TIM_Prescaler=42;//Prescaler is 16 bit.
    tim3.TIM_RepetitionCounter=0;// For Timer 1 and 8.
    TIM_TimeBaseInit(TIM3,&tim3);

    TIM_OCInitTypeDef timer_outc;
    timer_outc.TIM_OCMode=TIM_OCMode_PWM1;
    timer_outc.TIM_OCPolarity=TIM_OCPolarity_High;
    timer_outc.TIM_OutputState=TIM_OutputState_Enable;
    timer_outc.TIM_Pulse=0;

    TIM_OC1Init(TIM3,&timer_outc);
    TIM_OC2Init(TIM3,&timer_outc);
    TIM_OC3Init(TIM3,&timer_outc);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//enable the corresponding preload register by setting the
    //OCxPE bit in the TIMx_CCMRx register
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3,ENABLE);//setting the ARPE bit in the TIMx_CR1 register.
    TIM_Cmd(TIM3,ENABLE);//Starting the clock
    TIM_SetCounter(TIM3,0);
}
void Stop()
{
	TIM4->CCR2=0;
	TIM4->CCR3=0;
	TIM4->CCR4=0;
	TIM3->CCR1=0;
	TIM3->CCR2=0;
	TIM3->CCR3=0;
}

volatile int Hall_Values()
{
	return ((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))+(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)*2)+(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)*4));
}

void Check_Hall_Pwm(volatile int HallValues)		//clockwise
{
    switch(HallValues)
    { case(0):
      {
        Stop();
        break;
      }
      case(5):
      {
    	TIM4->CCR2=pwm_value;
    	TIM4->CCR3=0;
        TIM4->CCR4=0;
        TIM3->CCR1=0;
        TIM3->CCR2=0;
        GPIO_SetBits(GPIOC, GPIO_Pin_8);
        break;
      }
       case(4):
       {
    	 TIM4->CCR2=0;
    	 GPIO_SetBits(GPIOD, GPIO_Pin_14);
    	 TIM4->CCR4=0;
    	 TIM3->CCR1=0;
    	 TIM3->CCR2=pwm_value;
    	 TIM3->CCR3=0;
         break;
       }
       case(6):
       {
    	 TIM4->CCR2=0;
    	 TIM4->CCR3=0;
    	 TIM4->CCR4=0;
    	 GPIO_SetBits(GPIOC, GPIO_Pin_6);
       TIM3->CCR2=pwm_value;
    	 TIM3->CCR3=0;
         break;
       }
      case(2):
      {
         TIM4->CCR2=0;
         TIM4->CCR3=0;
         TIM4->CCR4=pwm_value;
         TIM3->CCR1=0;
         TIM3->CCR2=0;
         GPIO_SetBits(GPIOC, GPIO_Pin_8);
         break;
      }
       case(3):
       {
         TIM4->CCR2=0;
         GPIO_SetBits(GPIOD, GPIO_Pin_14);
         TIM4->CCR4=pwm_value;
         TIM3->CCR1=0;
         TIM3->CCR2=0;
         TIM3->CCR3=0;
         break;
       }
       case(1):
      {
         TIM4->CCR2=pwm_value;
         TIM4->CCR3=0;
         TIM4->CCR4=0;
         GPIO_SetBits(GPIOC, GPIO_Pin_6);
         TIM3->CCR2=0;
         TIM3->CCR3=0;
         break;
      }
      case(7):
      {
      Stop();
      break;
      }
    }
}
/*
void Check_Hall_Pwm2(volatile int HallValues)		//anticlockwise
{
    switch(HallValues)
    { case(0):
      {
        Stop();
        break;
      }
      case(5):
      {
    	TIM4->CCR2=0;
    	TIM4->CCR3=0;
        TIM4->CCR4=pwm_value;
        TIM3->CCR1=0;
        TIM3->CCR2=0;
        TIM3->CCR3=pwm_value;
        break;
      }
       case(4):
       {
    	 TIM4->CCR2=0;
    	 TIM4->CCR3=pwm_value;
    	 TIM4->CCR4=pwm_value;
    	 TIM3->CCR1=0;
    	 TIM3->CCR2=0;
    	 TIM3->CCR3=0;
         break;
       }
       case(6):
       {
    	 TIM4->CCR2=pwm_value;
    	 TIM4->CCR3=0;
    	 TIM4->CCR4=0;
    	 TIM3->CCR1=pwm_value;
         TIM3->CCR2=0;
    	 TIM3->CCR3=pwm_value;
         break;
       }
      case(2):
      {
         TIM4->CCR2=pwm_value;
         TIM4->CCR3=0;
         TIM4->CCR4=0;
         TIM3->CCR1=0;
         TIM3->CCR2=0;
         TIM3->CCR3=pwm_value;
         break;
      }
       case(3):
       {
         TIM4->CCR2=0;
         TIM4->CCR3=pwm_value;
         TIM4->CCR4=0;
         TIM3->CCR1=0;
         TIM3->CCR2=pwm_value;
         TIM3->CCR3=0;
         break;
       }
       case(1):
      {
         TIM4->CCR2=0;
         TIM4->CCR3=0;
         TIM4->CCR4=0;
         TIM3->CCR1=pwm_value;
         TIM3->CCR2=pwm_value;
         TIM3->CCR3=0;
         break;
      }
      case(7):
      {
      Stop();
      break;
      }
    }
}
void EXTI4_IRQHandler(void)   //ccw
{
    while(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
      Check_Hall_Pwm2(Hall_Values());
      EXTI_ClearITPendingBit(EXTI_Line4);
      NVIC_ClearPendingIRQ(EXTI4_IRQn);
    }
}
void EXTI5_IRQHandler(void)     //ccw
{
    while(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
      Check_Hall_Pwm2(Hall_Values());
      EXTI_ClearITPendingBit(EXTI_Line5);
      NVIC_ClearPendingIRQ(EXTI6_IRQn);
    }
}
void EXTI6_IRQHandler(void)   //ccw
{
    while(EXTI_GetITStatus(EXTI_Line6) != RESET)

    {
      Check_Hall_Pwm2(Hall_Values());
      EXTI_ClearITPendingBit(EXTI_Line6);
      NVIC_ClearPendingIRQ(EXTI6_IRQn);
    }
}

*/
void EXTI1_IRQHandler(void)   //cw
{
    while(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
    	Check_Hall_Pwm(Hall_Values());
	    EXTI_ClearITPendingBit(EXTI_Line1);
	    NVIC_ClearPendingIRQ(EXTI1_IRQn);
    }
}
void EXTI2_IRQHandler(void)   //cw
{
    while(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
    	Check_Hall_Pwm(Hall_Values());
	    EXTI_ClearITPendingBit(EXTI_Line2);
	    NVIC_ClearPendingIRQ(EXTI2_IRQn);
    }
}
void EXTI3_IRQHandler(void)   //cw
{
    while(EXTI_GetITStatus(EXTI_Line3) != RESET)

    {
    	Check_Hall_Pwm(Hall_Values());
	    EXTI_ClearITPendingBit(EXTI_Line3);
	    NVIC_ClearPendingIRQ(EXTI3_IRQn);
    }
}

int main(void)
{
	Hall_Input();
	Out_pin();
	Interrupt();
	PWM_timers();

	while(1)
	    {
	    //	printf((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))+(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)*2)+(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)*4));
	    }
}
