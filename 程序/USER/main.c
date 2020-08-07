#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "exti.h"
#include "key.h"
#include "mlx90614.h"
#include "lcd.h"
#include "sdram.h"
#include "malloc.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "string.h"
#include "sdio_sdcard.h"
#include "fontupd.h"
#include "text.h"
#include "rtc.h"
#include "tmp.h"
#include "timer.h"
#include "pwm.h"
//0x5aID
//0x06室温
u32 ccc = 9 ;//当前圈加10
u32 cc = 0 ;//定时器当前的脉冲数
u32 c = 0 ;//总的脉冲
u8 biao = 0 ;

int main(void)
{
		RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    u8 tbuf[45];
	  u8 tmp[12];
		float temp =0;
    HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(9600);              //初始化USART
    LED_Init();
	
	//电机
	
		MOTOR_Init();
	  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);	//PE5置
		Enable_Set(1) ; //刚开始的时候电机不转
	  TIM9_PWM_Init(20000-1,90-1) ;
    TIM12_PWM_Init(20000-1,90-1);//45°
  
	
	
	
	
	
    EXTI_Init();  
		TIM4_Encoder_Configration(4800-1,0) ;
    MLX90614init();	
	  SDRAM_Init(); 
	  LCD_Init();	 
    RTC_Init();  	
    W25QXX_Init();				    //初始化W25Q256
    my_mem_init(SRAMIN);            //初始化内部内存池
    my_mem_init(SRAMEX);            //初始化外部SDRAM内存池
    my_mem_init(SRAMCCM);           //初始化内部CCM内存池
    exfuns_init();	
    f_mount(fs[1],"1:",1);          //挂载SPI FLASH.  	//为fatfs相关变量申请内存  	//初始化LCD 
    font_init();
		POINT_COLOR=RED; 
	    //初始化的时候多定义几个初始化前的脉冲
		Show_Str(50,30,200,32,"当前测量温度为：",32,0);
		Show_Str(50,110,200,32,"室温为：",32,0);
		Show_Str(50,190,200,32,"当前日期为：",32,0);
		Show_Str(50,270,200,32,"当前时间为：",32,0);
    while(1)
    {
		  	cc = TIM4->CNT ;//定时器当前的脉冲数
			

	//		 TIM_SetTIM12Compare1(1000);
	//     delay_ms(1000) ;
	//		 TIM_SetTIM12Compare1(2000);
			 
		if(biao == 2)//到达人的位置了
			{
				printf("请将额头对准探头");
				//发声讲话请将额头对准测量探头
				delay_ms(4000);//等待人把头伸过来
			
			//人头伸过来了测量体温程序
	   
				temp= MLX90614_ReadTemp(0x5a,0x07);
	  		tmp_to_string(temp,tmp);
				LCD_ShowString(50,70,240,12,32,tmp);
       
			// 温度语音通知
			  tmp_to_printf(temp,tmp) ;
				printf("您的体温为"); 
			  printf("%d",(int)temp/10);
			  printf("十");
		    printf("%s",tmp); 
				printf("摄氏度"); 
			  if(temp<37)
				{
				 TIM_SetTIM12Compare1(2000);
				 TIM3_Init(50000-1,4000-1);
				 }
				if(temp>=37)
				{
						HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET);
					  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);
				}
				//发声测量完成，您的体温为。。。，祝您身体健康，万事如意
				//检测温度判断，当温度比较高的时候控制蜂鸣器报警，屏幕显示底色变为红色，舵机不开启。
				//检测温度判断，温度正常，舵机开启。
				//电机开始反转复位到原来的位置，这里可以设置一个定时器，在定时器计时结束的时候让电机开始反转。
			                    //这个定时器是500ms
				delay_ms(2000);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
				delay_ms(2000);
				DIR_Set(0) ;//设置方向反转    
		    Enable_Set(0) ;
	    	LED0 = !LED0 ;
				//测量完体温之后
				
				
				//进入上行阶段
				biao = 3 ; 
				

                   				//清除到人头的标志位
        
			}
			if (c < 48000) //回到我原来的位置了
			{                  //PE4为1，PE3为0 ；（当前正在反转）
				 if(    (((( GPIOE->ODR ) >> 4) & (0X01)) == 0) && (((( GPIOE->ODR ) >> 3) & (0X01)) == 0) &&(biao == 3) )
				 {
					 Enable_Set(1) ; //这里加一个判断，如果现在电机正在反转并且电机驱动板已经使能了//这里的判断是防止最开始的时候由于整体的脉冲比较少，无法启动
				                   // 停止转动，位置复位。
					 biao = 0 ;
				 }					 
			}
				
			
				//室温检测
		   temp= MLX90614_ReadTemp(0x5a,0x06);
	     tmp_to_string(temp,tmp);
  	   LCD_ShowString(50,150,240,12,32,tmp);
			
			  //当前时间
				HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
			  sprintf((char*)tbuf,"%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
				Show_Str(50,310,210,32,tbuf,32,0);
        HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
		  	sprintf((char*)tbuf,"20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date); 
		  	Show_Str(50,230,210,32,tbuf,32,0);
			
			
			  //当前的总脉冲计算
			  c = cc + ccc*4800 ;
				LCD_ShowNum(10,340,cc,32,32);
			  LCD_ShowNum(10,380,ccc,32,32);
				LCD_ShowNum(10,420,c,32,32);
				LCD_ShowNum(10,500,biao,32,32);
				
			
        delay_ms(10);            
    }
}



	 
	
   
