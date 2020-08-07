#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PB1Ϊ���.��ʹ��ʱ��	    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOBʱ��
		
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; //PB1,0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0��1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB1��1  
}

void MOTOR_Init(void)
{
		GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();           //����GPIOEʱ��
//�͵�ƽ	
    GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_3; //
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLDOWN;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
//�ߵ�ƽ
	  GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_5; //PE2
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP ;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);

//�͵�ƽ
	
	

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);	//PE4��0 
	  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
//�ߵ�ƽ

    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);	//PE5��
}
void DIR_Set(u8 dir)
{
		if(dir == 0)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);	//��תPE4��0 
		}
		else if(dir == 1)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET);	//��ת��PE4Ϊ1��
		}
}

void	Enable_Set(u8 enable)
{
		if(enable == 0)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);	//��ʹ�������壩PE3��0 
		}
		else if(enable == 1)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);	//����ʹ�������壩PE3��1
		}

}

