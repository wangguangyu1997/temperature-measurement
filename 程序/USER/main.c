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
//0x06����
u32 ccc = 9 ;//��ǰȦ��10
u32 cc = 0 ;//��ʱ����ǰ��������
u32 c = 0 ;//�ܵ�����
u8 biao = 0 ;

int main(void)
{
		RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    u8 tbuf[45];
	  u8 tmp[12];
		float temp =0;
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(9600);              //��ʼ��USART
    LED_Init();
	
	//���
	
		MOTOR_Init();
	  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);	//PE5��
		Enable_Set(1) ; //�տ�ʼ��ʱ������ת
	  TIM9_PWM_Init(20000-1,90-1) ;
    TIM12_PWM_Init(20000-1,90-1);//45��
  
	
	
	
	
	
    EXTI_Init();  
		TIM4_Encoder_Configration(4800-1,0) ;
    MLX90614init();	
	  SDRAM_Init(); 
	  LCD_Init();	 
    RTC_Init();  	
    W25QXX_Init();				    //��ʼ��W25Q256
    my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);            //��ʼ���ⲿSDRAM�ڴ��
    my_mem_init(SRAMCCM);           //��ʼ���ڲ�CCM�ڴ��
    exfuns_init();	
    f_mount(fs[1],"1:",1);          //����SPI FLASH.  	//Ϊfatfs��ر��������ڴ�  	//��ʼ��LCD 
    font_init();
		POINT_COLOR=RED; 
	    //��ʼ����ʱ��ඨ�弸����ʼ��ǰ������
		Show_Str(50,30,200,32,"��ǰ�����¶�Ϊ��",32,0);
		Show_Str(50,110,200,32,"����Ϊ��",32,0);
		Show_Str(50,190,200,32,"��ǰ����Ϊ��",32,0);
		Show_Str(50,270,200,32,"��ǰʱ��Ϊ��",32,0);
    while(1)
    {
		  	cc = TIM4->CNT ;//��ʱ����ǰ��������
			

	//		 TIM_SetTIM12Compare1(1000);
	//     delay_ms(1000) ;
	//		 TIM_SetTIM12Compare1(2000);
			 
		if(biao == 2)//�����˵�λ����
			{
				printf("�뽫��ͷ��׼̽ͷ");
				//���������뽫��ͷ��׼����̽ͷ
				delay_ms(4000);//�ȴ��˰�ͷ�����
			
			//��ͷ������˲������³���
	   
				temp= MLX90614_ReadTemp(0x5a,0x07);
	  		tmp_to_string(temp,tmp);
				LCD_ShowString(50,70,240,12,32,tmp);
       
			// �¶�����֪ͨ
			  tmp_to_printf(temp,tmp) ;
				printf("��������Ϊ"); 
			  printf("%d",(int)temp/10);
			  printf("ʮ");
		    printf("%s",tmp); 
				printf("���϶�"); 
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
				//����������ɣ���������Ϊ��������ף�����彡������������
				//����¶��жϣ����¶ȱȽϸߵ�ʱ����Ʒ�������������Ļ��ʾ��ɫ��Ϊ��ɫ�������������
				//����¶��жϣ��¶����������������
				//�����ʼ��ת��λ��ԭ����λ�ã������������һ����ʱ�����ڶ�ʱ����ʱ������ʱ���õ����ʼ��ת��
			                    //�����ʱ����500ms
				delay_ms(2000);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
				delay_ms(2000);
				DIR_Set(0) ;//���÷���ת    
		    Enable_Set(0) ;
	    	LED0 = !LED0 ;
				//����������֮��
				
				
				//�������н׶�
				biao = 3 ; 
				

                   				//�������ͷ�ı�־λ
        
			}
			if (c < 48000) //�ص���ԭ����λ����
			{                  //PE4Ϊ1��PE3Ϊ0 ������ǰ���ڷ�ת��
				 if(    (((( GPIOE->ODR ) >> 4) & (0X01)) == 0) && (((( GPIOE->ODR ) >> 3) & (0X01)) == 0) &&(biao == 3) )
				 {
					 Enable_Set(1) ; //�����һ���жϣ�������ڵ�����ڷ�ת���ҵ���������Ѿ�ʹ����//������ж��Ƿ�ֹ�ʼ��ʱ���������������Ƚ��٣��޷�����
				                   // ֹͣת����λ�ø�λ��
					 biao = 0 ;
				 }					 
			}
				
			
				//���¼��
		   temp= MLX90614_ReadTemp(0x5a,0x06);
	     tmp_to_string(temp,tmp);
  	   LCD_ShowString(50,150,240,12,32,tmp);
			
			  //��ǰʱ��
				HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN);
			  sprintf((char*)tbuf,"%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
				Show_Str(50,310,210,32,tbuf,32,0);
        HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
		  	sprintf((char*)tbuf,"20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date); 
		  	Show_Str(50,230,210,32,tbuf,32,0);
			
			
			  //��ǰ�����������
			  c = cc + ccc*4800 ;
				LCD_ShowNum(10,340,cc,32,32);
			  LCD_ShowNum(10,380,ccc,32,32);
				LCD_ShowNum(10,420,c,32,32);
				LCD_ShowNum(10,500,biao,32,32);
				
			
        delay_ms(10);            
    }
}



	 
	
   
