#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>
char data = 'a';

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;
	GP1.GPIO_Mode = GPIO_Mode_AF;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_UP;
	GP1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GP1 );
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11,GPIO_AF_USART3);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12,GPIO_AF_USART3);

	USART_InitTypeDef us3;
	us3.USART_BaudRate= 9600;
    us3.USART_WordLength = USART_WordLength_8b;
    us3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    us3.USART_Mode = USART_Mode_Tx;
    //us3.USART_Parity = USART_Parity_Even;
    us3.USART_StopBits = USART_StopBits_1;
    USART_Init(USART3, &us3);
//    USART_ClockInitTypeDef uc3;
//    uc3.USART_CPHA = USART_CPHA_2Edge;
//    uc3.USART_CPOL = USART_CPOL_High;
//    uc3.USART_Clock = USART_Clock_Enable;
//    uc3.USART_LastBit = USART_LastBit_Enable;
//    USART_ClockInit(USART3, &uc3);
    USART_Cmd(USART3, ENABLE);


    while(1)
    {
    	if(USART_GetFlagStatus(USART3, USART_FLAG_TXE)== SET)
    	{
    		USART_SendData(USART3, data);
    		USART_ClearFlag(USART3,USART_FLAG_TXE);
    	}

    }
}
