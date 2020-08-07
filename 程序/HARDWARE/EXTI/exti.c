#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//�ⲿ�жϳ�ʼ��

void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
    GPIO_Initure.Pin=GPIO_PIN_9;                //PB9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_13;               //PB13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
	  GPIO_Initure.Pin=GPIO_PIN_1;                //PC1
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;      //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
		GPIO_Initure.Pin=GPIO_PIN_4;                //PC4
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
	
    //�ж���9-PB9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���9
      
    
    //�ж���13-PB13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,1);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  
		
		
/*    //�ж���1-PC1
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);             //ʹ���ж���1
		
		//�ж���4-PC4
    HAL_NVIC_SetPriority(EXTI1_IRQn,2,3);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);             //ʹ���ж���4
	*/	
		
}


//�жϷ�����
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);//�����жϴ����ú���
}



void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);//�����жϴ����ú���
}

void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);//�����жϴ����ú���
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);//�����жϴ����ú���
}



//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
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
