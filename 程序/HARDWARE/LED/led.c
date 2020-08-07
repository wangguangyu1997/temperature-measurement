#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/5
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//初始化PB1为输出.并使能时钟	    
//LED IO初始化
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
		
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //PB1,0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0置1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB1置1  
}

void MOTOR_Init(void)
{
		GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();           //开启GPIOE时钟
//低电平	
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_3; //
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLDOWN;          //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
//高电平
	  GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_5; //PE2
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP ;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);

//低电平
	
	

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);	//PE4置0 
	  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
//高电平

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);	//PE5置
}
void DIR_Set(u8 dir)
{
		if(dir == 0)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);	//正转PE4置0 
		}
		else if(dir == 1)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);	//反转（PE4为1）
		}
}

void	Enable_Set(u8 enable)
{
		if(enable == 0)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);	//（使能驱动板）PE3置0 
		}
		else if(enable == 1)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);	//（不使能驱动板）PE3置1
		}

}

