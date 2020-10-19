#include "LED.h"
#include "sys.h" 

void LED_init(void){
	
// GPIO_InitTypeDef  GPIO_InitStructure;
//	 
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|
//  RCC_APB2Periph_GPIOE, ENABLE);	    //PB,PE
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			    //LED0-->PB.5 
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    	 
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);			     //GPIOB.5   // khoi tao 
	GPIO_Set(GPIOC,GPIO_Pin_13,GPIO_Mode_Out_PP , GPIO_Speed_50MHz );
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);					//PB.5 =0
	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //LED1-->PE.5
//  GPIO_Init(GPIOE, &GPIO_InitStructure);	  	       
//  GPIO_ResetBits(GPIOE,GPIO_Pin_5); 			 //PE.5 =0  
}