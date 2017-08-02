#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include "semihosting.h"
#include "stdio.h"
#define Period 2000
#define pwm_value 2000
#define hall 0

GPIO_InitTypeDef Hall1;//PC2
GPIO_InitTypeDef Hall2;//PC3 NEED TO GIVE
GPIO_InitTypeDef Hall3;//PC4
EXTI_InitTypeDef Ext1;
EXTI_InitTypeDef Ext2;
EXTI_InitTypeDef Ext3;
NVIC_InitTypeDef nvic1;
NVIC_InitTypeDef nvic2;
NVIC_InitTypeDef nvic3;

TIM_TimeBaseInitTypeDef Timer_4;
TIM_OCInitTypeDef Timer_OUT;

TIM_TimeBaseInitTypeDef Timer_3;
TIM_OCInitTypeDef Timer_OUT1;
GPIO_InitTypeDef PmosA;//PD13 A TIM4_>ccr2
GPIO_InitTypeDef ENA;//PC6
GPIO_InitTypeDef PmosB;//PD14 B TIM4_>ccr3
GPIO_InitTypeDef ENB;//PC7
GPIO_InitTypeDef PmosC;//PD15 C TIM4_>ccr4
GPIO_InitTypeDef ENC;//PC8


void Gpio_Interrupt()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	Hall1.GPIO_Mode=GPIO_Mode_IN;
	Hall1.GPIO_OType=GPIO_OType_PP;
	Hall1.GPIO_Pin=GPIO_Pin_2;
	Hall1.GPIO_PuPd=GPIO_PuPd_NOPULL;
	Hall1.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&Hall1);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource2);
	Ext1.EXTI_Line=EXTI_Line2;
	Ext1.EXTI_LineCmd=ENABLE;
	Ext1.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext1.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&Ext1);

	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nvic1.NVIC_IRQChannel=EXTI2_IRQn;
	nvic1.NVIC_IRQChannelCmd=ENABLE;
	nvic1.NVIC_IRQChannelPreemptionPriority=0;
	nvic1.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic1);



	Hall2.GPIO_Mode=GPIO_Mode_IN;
	Hall2.GPIO_OType=GPIO_OType_PP;
	Hall2.GPIO_Pin=GPIO_Pin_3;
	Hall2.GPIO_PuPd=GPIO_PuPd_NOPULL;
	Hall2.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&Hall2);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource3);
    Ext2.EXTI_Line=EXTI_Line3;
	Ext2.EXTI_LineCmd=ENABLE;
	Ext2.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext2.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&Ext2);

	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nvic2.NVIC_IRQChannel=EXTI3_IRQn;
	nvic2.NVIC_IRQChannelCmd=ENABLE;
	nvic2.NVIC_IRQChannelPreemptionPriority=0;
	nvic2.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic2);


	Hall3.GPIO_Mode=GPIO_Mode_IN;
	Hall3.GPIO_OType=GPIO_OType_PP;
	Hall3.GPIO_Pin=GPIO_Pin_4;
	Hall3.GPIO_PuPd=GPIO_PuPd_NOPULL;
	Hall3.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&Hall3);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource4);
	Ext3.EXTI_Line=EXTI_Line4;
	Ext3.EXTI_LineCmd=ENABLE;
	Ext3.EXTI_Mode=EXTI_Mode_Interrupt;
	Ext3.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&Ext3);

	//	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	nvic3.NVIC_IRQChannel=EXTI4_IRQn;
	nvic3.NVIC_IRQChannelCmd=ENABLE;
	nvic3.NVIC_IRQChannelPreemptionPriority=0;
	nvic3.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&nvic3);

}
void HALL_TEST_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef test;
	test.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	test.GPIO_Mode=GPIO_Mode_OUT;
	test.GPIO_OType=GPIO_OType_PP;
	test.GPIO_PuPd=GPIO_PuPd_NOPULL;
	test.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&test);

}
void HALL_TEST(int abc)
{
	switch(abc)
	    {

	      case(0):
	      {
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_13,0); //QL1
	    	  	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,0); //QL2
	    	  	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,0); //QL3	        break;
	      }
	      /*
	       * Hall1=1,Hall2=1,Hall3=0, with bases 3
	       * Means A-Float,B-High_Side,C-Low_Side
	       */
	      case(3):
	      {
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_13,1); //QL1
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,1); //QL2
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,0); //QL3
	    	  break;
	      }

	      /*
	       * Hall1=0,Hall2=1,Hall3=0, with bases 2
	       * Means A-Low_Side,B-High_Side,C-float
	       */
	       case(2):
	       {
	    	   GPIO_WriteBit(GPIOE,GPIO_Pin_13,0); //QL1
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,1); //QL2
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,0); //QL3
	    	   break;

	       }

	       /*
	       * Hall1=0,Hall2=1,Hall3=1, with bases 6
	       * Means A-Low_Side,B-float,C-High_Side
	       */
	       case(6):
	       {


	    	   GPIO_WriteBit(GPIOE,GPIO_Pin_13,0); //QL1
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,1); //QL2
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,1); //QL3
	    	   break;

	       }

	          /*
	       * Hall1=0,Hall2=0,Hall3=1, with bases 4
	       * Means A-float,B-Low_side,C-High_Side
	       */
	      case(4):
	      {
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_13,0); //QL1
	    	  	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,0); //QL2
	    	  	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,1); //QL3
	    	  break;
	      }

	        /*
	       * Hall1=1,Hall2=0,Hall3=1, with bases 5
	       * Means A-High_Side,B-Low_side,C-Float
	       */

	       case(5):
	       {
	    	   GPIO_WriteBit(GPIOE,GPIO_Pin_13,1); //QL1
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,0); //QL2
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,1); //QL3
	    	   break;
	       }

	        /*
	       * Hall1=1,Hall2=0,Hall3=0, with bases 1
	       * Means A-High_Side,B-float,C-Low_Side
	       */

	       case(1):
	      {
	    	   GPIO_WriteBit(GPIOE,GPIO_Pin_13,1); //QL1
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,0); //QL2
	    	   	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,0); //QL3
	    	   break;
	      }


	      case(7):
	     {
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_13,1); //QL1
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_14,1); //QL2
	    	  GPIO_WriteBit(GPIOE,GPIO_Pin_15,1); //QL3
			  break;
	     }


	    }

}




void Gpio_pwm()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	PmosA.GPIO_Pin=GPIO_Pin_13;
	PmosA.GPIO_Mode=GPIO_Mode_AF;
	PmosA.GPIO_OType=GPIO_OType_PP;
	PmosA.GPIO_PuPd=GPIO_PuPd_NOPULL;
	PmosA.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&PmosA);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);

	PmosB.GPIO_Pin=GPIO_Pin_14;
	PmosB.GPIO_Mode=GPIO_Mode_AF;
	PmosB.GPIO_OType=GPIO_OType_PP;
	PmosB.GPIO_PuPd=GPIO_PuPd_NOPULL;
	PmosB.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&PmosB);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);

    PmosC.GPIO_Pin=GPIO_Pin_15;
    PmosC.GPIO_Mode=GPIO_Mode_AF;
    PmosC.GPIO_OType=GPIO_OType_PP;
    PmosC.GPIO_PuPd=GPIO_PuPd_NOPULL;
    PmosC.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&PmosC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);



	ENA.GPIO_Pin=GPIO_Pin_6;
	ENA.GPIO_Mode=GPIO_Mode_OUT;
	ENA.GPIO_OType=GPIO_OType_PP;
	ENA.GPIO_PuPd=GPIO_PuPd_NOPULL;
	ENA.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&ENA);
	//GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);

	ENB.GPIO_Pin=GPIO_Pin_7;
	ENB.GPIO_Mode=GPIO_Mode_OUT;
	ENB.GPIO_OType=GPIO_OType_PP;
	ENB.GPIO_PuPd=GPIO_PuPd_NOPULL;
	ENB.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&ENB);
	//GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);

    ENC.GPIO_Pin=GPIO_Pin_8;
    ENC.GPIO_Mode=GPIO_Mode_OUT;
    ENC.GPIO_OType=GPIO_OType_PP;
    ENC.GPIO_PuPd=GPIO_PuPd_NOPULL;
    ENC.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOC,&ENC);
    //GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);

}


void pwm_timers()
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    Timer_4.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
    Timer_4.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
    Timer_4.TIM_Period=Period;//The Top Value That is loaded to the Auto reload register.//the default value.
    Timer_4.TIM_Prescaler=42;//Prescaler is 16 bit.
    Timer_4.TIM_RepetitionCounter=0;// For Timer 1 and 8.
    TIM_TimeBaseInit(TIM4,&Timer_4);
    Timer_OUT.TIM_OCMode=TIM_OCMode_PWM1;
    Timer_OUT.TIM_OCPolarity=TIM_OCPolarity_High;
    Timer_OUT.TIM_OutputState=TIM_OutputState_Enable;
    Timer_OUT.TIM_Pulse=0;
    TIM_OC2Init(TIM4,&Timer_OUT);
    TIM_OC3Init(TIM4,&Timer_OUT);
    TIM_OC4Init(TIM4,&Timer_OUT);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//enable the corresponding preload register by setting the
    //OCxPE bit in the TIMx_CCMRx register
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4,ENABLE);//setting the ARPE bit in the TIMx_CR1 register.
    TIM_Cmd(TIM4,ENABLE);//Starting the clock
    TIM_SetCounter(TIM4,0);

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//    Timer_3.TIM_ClockDivision=TIM_CKD_DIV1;//No Clock Division.
//    Timer_3.TIM_CounterMode=TIM_CounterMode_Up;//Upcounting Mode
//    Timer_3.TIM_Period=Period;//The Top Value That is loaded to the Auto reload register.//the default value.
//    Timer_3.TIM_Prescaler=42;//Prescaler is 16 bit.
//    Timer_3.TIM_RepetitionCounter=0;// For Timer 1 and 8.
//    TIM_TimeBaseInit(TIM3,&Timer_3);
//    Timer_OUT1.TIM_OCMode=TIM_OCMode_PWM1;
//    Timer_OUT1.TIM_OCPolarity=TIM_OCPolarity_High;
//    Timer_OUT1.TIM_OutputState=TIM_OutputState_Enable;
//    Timer_OUT1.TIM_Pulse=0;
//    TIM_OC1Init(TIM3,&Timer_OUT);
//    TIM_OC2Init(TIM3,&Timer_OUT);
//    TIM_OC3Init(TIM3,&Timer_OUT);
//    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//enable the corresponding preload register by setting the
//    //OCxPE bit in the TIMx_CCMRx register
//    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
//    TIM_ARRPreloadConfig(TIM3,ENABLE);//setting the ARPE bit in the TIMx_CR1 register.
//    TIM_Cmd(TIM3,ENABLE);//Starting the clock
//    TIM_SetCounter(TIM3,0);
}

void Stop()
{
	TIM4->CCR2=0; //QH1
	TIM4->CCR3=0; //QH2
	TIM4->CCR4=0; //QH3
	GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,0); //QL1
	GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,0); //QL2
	GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,0); //QL3
}

volatile int Hall_Values()
 {

	return ((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))+(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)*2)+(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)*4));
 //Bases are 1,2 and 4.

 }




void Check_Hall_Pwm(volatile int HallValues)
{


    switch(HallValues)
    {

      case(0):
      {
        Stop();
        break;
      }
      /*
       * Hall1=1,Hall2=1,Hall3=0, with bases 3
       * Means A-Float,B-High_Side,C-Low_Side
       */
      case(3):
      {
    	  TIM4->CCR2=0; //QH1
    	  TIM4->CCR3=pwm_value; //QH2
    	  TIM4->CCR4=0; //QH3
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,0); //QL1
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,0); //QL2
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,1); //QL3
    	  break;
      }

      /*
       * Hall1=0,Hall2=1,Hall3=0, with bases 2
       * Means A-Low_Side,B-High_Side,C-float
       */
       case(2):
       {
    	   TIM4->CCR2=0; //QH1
    	   TIM4->CCR3=pwm_value; //QH2
    	   TIM4->CCR4=0; //QH3
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,1); //QL1
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,0); //QL2
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,0); //QL3
    	   break;

       }

       /*
       * Hall1=0,Hall2=1,Hall3=1, with bases 6
       * Means A-Low_Side,B-float,C-High_Side
       */
       case(6):
       {


    	   TIM4->CCR2=0; //QH1
    	   TIM4->CCR3=0; //QH2
    	   TIM4->CCR4=pwm_value; //QH3
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,1); //QL1
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,0); //QL2
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,0); //QL3
    	   break;

       }

          /*
       * Hall1=0,Hall2=0,Hall3=1, with bases 4
       * Means A-float,B-Low_side,C-High_Side
       */
      case(4):
      {
    	  TIM4->CCR2=0; //QH1
    	  TIM4->CCR3=0; //QH2
    	  TIM4->CCR4=pwm_value; //QH3
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,0); //QL1
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,1); //QL2
    	  GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,0); //QL3
    	  break;
      }

        /*
       * Hall1=1,Hall2=0,Hall3=1, with bases 5
       * Means A-High_Side,B-Low_side,C-Float
       */

       case(5):
       {
    	   TIM4->CCR2=pwm_value; //QH1
    	   TIM4->CCR3=0; //QH2
    	   TIM4->CCR4=0; //QH3
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,0); //QL1
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,1); //QL2
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,0); //QL3
    	   break;
       }

        /*
       * Hall1=1,Hall2=0,Hall3=0, with bases 1
       * Means A-High_Side,B-float,C-Low_Side
       */

       case(1):
      {
    	   TIM4->CCR2=pwm_value; //QH1
    	   TIM4->CCR3=0; //QH2
    	   TIM4->CCR4=0; //QH3
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_6 ,0); //QL1
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_7 ,0); //QL2
    	   GPIO_WriteBit(GPIOC,GPIO_Pin_8 ,1); //QL3
    	   break;
      }


      case(7):
     {
		  Stop();
		  break;
     }


    }
}

volatile GPIO_InitTypeDef temp;

int i,j;
int main(void)
{
	Gpio_Interrupt();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	temp.GPIO_Mode=GPIO_Mode_OUT;
	temp.GPIO_OType=GPIO_OType_PP;
	temp.GPIO_Pin=GPIO_Pin_12;
	temp.GPIO_PuPd=GPIO_PuPd_NOPULL;
	temp.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&temp);

	//GPIO_SetBits(GPIOD,GPIO_Pin_12);

	Gpio_pwm();
	pwm_timers();
//	HALL_TEST_init();
//	HALL_TEST(hall);
	Check_Hall_Pwm(3);

//	GPIO_WriteBit(GPIOE,GPIO_Pin_13,1); //QL1
//	GPIO_WriteBit(GPIOE,GPIO_Pin_14,1); //QL2
//	GPIO_WriteBit(GPIOE,GPIO_Pin_15,1); //QL3
	while(1);
}
void EXTI2_IRQHandler(void)
{
   // while(EXTI_GetITStatus(EXTI_Line2) != RESET)
    //{

    	GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
    	Check_Hall_Pwm(Hall_Values());
	    EXTI_ClearITPendingBit(EXTI_Line2);
	    NVIC_ClearPendingIRQ(EXTI2_IRQn);
    //}
}

void EXTI3_IRQHandler(void)
{
    //while(EXTI_GetITStatus(EXTI_Line3) != RESET)
    //{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
		Check_Hall_Pwm(Hall_Values());
		EXTI_ClearITPendingBit(EXTI_Line3);
		NVIC_ClearPendingIRQ(EXTI3_IRQn);
    //}
}

void EXTI4_IRQHandler(void)
{
    //while(EXTI_GetITStatus(EXTI_Line4) != RESET)

    //{
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
    	Check_Hall_Pwm(Hall_Values());
    	EXTI_ClearITPendingBit(EXTI_Line4);
    	NVIC_ClearPendingIRQ(EXTI4_IRQn);
    //}
}

