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
#define MSEC_EXECUTIONS 3000
#endif

#ifndef MSEC_CALIBRATION
#define MSEC_CALIBRATION 2000
#endif

#ifndef DISPLAY_LED
#define DISPLAY_LED PB0
#endif

#ifndef LED_RED
#define LED_RED PB1
#endif

#ifndef LED_BLUE
#define LED_BLUE PC5
#endif

//delegate to init of lcd driver
void initLcd ();

// Some introduction screen
void showWelcomeScreen();

// Full screen with all executions
void showAllExecutions(uint32_t count);

//show result of last calibration
void showLastCalibration (float cap1, float cap2);

// Amount of executions since last start
void showTodaysExecutions(uint16_t count);

//Show voltage of small cap
void showVoltageLow (float volt);

//Show voltage of high cat
void showVoltageHigh (float volt);

//Show if both big caps are fired. 1=true, other = false
void showIfBothCapActive (uint8_t isSecondActive);

// Show loading capacitor message
void showLoading ();

//Show contact measurement message.
void showContact ();

//Show execution
void showFire();

//The calculated resistance of the last execution
void showOhm(float ohm);

// The calculated amperes drawn in the last execution
void showAmpere (float ampere);

//Debug output
void writeDebug (const char *data);

//Display calibration is in progress
void showCalibration (double time);

//faster display update, just change sec value
void showUpdateCalibration (double time);

//Display Capacity for 5 sec.
void showCapacity (float cap1, float cap2);

#endif /* GUI_H_ */