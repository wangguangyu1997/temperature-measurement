#include "timer.h"
#include "led.h"
#include "pwm.h"

TIM_HandleTypeDef TIM4_Handler; 
TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM2_Handler; 
TIM_Encoder_InitTypeDef TIM4_Encoder_Handler;
TIM_HandleTypeDef TIM7_Handler;
extern u32 ccc ;
extern u8 biao ;
//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)（90hz）
void TIM3_Init(u16 arr,u16 psc)
{  
  __HAL_RCC_TIM3_CLK_ENABLE(); 
 	TIM3->ARR=arr;  	//设定计数器自动重装值 
	TIM3->PSC=psc;  	//预分频器	 
  TIM3->SR &=(~(1<<0));  	
	TIM3->DIER|=1<<0;   //允许更新中断	

	TIM3->CR1|=0x01;    //使能定时器3
  
            //使能TIM10时钟
	HAL_NVIC_SetPriority(TIM3_IRQn,1,4);    //设置中断优先级，抢占优先级1，子优先级3
	HAL_NVIC_EnableIRQ(TIM3_IRQn); 
	  
}

void TIM7_Init(u16 arr,u16 psc)
{  
  __HAL_RCC_TIM7_CLK_ENABLE(); 
 	TIM7->ARR=arr;  	//设定计数器自动重装值 
	TIM7->PSC=psc;  	//预分频器	 
  TIM7->SR &=(~(1<<0));  	
	TIM7->DIER|=1<<0;   //允许更新中断	

	TIM7->CR1|=0x01;    //使能定时器3
  
            //使能TIM10时钟
	HAL_NVIC_SetPriority(TIM7_IRQn,1,6);    //设置中断优先级，抢占优先级1，子优先级3
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

	
}



void TIM2_Init(u16 arr,u16 psc)
{  
  __HAL_RCC_TIM2_CLK_ENABLE(); 
 	TIM2->ARR=arr;  	//设定计数器自动重装值 
	TIM2->PSC=psc;  	//预分频器	 
  TIM2->SR &=(~(1<<0));  	
	TIM2->DIER|=1<<0;   //允许更新中断	

	TIM2->CR1|=0x01;    //使能定时器3
  
            //使能TIM10时钟
	HAL_NVIC_SetPriority(TIM2_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
void TIM4_Encoder_Configration(u16 arr,u16 psc)
{   
		TIM4_Handler.Instance=TIM4;
		TIM4_Handler.Init.Prescaler=psc;    
		TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;   
		TIM4_Handler.Init.Period=arr;                        
		TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		//HAL_TIM_Base_Init(&TIM4_Handler);//HAL_TIM_OC_Init(&TIM4_Handler);



		TIM4_Encoder_Handler.EncoderMode=TIM_ENCODERMODE_TI12;
		TIM4_Encoder_Handler.IC1Filter=0;
		TIM4_Encoder_Handler.IC1Polarity=TIM_ICPOLARITY_RISING;
		TIM4_Encoder_Handler.IC1Prescaler=TIM_ICPSC_DIV1;
		TIM4_Encoder_Handler.IC1Selection=TIM_ICSELECTION_DIRECTTI;


		TIM4_Encoder_Handler.IC2Filter=0;
		TIM4_Encoder_Handler.IC2Polarity=TIM_ICPOLARITY_RISING;
		TIM4_Encoder_Handler.IC2Selection=TIM_ICSELECTION_DIRECTTI;
		TIM4_Encoder_Handler.IC2Prescaler=TIM_ICPSC_DIV1;
		HAL_TIM_Encoder_Init(&TIM4_Handler,&TIM4_Encoder_Handler);

		HAL_TIM_Encoder_Start(&TIM4_Handler,TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start_IT(&TIM4_Handler,TIM_CHANNEL_ALL);//????
		TIM4->CNT=0;
		__HAL_TIM_ENABLE_IT(&TIM4_Handler,TIM_IT_UPDATE);   //?????????????????????
			//__HAL_TIM_ENABLE(&TIM4_Handler);
		
}



//编码器模式使用的定时器
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{   
GPIO_InitTypeDef GPIO_Initure;
if(htim->Instance==TIM4)
  {
    __HAL_RCC_GPIOD_CLK_ENABLE(); 
    __HAL_RCC_TIM4_CLK_ENABLE();           
    GPIO_Initure.Pin=GPIO_PIN_12|GPIO_PIN_13;            
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;     
    GPIO_Initure.Pull=GPIO_PULLUP;         
    GPIO_Initure.Alternate=GPIO_AF2_TIM4;   
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

    HAL_NVIC_SetPriority(TIM4_IRQn,1,5);   
    HAL_NVIC_EnableIRQ(TIM4_IRQn);          



    HAL_NVIC_EnableIRQ(TIM4_IRQn);          
    



     TIM4->CNT=0;

}

}


//定时器3中断服务函数
//人来了
void TIM3_IRQHandler(void)
{
	if((TIM3->SR&0X0001)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) ==0)&&(biao == 0))//溢出中断
	{
		              //当没有到达人头的位置的时候才能开启正转，防止到我们的头到了之后，脚移动导致整体机械结构继续往下移动
		DIR_Set(1) ;//正转
		Enable_Set(0) ;//开始转动

		//下行开启了		
		biao = 1 ; 
		

		
	}else if(biao >= 2)
  {
		 TIM_SetTIM12Compare1(1000);
  }	
	 TIM3->SR&=~(1<<0);//清除中断标志位 	   
   TIM3->CR1 &= ~(0x1<<0) ;
}

//定时器2中断服务函数
//到达人的位置了
void TIM2_IRQHandler(void)
{ 
	if((TIM2->SR&0X0001)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13) ==0)&&(biao == 1))//溢出中断
	{
		
		Enable_Set(1) ;//停止转动
		DIR_Set(0) ;//设置方向反转 
    
		
		//到达人头的位置了
		biao = 2 ;

		
		
		
	}				   
	 TIM2->SR&=~(1<<0);//清除中断标志位 	   
   TIM2->CR1 &= ~(0x1<<0) ;
}
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);
}


void TIM7_IRQHandler(void)
{
	if(TIM7->SR&0X0001)//溢出中断
	{
		TIM_SetTIM12Compare1(1000);
		LED0 = !LED0 ;
		
		//TIM7->DIER &= ~(0X1<<0); 		    				   				     	    	
	}				   
	 TIM7->SR&=~(1<<0);//清除中断标志位 	   
   TIM7->CR1 &= ~(0x1<<0) ;//关闭定时器
		
}






//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//通过中断记录向上溢出和向下溢出的次数
     if(htim==(&TIM4_Handler))
		{
				if((TIM4->CR1 &(0X10)) == (0X10))
				{
						ccc-- ;
				}
				else if((TIM4->CR1 &(0X10)) == (0X00))
				{
						ccc++ ;
				}
				
		}
		
		
		
}
