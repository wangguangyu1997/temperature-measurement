#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern TIM_HandleTypeDef TIM4_Handler; 
extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM2_Handler; 
extern TIM_Encoder_InitTypeDef TIM4_Encoder_Handler;
extern TIM_HandleTypeDef TIM5_Handler;
void TIM4_Encoder_Configration(u16 arr,u16 psc);
void TIM3_Init(u16 arr,u16 psc);
void TIM2_Init(u16 arr,u16 psc);
void TIM7_Init(u16 arr,u16 psc);
#endif

