/*
 * MeasureVoltage.h
 *
 * Created: 24.03.2016 21:22:01
 *  Author: Oliver
 */ 


#ifndef MEASUREVOLTAGE_H_
#define MEASUREVOLTAGE_H_

#include <stdint.h>

#define C1_VOLT 1
#define C2_VOLT 2

#define CONTACT 3

#define ADC_FACTOR  0.038f

void initADC ();

float readCapVoltage(volatile uint8_t number);


#endif /* MEASUREVOLTAGE_H_ */