/*
* Calibration.c
*
* Created: 06.05.2016 08:06:21
*  Author: Oliver
*/

#include "Calibation.h"
#include "Gui.h"
#include "MeasureVoltage.h"

#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#define CALIBRATION_DURATION 180000 //ms
#define CALIBRATION_RESISTOR 3950.0f //ohm

float EEMEM eeCap1Mem;
float EEMEM eeCap2Mem;

volatile uint32_t msPassed;

double calculateCap (float start, float end){
	if (start == 0 || end == 0 ){
		return -1;
	}
	if (log(end/start) == 0){
		return -2;
	}
	return ((CALIBRATION_DURATION * -1) / CALIBRATION_RESISTOR) / log(end/start);
}

void calibrate() {
	
	showCalibration (CALIBRATION_DURATION);
	float mvC1Start = readCapVoltage(C1_VOLT);
	float mvC2Start = readCapVoltage(C2_VOLT);
	startTimer();
	float mvC1End = readCapVoltage(C1_VOLT);
	float mvC2End = readCapVoltage(C2_VOLT);
	stopTimer();
	
	
	float cap1 = calculateCap(mvC1Start, mvC1End);
	float cap2 = calculateCap(mvC2Start, mvC2End);
	
	showLastCalibration(cap1, cap2);
	
	storeCap (cap1, cap2);
}


void startTimer(){
	msPassed =0;
	TCCR0A = (1<<WGM01);
	TCCR0B |= ((1<<CS01) | (1<<CS00)); //prescaler 64
	OCR0A = 250-1; // (16,000,000/64)/1000
	TIMSK0 |= (1<<OCIE0A);
	sei();
	while (msPassed < CALIBRATION_DURATION){
		
	}
}

void stopTimer (){
	cli();
}
ISR (TIMER0_COMPA_vect)
{
	msPassed++;
	if (msPassed %10000 == 0){
		showUpdateCalibration (CALIBRATION_DURATION - msPassed);
	}
}


void storeCap (float cap1, double cap2){
	eeprom_busy_wait();
	eeprom_update_float((float*)&eeCap1Mem, cap1);
	eeprom_update_float((float*)&eeCap2Mem, cap2);

}

double loadCap1(){
	eeprom_busy_wait();
	return eeprom_read_float(&eeCap1Mem);
}

double loadCap2(){
	eeprom_busy_wait();
	return eeprom_read_float(&eeCap2Mem);
}


