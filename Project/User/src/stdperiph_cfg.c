/**
  ******************************************************************************
* File Name          : StdPeriph_Cfg.h
* Author              : 
* Version            : 
* Date                 : 
* Description      : 
* brief                  :periph device config
  ******************************************************************************
  * attention  :
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdperiph_cfg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEBUG_BOUND 115200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/****************************4 leds IO init************************************/
void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*enable gpioe clk*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	/*GPIOF 6 7 8 9 cgf PPout*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOE,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
}

/****************************usartx************************************/
void USARTx_Init(enum Usartx comx)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
    
	USART_InitStructure.USART_BaudRate = DEBUG_BOUND;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	switch(comx)
	{
		case usart1:
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA,&GPIO_InitStructure);	

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA,&GPIO_InitStructure);	

			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
            
			USART_Init(USART1, &USART_InitStructure); 
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			USART_Cmd(USART1, ENABLE);
			USART_ClearFlag(USART1, USART_FLAG_TC);
			break;
		}
		case usart2:
		{break;}
		case usart3:
		{break;}
		case uart4:
		{break;}
		case uart5:
		{break;}
		default:break;
	}

	  //Usart1 NVIC
    //NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		  
	NVIC_Init(&NVIC_InitStructure); 

             
}











