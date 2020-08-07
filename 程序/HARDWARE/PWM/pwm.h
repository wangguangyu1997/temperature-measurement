#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32429开发板
//定时器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:201/1/6
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
extern TIM_HandleTypeDef TIM9_Handler;      //定时器9PWM句柄 
extern TIM_OC_InitTypeDef TIM9_CH2Handler;	  //定时器9通道2句柄
extern TIM_HandleTypeDef TIM12_Handler;         //定时器9PWM句柄 
extern TIM_OC_InitTypeDef TIM12_CH1Handler;	    //定时器9通道2句柄

void TIM9_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM9Compare2(u32 compare);
void TIM12_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM12Compare1(u32 compare);
#endif

