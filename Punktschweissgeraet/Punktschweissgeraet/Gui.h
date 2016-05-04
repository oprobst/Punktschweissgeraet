/*
 * gui.h
 *
 * Control all output to LCD modul 
 *
 * Created: 22.03.2016 00:00:39
 *  Author: Oliver
 */ 
#include <stdint.h>

#ifndef GUI_H_
#define GUI_H_

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef MSEC_INTRO
#define MSEC_INTRO 0000
#endif

#ifndef MSEC_EXECUTIONS
#define MSEC_EXECUTIONS 000
#endif

#ifndef DISPLAY_LED
#define DISPLAY_LED PB0
#endif

//delegate to init of lcd driver
void initLcd ();

// Some introduction screen
void showWelcomeScreen();

// Full screen with all executions
void showAllExecutions(uint32_t count);

// Amount of executions since last start
void showTodaysExecutions(uint16_t count);

//Show voltage of small cap
void showVoltageLow (uint8_t volt, uint8_t mvolt);
//Show voltage of high cat
void showVoltageHigh (uint8_t volt, uint8_t mvolt);

//Show if both big caps are fired. 1=true, other = false
void showIfBothCapActive (uint8_t isSecondActive);

// Show loading capacitor message
void showLoading ();

//Show ready message.
void showReady ();

//Show execution
void showFire();

//Debug output
void writeDebug (const char *data);

#endif /* GUI_H_ */