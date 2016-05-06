/*
 * Calibration.c
 *
 * Created: 06.05.2016 08:06:21
 *  Author: Oliver
 */ 

#include "Calibation.h"
#include "Gui.h"
#include "MeasureVoltage.h"
#include <stdint.h>
#include <avr/eeprom.h>

#define CALIBRATION_DURATION 60000 //ms
#define CALIBRATION_RESISTOR 22000 //ohm

float EEMEM eeCap1Mem;
float EEMEM eeCap2Mem;

float calculateCap (uint16_t start, uint16_t end){
	return 0.0d;
}

void calibrate() {
	
	showCalibration ();
	uint16_t mvC1Start = readCapVoltage(0);
	uint16_t mvC2Start = readCapVoltage(1);
	_delay_ms(CALIBRATION_DURATION);
	uint16_t mvC1End = readCapVoltage(0);
	uint16_t mvC2End = readCapVoltage(1);
		
  
	float cap1 = calculateCap(mvC1Start, mvC1End);
	float cap2 = calculateCap(mvC2Start, mvC2End);
	
	showCapacity(cap1, cap2);
	
	storeCap (cap1, cap2);
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


