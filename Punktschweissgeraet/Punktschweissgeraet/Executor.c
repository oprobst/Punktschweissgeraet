/*
* Executor.c
*
* Created: 05.05.2016 21:50:49
*  Author: Oliver
*/

#include "MeasureVoltage.h"
#include "Executor.h"
#include <avr/io.h>
#include <stdint.h>  
#include <util/delay.h>


 #define LOW_EXEC_TIME 100
 #define BREAK_TIME 250
 #define HIGH_EXEC_TIME 200
 

double calculateOhm (float time, float capacity, float voltStart, float voltEnd){
	return ((time * -1) / capacity) / log(voltEnd/voltStart);
}

void execute (ExecutionResult *result, uint8_t executeCapacitor){

	uint16_t mvC1Start = 0;
	uint16_t mvC1End = 0;
	uint16_t mvC2Start = 0;
	uint16_t mvC2End = 0;
	 
	 //Read Voltage, set output to true, if executeCapacitor is true for cap.
	 mvC1Start = readCapVoltage(0);
	 PORTB |= (CHECK_BIT(executeCapacitor, 0)<< PB4);
	 _delay_ms(LOW_EXEC_TIME);
	 PORTB &= ~(1<< PB4);
	 mvC1End = readCapVoltage(0);
	 
	 _delay_ms(BREAK_TIME);

	 mvC2Start = readCapVoltage(1);
	 PORTD |= (CHECK_BIT(executeCapacitor, 1) << PD6 | CHECK_BIT(executeCapacitor, 2) << PD7);
	 _delay_ms(HIGH_EXEC_TIME);
	 PORTD &= ~(1 << PD6 | 1 << PD7);
	 mvC2End = readCapVoltage(1);

	 result->voltageUsedC1 = mvC1Start - mvC1End;
	 result->voltageUsedC2 = mvC2Start - mvC2End;
	 result->ohmC1 = calculateOhm (LOW_EXEC_TIME, CAP_LOW_SIZE, mvC1Start, mvC1End);
	 result->ohmC2 = calculateOhm (HIGH_EXEC_TIME, CAP_HIGH_SIZE, mvC2Start, mvC2End);
	 result->ampereC1 = mvC1Start / result->ohmC1;
	 result->ampereC2 = mvC2Start / result->ohmC2;
}