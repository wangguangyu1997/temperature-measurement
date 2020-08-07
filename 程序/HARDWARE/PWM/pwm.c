#include "pwm.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/6
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//�޸�˵��
//V1.1 20160106
//����TIM3_PWM_Init����,����PWM���
////////////////////////////////////////////////////////////////////////////////// 	 

TIM_HandleTypeDef TIM9_Handler;         //��ʱ��9PWM��� 
TIM_OC_InitTypeDef TIM9_CH2Handler;	    //��ʱ��9ͨ��2���

TIM_HandleTypeDef TIM12_Handler;         //��ʱ��9PWM��� 
TIM_OC_InitTypeDef TIM12_CH1Handler;	    //��ʱ��9ͨ��2���

//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM9_PWM_Init(u16 arr,u16 psc)
{ 
    TIM9_Handler.Instance=TIM9;            //��ʱ��9
    TIM9_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM9_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM9_Handler);       //��ʼ��PWM
    
    TIM9_CH2Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM9_CH2Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM9_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM9_Handler,&TIM9_CH2Handler,TIM_CHANNEL_2);//����TIM9ͨ��2
	
    HAL_TIM_PWM_Start(&TIM9_Handler,TIM_CHANNEL_2);//����PWMͨ��2
}
void TIM12_PWM_Init(u16 arr,u16 psc)
{ 
    TIM12_Handler.Instance=TIM12;            //��ʱ��9
    TIM12_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM12_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM12_Handler);       //��ʼ��PWM
    
    TIM12_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM12_CH1Handler.Pulse=1000;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM12_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH ; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH1Handler,TIM_CHANNEL_1);//����TIM9ͨ��2
	
    HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_1);//����PWMͨ��2
}

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM9)
	{
		GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM9_CLK_ENABLE();			//ʹ�ܶ�ʱ��9
    __HAL_RCC_GPIOE_CLK_ENABLE();			//����GPIOEʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_6;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	  GPIO_Initure.Alternate= GPIO_AF3_TIM9;	//PB1����ΪTIM9_CH2
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	}
	else if(htim->Instance==TIM12)
	{
	 GPIO_InitTypeDef GPIO_Initure;
	  __HAL_RCC_TIM12_CLK_ENABLE();			//ʹ�ܶ�ʱ��9
    __HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOEʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_14;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	  GPIO_Initure.Alternate= GPIO_AF9_TIM12 ;	//PB14����ΪTIM9_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	}
}
	


//����TIMͨ��4��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM9Compare2(u32 compare)
{
	TIM9->CCR2=compare; 
}
void TIM_SetTIM12Compare1(u32 compare)
{
	TIM12->CCR1=compare; 
}

