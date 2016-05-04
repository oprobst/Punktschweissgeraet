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
	
	for (int i = 0; i< 4; i++ ){
		PINB |= (1<<DISPLAY_LED);
		_delay_ms (500);
	}
	_delay_ms (MSEC_INTRO);
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
	lcd_setcursor( 0, 2  );
	lcd_string(str );
}

void showVoltage (uint8_t volt, uint8_t mvolt, uint8_t row){
	lcd_setcursor(  11, row );
	if (volt <= 2){
		
		lcd_string(" OFF ");
    } else {
		char str[5];
		sprintf(str, "%d", volt);
		if (volt <10){
			lcd_string(" ");
		}
		
		lcd_string(str );
		sprintf(str, ",%dV", mvolt);
		lcd_setcursor( 13, row );
		lcd_string(str );
	}
}

void showVoltageLow (uint8_t volt, uint8_t mvolt){
	showVoltage(volt, mvolt, 1);
}


void showVoltageHigh (uint8_t volt, uint8_t mvolt){
	showVoltage(volt, mvolt, 2);
}


void showIfBothCapActive (uint8_t isSecondActive){
	lcd_setcursor(8,2);
	if ((isSecondActive) & (1<<1)){
		lcd_string("2x");
		} else {
		lcd_string("1x");
	}
}


void showLoading (){
	lcd_setcursor( 0, 1 );
	lcd_string("Loading" );
}


void showReady (){
	lcd_setcursor(0, 1 );
	lcd_string("Ready  " );
}

void showFire(){
	lcd_setcursor(0, 1 );
	lcd_string("FIRE!  " );
}

void writeDebug (const char *data ){
	if(DEBUG){
	    lcd_setcursor(2, 2);
		lcd_string(data);
	}
}

