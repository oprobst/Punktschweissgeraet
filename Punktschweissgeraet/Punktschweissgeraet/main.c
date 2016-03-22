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

#define C1_VOLT PC4
#define C2_VOLT PC3

#define CONTACT PC2

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

int main(void) {
	
	//PINB |= (1<<PB1); //Invert PB4
	uint32_t c =0;
	uint32_t execCount =0;
	
	
	initPorts();
	initADC();
	initExecCount();
	initLcd();
	showWelcomeScreen();
	showAllExecutions(getAllExecutions());
	showLoading();
	showIfBothCapActive (TRUE);
	showVoltageHigh(32,2);
	showVoltageLow(8,2);
	
	//bit0 = first large C, bit1= second large C, bit2= small c
	uint8_t executeCapacitor = 0b1;
	uint8_t isReady = TRUE;
	
	

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
				  PORTB &= ~(1 << PB1);
				execute(executeCapacitor);
				showTodaysExecutions(++execCount);
				isReady == FALSE;	
               
				c = 0;
				showLoading();
			} else{
				
			}			
		}
		
		c += 1;
		if (c > 100000){
			PORTB |= (1 << PB1); 					
			showReady();
			isReady == TRUE;
			c=0;
		}
		
		//int volt = readADC();
		//volt = 1000 * volt * 3900 / 560 ;
		//lcd_setcursor( 1, 2 );
		//char str[15];
		//sprintf(str, "%d mV", volt);
		//lcd_string(str );
		
		}
	
}
 
void execute (uint8_t executeCapacitor){
	
	showFire();
	
	if (CHECK_BIT(executeCapacitor, 0)){
 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
	}
	if (CHECK_BIT(executeCapacitor, 1)){
 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
	 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
	}
	if (CHECK_BIT(executeCapacitor, 2)){
 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
	 
		PINC |= (1<<PC5); //Invert PB4
		_delay_ms(1500);
	}
	
	
}


void initADC ( ) {
	
	// ADC Configuration: Mux only for PB3, RefVoltage = Vcc, no left shift for 10bit accuracy.
	ADMUX =
	(0 << ADLAR) |
	(0 << REFS1) |
	(0 << REFS0) |
	(0 << MUX3)  |
	(1 << MUX2)  |
	(0 << MUX1)  |
	(0 << MUX0);

	//ADC enabled, prescaler to 128 bit
	ADCSRA =
	(1 << ADEN)  |
	(1 << ADPS2) |
	(0 << ADPS1) |
	(0 << ADPS0);
	
	//do one read
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC) ) {
	}
	(void) ADCW;
}
/*
* Do a single ADC read
*/
int readADC(void)
{
	
	uint8_t adc_lobyte; // to hold the low byte of the ADC register (ADCL)
	uint16_t raw_adc;
	
	ADCSRA |= (1 << ADSC);         // start ADC measurement
	while (ADCSRA & (1 << ADSC) ); // wait till conversion complete

	// for 10-bit resolution:
	adc_lobyte = ADCL; // get the sample value from ADCL
	raw_adc = ADCH<<8 | adc_lobyte;   // add lobyte and hibyte

	return raw_adc;
}

void initPorts (){
	DDRB |= ((1 << PB1) |(1 << PB2) |(0 << PB3) |(1 << PB4) | (1 << PB0));
	DDRC |= ((1 << PC5) | (0 << PC1)|(0 << PC0)|(0 << PC4)|(0 << PC3));
	PORTC |= ((1 << PC1)|(1 << PC0));
}