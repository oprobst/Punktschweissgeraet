/*
 * ExecCount.c
 *
 * Created: 22.03.2016 00:34:32
 *  Author: Oliver
 */ 

#include "ExecCount.h"
#include <avr/eeprom.h>

uint32_t overallCount = 0;
uint16_t todayCount = 0;
uint32_t EEMEM eeExecMem;

void initExecCount (){
    eeprom_busy_wait();
	overallCount = eeprom_read_dword(0);	
	eeprom_busy_wait();
	overallCount = eeprom_read_dword(&eeExecMem);
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

void storeOverallExecutions(){
	  eeprom_busy_wait();
	  eeprom_update_dword((uint32_t*) &eeExecMem, overallCount);
}