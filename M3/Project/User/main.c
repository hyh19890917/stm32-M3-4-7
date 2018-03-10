/**
  ******************************************************************************
  * @file  main.c 
  * @author  
  * @version V3.5.0
  * @date   
  * @brief   Main program body
  ******************************************************************************
  * @attention
  ******************************************************************************
  */  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stdperiph_cfg.h"
#include "i2c_ee.h"
#include <stdio.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
u8 i2c_buff_read[256]={0};
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/
void delay(int n)
{
    while(n--) ;
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
ErrorStatus I2C_EE_Test(u8 test_start_addr,u8 test_cnt)
{
	u8 temp_addr= test_start_addr;
	for(u16 i=0;i<test_cnt;i++)
	{
		I2C_EE_ByteWrite((u8*)&i, temp_addr);
		I2C_EE_WaitEepromStandbyState();
		//printf("write date %i into addr %#x\n",i,temp_addr);
		temp_addr ++;
	}
	printf("test eeprom write---ok!\n");
	temp_addr = 0x10;
	u8 * temp_read = i2c_buff_read;
	for (u16 i= 0;i<10; i++)
		{
			I2C_EE_ByteRead(temp_read, temp_addr);
			i2c_buff_read[i] = *temp_read;
			//printf("read date of addr %#x is %d \n",temp_addr,i2c_buff_read[i]);
			temp_addr ++;
		}
	printf("test eeprom read--ok!\n");
	return SUCCESS;
	
}
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
	USARTx_Init(usart1);
	LED_GPIO_Init();
	I2C_EE_Init();
	printf("Hello MCU!\n");
//I2C_Test();
  /* Add your application code here
     */
//	if(I2C_EE_Test(0x10,3) == SUCCESS)
//	{
//		printf("eeprom test succees!");
//	}

  /* Infinite loop */
	while (1)
	{
	}
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */

	//USART_ClearFlag(USART1, USART_FLAG_TC);
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  
  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/*
	u8 cnt = 9;
	u8 ddr= PARA1_addr;
	while(cnt)
	{
		I2C_EE_ByteWrite(&i2c_buff_write[9-cnt],ddr );
		//I2C_EE_BufferWrite(&i2c_buff_write[9-cnt],ddr,1 );
		I2C_EE_WaitEepromStandbyState();
		ddr ++;
		cnt --;
	}

	//I2C_EE_BufferWrite(i2c_buff_write, PARA1_addr,2);
	I2C_EE_BufferRead(i2c_buff_read,0x00, 15);
	
	while(15 > cnt)
	{
		printf("para1_date%d=%#x\n",cnt+1,i2c_buff_read[cnt]);
		cnt ++;
	}
	u8 * readd_dr = &i2c_buff_read[16];
	
	I2C_EE_ByteRead(readd_dr,0x01);
	printf("%#x\n",*readd_dr);
	for(int i=0;i<10;i++)
{
	I2C_EE_ByteRead(readd_dr,ddr);
	//I2C_EE_BufferRead(&i2c_buff_read[16], 0x10,1);
	printf("%#x\n",*readd_dr);
	readd_dr ++;
	ddr ++;
}

*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
