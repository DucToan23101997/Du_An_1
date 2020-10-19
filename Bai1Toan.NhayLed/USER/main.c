#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"



/************************************************
www.stm32vn.com
************************************************/
 uint8_t i ;
 int main(void)
 {	
	 LED_init();
	 delay_init();
  while(1)
	{
	    //LED0 =0;//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	    GPIO_SetBits(GPIOC,GPIO_Pin_13);
		  delay_ms(3000);
			//LED0 =1;
		  //GPIO_SetBits(GPIOC,GPIO_Pin_13);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		  delay_ms(3000);
		for(i = 0 ; i <5 ; i++)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
		  delay_ms(300);
			//LED0 =1;
		  //GPIO_SetBits(GPIOC,GPIO_Pin_13);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		  delay_ms(300);
		}
	}
 }