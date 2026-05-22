#ifndef __MOTER_H
#define __MOTER_H

#include "main.h"
#include "tim.h"

#define AIN1_PORT GPIOB
#define AIN2_PORT GPIOB
#define BIN1_PORT GPIOB
#define BIN2_PORT GPIOB
#define AIN1_PIN GPIO_PIN_12
#define AIN2_PIN GPIO_PIN_13
#define BIN1_PIN GPIO_PIN_14
#define BIN2_PIN GPIO_PIN_15

#define STBY_PORT GPIOA
#define STBY_PIN GPIO_PIN_12

#define PWM_TIMER_A &htim2
#define PWM_TIMER_B &htim2
#define PWM_CH_A TIM_CHANNEL_2
#define PWM_CH_B TIM_CHANNEL_3

#define MOTER_MAX_SPEED 100
#define MOTER_MIN_SPEED -100

void moter_init(void);
void moter_stop(void);
void moter_a_set_speed(int8_t speed);
void moter_b_set_speed(int8_t speed);

#endif
