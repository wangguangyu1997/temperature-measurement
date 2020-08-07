#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//外部中断驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/5
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//外部中断初始化

void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
    GPIO_Initure.Pin=GPIO_PIN_9;                //PB9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_13;               //PB13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
	  GPIO_Initure.Pin=GPIO_PIN_1;                //PC1
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
		GPIO_Initure.Pin=GPIO_PIN_4;                //PC4
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
	
    //中断线9-PB9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //使能中断线9
      
    
    //中断线13-PB13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,1);   //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //使能中断线13  
		
		
/*    //中断线1-PC1
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);             //使能中断线1
		
		//中断线4-PC4
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,3);       //抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);             //使能中断线4
	*/	
		
}


//中断服务函数
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);//调用中断处理公用函数
}



void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);//调用中断处理公用函数
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);//调用中断处理公用函数
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);//调用中断处理公用函数
}



//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
        case GPIO_PIN_9:
            TIM3_Init(5000-1,9000-1);
            break;

        case GPIO_PIN_13:
            TIM2_Init(10000-1,9000-1);
            break;
				
				case GPIO_PIN_1:
            break;
				
				case GPIO_PIN_4:
            break;
				
    }
}
