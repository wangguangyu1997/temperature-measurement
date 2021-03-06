#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//定时器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/6
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//修改说明
//V1.1 20160106
//新增TIM3_PWM_Init函数,用于PWM输出
////////////////////////////////////////////////////////////////////////////////// 	 

TIM_HandleTypeDef TIM9_Handler;         //定时器9PWM句柄 
TIM_OC_InitTypeDef TIM9_CH2Handler;	    //定时器9通道2句柄

TIM_HandleTypeDef TIM12_Handler;         //定时器9PWM句柄 
TIM_OC_InitTypeDef TIM12_CH1Handler;	    //定时器9通道2句柄

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM9_PWM_Init(u16 arr,u16 psc)
{ 
    TIM9_Handler.Instance=TIM9;            //定时器9
    TIM9_Handler.Init.Prescaler=psc;       //定时器分频
    TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM9_Handler.Init.Period=arr;          //自动重装载值
    TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM9_Handler);       //初始化PWM
    
    TIM9_CH2Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM9_CH2Handler.Pulse=arr/2;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM9_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM9_Handler,&TIM9_CH2Handler,TIM_CHANNEL_2);//配置TIM9通道2
	
    HAL_TIM_PWM_Start(&TIM9_Handler,TIM_CHANNEL_2);//开启PWM通道2
}
void TIM12_PWM_Init(u16 arr,u16 psc)
{ 
    TIM12_Handler.Instance=TIM12;            //定时器9
    TIM12_Handler.Init.Prescaler=psc;       //定时器分频
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM12_Handler.Init.Period=arr;          //自动重装载值
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM12_Handler);       //初始化PWM
    
    TIM12_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM12_CH1Handler.Pulse=1000;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM12_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH ; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH1Handler,TIM_CHANNEL_1);//配置TIM9通道2
	
    HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_1);//开启PWM通道2
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM9)
	{
		GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM9_CLK_ENABLE();			//使能定时器9
    __HAL_RCC_GPIOE_CLK_ENABLE();			//开启GPIOE时钟
	
    GPIO_Initure.Pin=GPIO_PIN_6;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	  GPIO_Initure.Alternate= GPIO_AF3_TIM9;	//PB1复用为TIM9_CH2
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	}
	else if(htim->Instance==TIM12)
	{
	 GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM12_CLK_ENABLE();			//使能定时器9
    __HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOE时钟
	
    GPIO_Initure.Pin=GPIO_PIN_14;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	  GPIO_Initure.Alternate= GPIO_AF9_TIM12 ;	//PB14复用为TIM9_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	}
}
	


//设置TIM通道4的占空比
//compare:比较值
void TIM_SetTIM9Compare2(u32 compare)
{
	TIM9->CCR2=compare; 
}
void TIM_SetTIM12Compare1(u32 compare)
{
	TIM12->CCR1=compare; 
}

