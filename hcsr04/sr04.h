#ifndef __SR04_H
#define __SR04_H 


#include "stdlib.h"	
#include "main.h"
#include "tim.h"


void Delay_us(uint32_t us);

void Send_Ultrasonic(void);

uint16_t Ultrasonic(void);

void SR04(void);





#endif
