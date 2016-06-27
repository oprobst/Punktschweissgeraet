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

 #define LOW_EXEC_TIME 10
 #define BREAK_TIME 50
 #define HIGH_EXEC_TIME 20
 #define WAIT_TILL_MEASURE 5
 
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

double calcMaxAmpere (float maxVolt, float ohm){
	if (ohm <= 0.0){
		return 0;
	}
	return (double) (maxVolt / ohm);
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
	if (msPassed == WAIT_TILL_MEASURE){
		mvC2End = readCapVoltage(C1_VOLT);		
	}
    msPassed++;

}

void execute (ExecutionResult *result, uint8_t executeCapacitor){
	 
	 initExecTimer();
	 //Read Voltage, set output to true, if executeCapacitor is true for cap.
	//float mvC1Start = readCapVoltage(C2_VOLT);
	
	 PORTB |= (CHECK_BIT(executeCapacitor, 2) << PB4);
	 wait(LOW_EXEC_TIME);
	 PORTB &= ~(1<< PB4);
	// mvC1End = readCapVoltage(C1_VOLT);
	 
	 wait(BREAK_TIME);

	 float mvC2Start = readCapVoltage(C1_VOLT);
	 
	 PORTD |= (CHECK_BIT(executeCapacitor, 1) << PD6 | CHECK_BIT(executeCapacitor, 0) << PD7);
	 wait(HIGH_EXEC_TIME);
	 PORTD &= ~(1 << PD6 | 1 << PD7);
	 //mvC2End = readCapVoltage(C2_VOLT);

     stopExecTimer();
	// result->voltageUsedC1 = mvC1Start - mvC1End;
	 result->voltageUsedC2 = mvC2Start - mvC2End;
	// result->ohmC1  = calculateOhm (0.001, CAP_LOW_SIZE, mvC1Start, mvC1End);
	 result->ohmC2 = calculateOhm (0.001 * WAIT_TILL_MEASURE, CAP_HIGH_SIZE, mvC2Start, mvC2End); 
	// result->ampereC1 = calcMaxAmpere (mvC1Start , result->ohmC1);
	 result->ampereC2 =calcMaxAmpere (mvC2Start , result->ohmC2);
	  
}


