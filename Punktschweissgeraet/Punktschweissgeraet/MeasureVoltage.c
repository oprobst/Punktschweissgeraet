 
 #include "MeasureVoltage.h"
 #include <stdint.h>

 #include <avr/io.h>



 void initADC (){
	 ADMUX =
	 (0 << ADLAR) |
	 (0 << REFS1) |
	 (0 << REFS0) |
	 (0 << MUX3)  |
	 (0 << MUX2)  |
	 (1 << MUX1)  |
	 (1 << MUX0);
	 
	 //ADC enabled, prescaler to 128 bit
	 ADCSRA =
	 (1 << ADEN)  |
	 (1 << ADPS2) |
	 (1 << ADPS1) |
	 (0 << ADPS0);
	 
 }

 /*
 * Do a single ADC read
 */
 uint16_t readSingleADC(void)
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


 uint16_t readADCsamples( uint8_t nsamples )
 {
	 uint32_t sum = 0;
	 readSingleADC ();
	 for (uint8_t i = 0; i < nsamples; ++i ) {
		 sum += readSingleADC( );
	 }
	 
	 return (uint16_t)( sum / nsamples );
 }


 uint16_t readADC (volatile uint8_t channel) {
	 
	 switch (channel){
		 case C1_VOLT: //PC4
		 
		 ADMUX =
		 (0 << ADLAR) |
		 (0 << REFS1) |
		 (0 << REFS0) |
		 (0 << MUX3)  |
		 (1 << MUX2)  |
		 (0 << MUX1)  |
		 (0 << MUX0);
		 return readADCsamples(3);
		 case C2_VOLT: //PC3
		 ADMUX =
		 (0 << ADLAR) |
		 (0 << REFS1) |
		 (0 << REFS0) |
		 (0 << MUX3)  |
		 (0 << MUX2)  |
		 (1 << MUX1)  |
		 (0 << MUX0);
		 return readADCsamples(3);
		 
		 default: //read CONTACT, no error handling... //PC2
		 ADMUX =
		 (0 << ADLAR) |
		 (0 << REFS1) |
		 (0 << REFS0) |
		 (0 << MUX3)  |
		 (0 << MUX2)  |
		 (1 << MUX1)  |
		 (1 << MUX0);
		 return readADCsamples(3);
		 
	 }
	 
 }

 // Return the voltage at capacitor in Volt
 float readCapVoltage(volatile uint8_t number){
	 uint16_t volt = readADC(number);
	 float zdiode_corr = 0;
	 if (volt > 430){
		 zdiode_corr = pow((volt-430),2.2)/200000000;
	 }
	 return ((float) volt) * (ADC_FACTOR + zdiode_corr);
 }

