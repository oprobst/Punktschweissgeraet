/*
* Executor.c
*
* Created: 05.05.2016 21:50:49
*  Author: Oliver
*/

#define F_CPU 16000000UL //16 MHz

#include "MeasureVoltage.h"
#include "Executor.h"
#include <avr/io.h>
#include <stdint.h>  
#include <avr/interrupt.h>

 #define LOW_EXEC_TIME 30
 #define BREAK_TIME 250
 #define HIGH_EXEC_TIME 30
 
 volatile uint32_t msPassed;

double calculateOhm (float time, float capacity, float voltStart, float voltEnd){
	if (voltStart == 0 || voltEnd == 0 ){
		return 0;
	}
	if (log(voltEnd/voltStart) == 0){
		return 0;
	}
	if (capacity == 0){
		return 0;
	}
	return ((time * -1) / capacity) / log(voltEnd/voltStart);
}

uint16_t calcMaxAmpere (float maxVolt, float ohm){
	if (ohm <= 0.0){
		return 0;
	}
	return (uint16_t) (maxVolt / ohm);
}

void initExecTimer(){
	TCCR1A = (1<<WGM01);
	TCCR1B |= ((1<<CS01) | (1<<CS00)); //prescaler 64
	OCR1A = 250-1; // (16,000,000/64)/1000
	TIMSK1 |= (1<<OCIE1A);
	sei();
}

volatile float mvC1End = -1;
volatile float mvC2End = -1;

void wait(uint8_t waitTime){
	msPassed =0;
	while (msPassed < waitTime){
		
	}
}

void stopExecTimer (){
	cli();
}

ISR (TIMER1_COMPA_vect)
{
	if (mvC2End == -1){
		mvC1End = readCapVoltage(C1_VOLT);
		mvC2End = readCapVoltage(C2_VOLT);
    }
    msPassed++;

}

void execute (ExecutionResult *result, uint8_t executeCapacitor){

	float mvC1Start = 0;
	float mvC1End = 0;
	float mvC2Start = 0;
	float mvC2End = 0;
	 initExecTimer();
	 //Read Voltage, set output to true, if executeCapacitor is true for cap.
	 mvC1Start = readCapVoltage(C1_VOLT);
	 PORTB |= (CHECK_BIT(executeCapacitor, 0)<< PB4);
	 wait(LOW_EXEC_TIME);
	 PORTB &= ~(1<< PB4);
	 mvC1End = readCapVoltage(C1_VOLT);
	 
	 wait(BREAK_TIME);

	 mvC2Start = readCapVoltage(C2_VOLT);
	 PORTD |= (CHECK_BIT(executeCapacitor, 1) << PD6 | CHECK_BIT(executeCapacitor, 2) << PD7);
	 wait(HIGH_EXEC_TIME);
	 PORTD &= ~(1 << PD6 | 1 << PD7);
	 mvC2End = readCapVoltage(C2_VOLT);

     stopExecTimer();
	 result->voltageUsedC1 = mvC1Start - mvC1End;
	 result->voltageUsedC2 = mvC2Start - mvC2End;
	 result->ohmC1  = calculateOhm (1, CAP_LOW_SIZE, mvC1Start, mvC1End);
	 result->ohmC2 = calculateOhm (1, CAP_HIGH_SIZE, mvC2Start, mvC2End); 
	 result->ampereC1 = calcMaxAmpere (mvC1Start , result->ohmC1);
	 result->ampereC2 = calcMaxAmpere (mvC2Start , result->ohmC2);
	  
}


