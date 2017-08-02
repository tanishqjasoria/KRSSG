#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>
uint16_t data_send = (uint16_t) '0';

void usart3_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GP1.GPIO_Mode = GPIO_Mode_AF;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_UP;
	GP1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GP1 );
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10,GPIO_AF_USART3);     	//TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11,GPIO_AF_USART3);		//RX
	USART_InitTypeDef us3;
	us3.USART_BaudRate= 9600;
    us3.USART_WordLength = USART_WordLength_8b;
    us3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    us3.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//    us3.USART_Parity = USART_Parity_Even;
    us3.USART_StopBits = USART_StopBits_1;
    USART_Init(USART3, &us3);
    USART_Cmd(USART3, ENABLE);

}
void usart3_clockinit()
{
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12,GPIO_AF_USART3);		//CLK
    USART_ClockInitTypeDef uc3;
    uc3.USART_CPHA = USART_CPHA_2Edge;
    uc3.USART_CPOL = USART_CPOL_High;
    uc3.USART_Clock = USART_Clock_Enable;
    uc3.USART_LastBit = USART_LastBit_Enable;
    USART_ClockInit(USART3, &uc3);
    USART_Cmd(USART3, ENABLE);
}
void gpiod_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GP1;
	GP1.GPIO_Pin = GPIO_Pin_All;
	GP1.GPIO_Mode = GPIO_Mode_OUT;
	GP1.GPIO_OType = GPIO_OType_PP;
	GP1.GPIO_PuPd = GPIO_PuPd_DOWN;
	GP1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD ,&GP1 );
}
void usart_sendData(uint16_t a)
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE)== RESET);
	USART_SendData(USART3, a);
 	USART_ClearFlag(USART3,USART_FLAG_TXE);
}
uint16_t usart_rec_Data()
{
	uint16_t data;
    while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)== RESET);
    data = USART_ReceiveData(USART3);
 	USART_ClearFlag(USART3,USART_FLAG_RXNE);
 	return data;

}
int main(void)
{
	usart3_init();
	gpiod_init();
	uint16_t data;

    while(1)
    {
//    	usart_sendData(data_send);
    	data = usart_rec_Data();
    	if(data=='a')
    	{
    		GPIO_SetBits(GPIOD, GPIO_Pin_13);
    	}
    	else
    	{
    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    	}
    }

}

