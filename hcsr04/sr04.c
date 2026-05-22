#include "SR04.h"
#include "oled.h"

//使用此库时，需要安装OLED库！

//使用PA0引脚1进行高低电平输出（可改

//定时器1的PA8进行捕获（可改

//主频为72

float distance;

#pragma O0
void Delay_us(uint32_t us)
{
    volatile uint32_t n = us * 8; 
    while(n--);
}
#pragma O2

void Send_Ultrasonic()//发送超声波
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);//引脚电平拉高持续至少10us以上，这里我延时12us
	Delay_us(12);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);//引脚电平拉低
	
}



uint16_t Ultrasonic()//超声波处理函数
{
	__HAL_TIM_SET_COUNTER(&htim3,0);//设置定时器计数值
	
	__HAL_TIM_CLEAR_FLAG(&htim3,TIM_FLAG_CC1);//清除cc1标志位
	__HAL_TIM_CLEAR_FLAG(&htim3,TIM_FLAG_CC2);//清除cc2标志位
	
	HAL_TIM_IC_Start(&htim3,TIM_CHANNEL_1);//使能输入捕获通道一
	HAL_TIM_IC_Start(&htim3,TIM_CHANNEL_2);//使能输入捕获通道二
	
	Send_Ultrasonic();//发送超声波
	
	uint8_t Success = 0;//设置是否成功标志位
	uint32_t Timeout = HAL_GetTick() + 20;//延时20ms
	
	while(Timeout > HAL_GetTick())
	{
		uint32_t ccr1Flag = __HAL_TIM_GET_FLAG(&htim1,TIM_FLAG_CC1);//获取cc1标志位状态
		uint32_t ccr2Flag = __HAL_TIM_GET_FLAG(&htim1,TIM_FLAG_CC2);//获取cc2标志位状态
		
		if(ccr1Flag && ccr2Flag)//同时为1时候
		{
			Success = 1;//表示成功置1
			break;
		}
		
		 
	}
	
	HAL_TIM_IC_Stop(&htim3,TIM_CHANNEL_1);//停止通道1输入捕获
	HAL_TIM_IC_Stop(&htim3,TIM_CHANNEL_2);//停止通道2输入捕获
	
	if(Success == 1)//如果成功
	{
		
		uint32_t ccr1 = __HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_1);//获取计数值，即上升沿采集的值
		uint32_t ccr2 = __HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_2);//获取计数值，即下降沿采集的值
		
		distance = (ccr2 - ccr1)*0.017;//带入公式
		
	}
	
	return distance;//返回距离
	
	
}


void SR04()
{
		Ultrasonic(); 
	
		OLED_ShowString(0, 0, (unsigned char*)"Distance: ", 16);
 if (distance >= 0.0f && distance < 1000.0f) 
    {

        uint16_t int_part = (uint16_t)distance;       
        uint16_t dec_part = (uint16_t)((distance - int_part) * 100);  

				OLED_ShowString(0, 0, (unsigned char*)"Distance: ", 16);
        OLED_ShowNum(72, 0, int_part, 3, 16);
        OLED_ShowChar(96, 0, '.', 16, 1);
        OLED_ShowNum(104, 0, dec_part, 2, 16);
        OLED_ShowString(120, 0, (unsigned char*)"cm", 16);
    }
    else
    {
   
        OLED_ShowString(72, 0, (unsigned char*)"Error", 16);
    }
		
		OLED_Refresh_Gram();
		
		//如果芯片卡顿死机，请解除下面的注释
//			HAL_Delay(100);    
		
}

