#define F_CPU 1000000UL //16 MHz

#define TRUE 1
#define FALSE 0

// LCD DEFINES
#define LCD_IO_MODE   1
#define LCD_PORT   PORTD


#define LCD_DATA0_PIN   5
#define LCD_DATA1_PIN   4
#define LCD_DATA2_PIN   3
#define LCD_DATA3_PIN   2

#define LCD_RS_PORT   PORTD
#define LCD_RS_PIN   0

#define LCD_RW_PORT   PORTB
#define LCD_RW_PIN   5

#define LCD_E_PORT   PORTD
#define LCD_E_PIN   1

// FURTHER IO
#define LED_RED PB1
#define LED_BLUE PC5
#define BEEP PB2

#define C1_FIRE PD7
#define C2_FIRE PD6
#define C3_FIRE PB4


#define SWITCH PC0
#define PUSH PC1

#define DISPLAY_LED PB0


#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

#include "Gui.h"
#include "lcd-routines.h"
#include "ExecCount.h"
#include "MeasureVoltage.h"

int main(void) {
	
	//PINB |= (1<<PB1); //Invert PB4
	uint32_t c =0;
	uint32_t d =1;
	uint32_t execCount =0;
	
	
	initPorts();
	initADC();
	initExecCount();
	initLcd();
	showWelcomeScreen();
	showAllExecutions(getAllExecutions());
	showLoading();
	showIfBothCapActive (TRUE);
	showVoltageHigh(0,0);
	showVoltageLow(0,0);
	
	//bit0 = first large C, bit1= second large C, bit2= small c
	uint8_t executeCapacitor = 0b1;
	uint8_t isReady = TRUE;
	
	uint16_t firstMVoltDigit = 0;
	uint16_t voltage = 0;

	while (1){
		
		//Check for switch:
		if ( !(PINC & ( 1 << SWITCH )) && CHECK_BIT(executeCapacitor, 1)) {
			executeCapacitor &= ~(1<<1);
			showIfBothCapActive(CHECK_BIT(executeCapacitor, 1));
			
			} else if ( (PINC & ( 1<<SWITCH )) &&  !CHECK_BIT(executeCapacitor, 1)){
			executeCapacitor |= (1<<1);
			showIfBothCapActive(CHECK_BIT(executeCapacitor, 1));
		}
		
		//check for push
		if ( ! (PINC & ( 1 << PUSH ))) {
			if (isReady == TRUE){
				PORTC &= ~(1 << LED_BLUE);
				execute(executeCapacitor);
				showTodaysExecutions(++execCount);
				isReady == FALSE;
				
				c = 0;
				showLoading();
				} else{
				
			}
		}
		
		c += 1;
		if (c > 1000){
			PORTC |= (1 << LED_BLUE);
			showReady();
			isReady == TRUE;
			c=0;
		}
		
		d -= 1;
		if (d == 0){
			
			d=10;
			
			firstMVoltDigit = readCapVoltage(C1_VOLT) /100;
			voltage = firstMVoltDigit/10;
			firstMVoltDigit = firstMVoltDigit-(voltage*10);
			showVoltageHigh(voltage,firstMVoltDigit);
			
			if (voltage <= 2){
				executeCapacitor &= ~(0<<1);
				executeCapacitor &= ~(1<<1);
				executeCapacitor &= ~(2<<1);  //DELETEME				
				 
			} else {
				executeCapacitor |= (0<<1);
				executeCapacitor |= (1<<1);
				executeCapacitor |= (2<<1);  //DELETEME
			 
			}
			
			firstMVoltDigit = readCapVoltage(C2_VOLT) /100;
			voltage = firstMVoltDigit/10;
			firstMVoltDigit = firstMVoltDigit-(voltage*10);
			showVoltageLow(voltage,firstMVoltDigit);
			if (voltage <= 2){
			 //  executeCapacitor &= ~(2<<1);  				
			} else {
			 //  executeCapacitor |= (2<<1);  
		    }
		
		}
		
	}
	
}



void execute (uint8_t executeCapacitor){
	
	showFire();	

	if (CHECK_BIT(executeCapacitor, 0)){
		
		PIND|= (1<<C1_FIRE);
		PINB |= (1<<LED_RED);
		_delay_ms(1500);
		
		PIND|= (1<<C1_FIRE);
		PINB |= (1<<LED_RED);
		_delay_ms(1500);
	}
	if (CHECK_BIT(executeCapacitor, 1)){
		PIND|= (1<<C2_FIRE);
		PINB |= (1<<LED_RED); //Invert PB4
		_delay_ms(1500);
		PIND|= (1<<C2_FIRE);
		PINB |= (1<<LED_RED); //Invert PB4
		_delay_ms(1500);
	}
	if (CHECK_BIT(executeCapacitor, 2)){
			 
		PINB|= (1<<C3_FIRE);
		PINB |= (1<<LED_RED); //Invert PB4
		_delay_ms(15);
		PINB|= (1<<C3_FIRE);
		PINB |= (1<<LED_RED); //Invert PB4

	}
	
	PINB |= (1<<BEEP); //Invert PB4
	_delay_ms(150);
	
	PINB |= (1<<BEEP); //Invert PB4


	
}

void initPorts (){
	DDRB |= ((1 << PB1) |(1 << PB2) |(0 << PB3) |(1 << PB4) | (1 << PB0));
	DDRC |= ((1 << PC5) | (0 << PC1)|(0 << PC0)|(0 << PC4)|(0 << PC3));
	PORTC |= ((1 << PC1)|(1 << PC0));
}