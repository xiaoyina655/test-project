#include "moter.h"
#include "tim.h"


void moter_init(void){
	HAL_TIM_PWM_Start (PWM_TIMER_A ,PWM_CH_A );
	HAL_TIM_PWM_Start (PWM_TIMER_B ,PWM_CH_B );
	HAL_GPIO_WritePin (STBY_PORT ,STBY_PIN ,GPIO_PIN_SET );
	
	HAL_GPIO_WritePin (AIN1_PORT ,AIN1_PIN ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (AIN2_PORT ,AIN2_PIN ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (BIN1_PORT ,BIN1_PIN ,GPIO_PIN_RESET );
	HAL_GPIO_WritePin (BIN2_PORT ,BIN2_PIN ,GPIO_PIN_RESET );
	

}
void moter_a_set_speed(int8_t speed){
	uint16_t pulse;
	uint8_t forword;
	
	if(speed >MOTER_MAX_SPEED )speed = MOTER_MAX_SPEED ;
	if(speed <MOTER_MIN_SPEED )speed = MOTER_MIN_SPEED ;

	if(speed >=0){
		forword =1;
		pulse = speed*100;
	}else {
		forword =0;
		pulse = speed *100;
	
	}
	if(forword ){
		HAL_GPIO_WritePin (AIN1_PORT ,AIN1_PIN ,GPIO_PIN_SET);
		HAL_GPIO_WritePin (AIN2_PORT ,AIN2_PIN ,GPIO_PIN_RESET);
	}else {
		HAL_GPIO_WritePin (AIN1_PORT ,AIN1_PIN ,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (AIN2_PORT ,AIN2_PIN ,GPIO_PIN_SET);
	}
	__HAL_TIM_SET_COMPARE (PWM_TIMER_A ,PWM_CH_A ,pulse );
	
}
void moter_b_set_speed(int8_t speed){
	uint16_t pulse;
	uint8_t forword;
	
	if(speed >MOTER_MAX_SPEED )speed = MOTER_MAX_SPEED ;
	if(speed <MOTER_MIN_SPEED )speed = MOTER_MIN_SPEED ;

	if(speed >=0){
		forword =1;
		pulse = speed*100;
	}else {
		forword =0;
		pulse = speed *100;
	
	}
	if(forword ){
		HAL_GPIO_WritePin (BIN1_PORT ,BIN1_PIN ,GPIO_PIN_SET);
		HAL_GPIO_WritePin (BIN2_PORT ,BIN2_PIN ,GPIO_PIN_RESET);
	}else {
		HAL_GPIO_WritePin (BIN1_PORT ,BIN1_PIN ,GPIO_PIN_RESET);
		HAL_GPIO_WritePin (BIN2_PORT ,BIN2_PIN ,GPIO_PIN_SET);
	}
	__HAL_TIM_SET_COMPARE (PWM_TIMER_B ,PWM_CH_B ,pulse );
	
}
void moter_stop(void){
	moter_a_set_speed(0);
}



