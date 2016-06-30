/*
 * ExecCount.c
 *
 * Created: 22.03.2016 00:34:32
 *  Author: Oliver
 */ 

#include "ExecCount.h"
#include <avr/eeprom.h>

uint32_t overallCount;
uint16_t todayCount;
uint32_t EEMEM eeExecMem;

void initExecCount (){
	eeprom_busy_wait();
	//eeprom_update_dword(&eeExecMem, 82);
	overallCount = eeprom_read_dword(&eeExecMem);
	todayCount = 0;
}

void storeOverallExecutions(){
	eeprom_busy_wait();
	eeprom_update_dword(&eeExecMem, overallCount);
}

void addExecution (){
	overallCount++;
	todayCount++;
	storeOverallExecutions();
}
uint32_t getAllExecutions(){
	return overallCount;	
}

uint16_t getTodaysExections(){
	return todayCount;
}

