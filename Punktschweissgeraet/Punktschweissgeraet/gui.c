#include "Gui.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

void initLcd(){
	 lcd_init();
	 PINB |= (1<<DISPLAY_LED); 
}

void showWelcomeScreen(){
	  lcd_clear();
	  lcd_setcursor( 0, 1 );
	  lcd_string("www.tief-dunkel-");
	  lcd_setcursor( 1, 2 );
	  lcd_string("   kalt.org");
	  
	  for (int i = 0; i< 2; i++ ){
		  PINB |= (1<<DISPLAY_LED); 
		  _delay_ms (200);
	  }	  
	    for (int i = 0; i< 2; i++ ){
		    PINB |= (1<<DISPLAY_LED);
		    _delay_ms (400);
	    } 
	   _delay_ms (MSEC_EXECUTIONS);
	   lcd_clear();
}

void showAllExecutions(uint32_t count){
	  lcd_clear();
	  lcd_setcursor( 0, 1 );
	  lcd_string("Ausloesungen:");
	  lcd_setcursor( 1, 2 );
	  char str[16];
	  sprintf(str, "%d", count);
	  lcd_string(str );	 
	  _delay_ms (MSEC_EXECUTIONS);
	   lcd_clear();
}


void showTodaysExecutions(uint16_t count){
	char str[5];
	sprintf(str, "%d", count);
	lcd_setcursor( 1, 2 );
	lcd_string(str );	 
}


void showVoltageLow (uint8_t volt, uint8_t mvolt){
	
}


void showVoltageHigh (uint8_t volt, uint8_t mvolt){
	
}


void showIfBothCapActive (uint8_t isSecondActive){
	
}


void showLoading (){
	
}


void showReady (){
	
}

