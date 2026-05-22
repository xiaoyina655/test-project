#include "servo.h"

void set_servo_angle_up(uint8_t up_angle)
{
	uint16_t pulse_up;
	if (up_angle>180)
	{
		up_angle=180;
	}
	pulse_up=500+(uint16_t )((uint32_t )up_angle *2000/180);
	__HAL_TIM_SET_COMPARE (SERVO_TIM ,SERVO_CHANNEL ,pulse_up );

}
