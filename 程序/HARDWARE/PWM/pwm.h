#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32429������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:201/1/6
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
extern TIM_HandleTypeDef TIM9_Handler;      //��ʱ��9PWM��� 
extern TIM_OC_InitTypeDef TIM9_CH2Handler;	  //��ʱ��9ͨ��2���
extern TIM_HandleTypeDef TIM12_Handler;         //��ʱ��9PWM��� 
extern TIM_OC_InitTypeDef TIM12_CH1Handler;	    //��ʱ��9ͨ��2���

void TIM9_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM9Compare2(u32 compare);
void TIM12_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM12Compare1(u32 compare);
#endif

