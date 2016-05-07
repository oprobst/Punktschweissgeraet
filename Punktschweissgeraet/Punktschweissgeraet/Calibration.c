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
#include <util/delay.h>

#define CALIBRATION_DURATION 300000.0d //ms
#define CALIBRATION_RESISTOR 3956.0f //ohm

float EEMEM eeCap1Mem;
float EEMEM eeCap2Mem;

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
	_delay_ms(CALIBRATION_DURATION);
	float mvC1End = readCapVoltage(C1_VOLT);
	float mvC2End = readCapVoltage(C2_VOLT);
		
  
  
	float cap1 = calculateCap(mvC1Start, mvC1End);
	float cap2 = calculateCap(mvC2Start, mvC2End);
	
	showLastCalibration(mvC1Start, mvC1End);
	
	showLastCalibration(cap1, cap1);
	
	//storeCap (cap1, cap2);
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


