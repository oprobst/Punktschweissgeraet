#define F_CPU 16000000UL //16 MHz
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
	lcd_setcursor( 0, 2 );
	char str[16];
	sprintf(str, "%lu", count);
	lcd_string(str );
	_delay_ms (MSEC_EXECUTIONS);
	lcd_clear();
}

void showLastCalibration(float cap1, float cap2){
	char str[16];
	lcd_clear();
	lcd_setcursor( 0, 1 );
	sprintf(str, "C1: %7.3f mF", cap1);
	lcd_string(str );
	
	lcd_setcursor( 0, 2 );	
	sprintf(str, "C2: %7.3f mF", cap2);
	lcd_string(str );
	_delay_ms (MSEC_CALIBRATION);
	lcd_clear();
}



void showTodaysExecutions(uint16_t count){
	char str[3];
	sprintf(str, "%03d", count);
	lcd_setcursor( 0, 1  );
	lcd_string(str );
}

void showVoltage (float volt, uint8_t row){
	lcd_setcursor(  11, row );
	if (volt <= 2){
		lcd_string(" OFF ");
    } else {		
		char c[5];
		sprintf(c, "%4.1fV",volt);	
		lcd_string(c);
	}
}

void showVoltageLow (float volt){
	showVoltage(volt,  1);
}


void showVoltageHigh (float volt){
	showVoltage(volt,  2);
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
	PORTC &= ~(1 << LED_BLUE);
	PORTB |= (1<<LED_RED); 
}


void showReady (){ 
	PORTB &= ~(1 << LED_RED); 
}

void showContact(){
	 PORTC |= (1 << LED_BLUE); 
	 PORTB &= ~(1 << LED_RED); 
}

void writeDebug (const char *data ){
	if(DEBUG){
	    lcd_setcursor(2, 2);
		lcd_string(data);
	}
}

void showOhm(float ohm){
	lcd_setcursor(0, 2);
	lcd_string("      ");
	if(ohm <= 0.0){
		return;
	}
	lcd_setcursor(0, 2);
	if (ohm > 999){
		lcd_string(">999\364");
	} else if (ohm > 0.00999){
	     char c[16];
	     sprintf(c, "%.0f\364", ohm);
	     lcd_string(c);
	} else {	 
      char c[16];
	  sprintf(c, "%.2fm\364", (ohm*1000));
	  lcd_string(c);
	}
	 
} 

void showAmpere (float ampere){
	lcd_setcursor(4, 1);
	lcd_string("     ");
	lcd_setcursor(4, 1);
	if (ampere < 1){
		char c[5];
		sprintf(c, "%.0f", ampere * 1000);
		lcd_string(c);
		lcd_string("mA");
	} else if (ampere < 1000){
		char c[5];
		sprintf(c, "%.0f", ampere);
		lcd_string(c);
		lcd_string("A");    	
	} else {				
	char c[5];
	sprintf(c, "%.2f", (ampere/1000));
	lcd_string(c); 
    lcd_string("kA");
    }
}

void showCalibration (double time){
	char str[16];
	lcd_clear();
	lcd_setcursor( 0, 1 );	 
	lcd_string("Kalibiervorgang" );	
	lcd_setcursor( 0, 2 );
	sprintf(str, "noch %.0lf sek.", (time/1000));
	lcd_string(str);
}

void showUpdateCalibration (double time){
	char str[16];
	lcd_setcursor( 5, 2 );
	sprintf(str, "%.0lf sek.", (time/1000));
	lcd_string(str);
}