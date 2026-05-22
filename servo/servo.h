#ifndef __SERVO_H
#define __SERVO_H

#include "main.h"
#include "tim.h"

#define SERVO_TIM     &htim1
#define SERVO_CHANNEL TIM_CHANNEL_1

void set_servo_angle_up(uint8_t up_angle);

#endif
