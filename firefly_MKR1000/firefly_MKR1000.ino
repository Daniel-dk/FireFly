
/*information about this sketch*/
/*Library imports*/
/* TWI / I2C library*/
#include <Wire.h>
/* SPI interface */
#include <SPI.h>
/*WiFi 101 driver for WINC5100*/
#include <WiFi101.h>
/* SD card interface library*/
#include <SD.h>
/* FastLED LED control library*/
#include <FastLED.h>		
/* OneButton library to handle callbacks and button press handling */
#include <OneButton.h>		
/* MadgwickAHRS algorithm to get orientation of an object based on accelerometer and gyroscope readings */
#include <MadgwickAHRS.h>
/* Project specific header */
#include "firelfy_MKR1000_header.h"


/* initialise the patter list */
SimplePatternList gPatterns = { pattern_0, pattern_1, pattern_2, pattern_3, pattern_4, pattern_5 };

/*setup code here */
void setup()
{
 
/* initialise pins that are not initialised by libraries */
	initGPIO();

/* link button press callbacks */
	initButtons();

/* initialise the IMU + Madgwick math*/
	initIMU();

/* init LED controller  */
/*- Default to WS2812B/NEOPIXEL @ 800kHz */
	//FastLED.addLeds<WS2812B, PIXEL_DATA>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);;
	controller = &(FastLED.addLeds<WS2812B, PIXEL_DATA, GRB>(leds, numLEDs));
	
	/* -ALternate init for WS2801 "SPI" like LEDs*/
//	FastLED.addLeds<WS2801, PIXEL_DATA,PIXEL_CLOCK>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);;
/* -ALternate init for APA102 "SPI" like LEDs*/
//	FastLED.addLeds<APA102, PIXEL_DATA,PIXEL_CLOCK>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);;
// there are many more FastLed supported controllers - there are our most common ones

/* init system information ( wifi and colour settings values) from EEPROM */
	initSystem();

/*set LED brightness scaling ( 0- 255 ) -Default is Maximum brightness*/
	FastLED.setBrightness(ledBrightness);

/* init Wifi to AP / EEPROM / SD */
	initWifi(wifiSettings_e);

/* init a Color palette from SD/EEPROM or use full HSV */
	initColour(colourSettings_e);
}

/* main program code here */
void loop()
{
/*handle Power supply*/
	//
/*handle IMU's Madgwick math*/
	// - next beast
/*check button states and handle callbacks*/
	buttonTick();
/*handle WiFi*/
	//
/*handle USB Serial*/
	//
/*handle LED animations*/
	LEDanimations();
	// TODO  : colour palette in EEPROM and selection of that vs full HSV
}
