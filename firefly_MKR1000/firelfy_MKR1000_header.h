#pragma once
/*Pin definitions*/


/*--Buttons*/
#define BUTTON_USR 2 // 12 on EVKIT
#define BUTTON_WIFI_RESET 21

/*--Pixel*/
/*--- Adressable LEDs*/
#define PIXEL_DATA 0 // 15 on evkit
#define PIXEL_CLOCK 1
/*--- PWM LED Strip*/
#define PWM_RED 3
#define PWM_GREEN 4
#define PWM_BLUE 5
/*--- onboard LED enable ( LED is tied to PWM pins )*/
#define ONBOARD_LED_EN 18
/*--- Maximum adressable LEDs we will allow*/
#define MAX_LEDS 400
/*--- default to supporting the max amount of adressable LEDs*/
#define NUM_LEDS_DEFAULT MAX_LEDS
/*--- default to full brightness range*/
#define DEFAULT_BRIGHTNESS 255
/*--- our maximum framerate that we won't go above*/
#define FRAMES_PER_SECOND  100
/*--- how many animation pattern things we have to cycle thru*/
#define MAX_PATTERN 6
/*--- index of the last pattern*/
#define MAX_PATTERN_IDX (MAX_PATTERN-1)
/*--- used when we cycle thru the patterns*/
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

/*--SD Card - on SPI0*/
#define CS_SD 6
#define SD_DETECT 17
/*--PSU*/
/*--- SETS PSU in 5V or 12V mode*/
#define PSU_MODE_SEL 19
#define PSU_ENABLE 20
#define V_LED_MON A0 // ADC for LED voltage line sense 3v3 == 14 VLED, 1.27 = 5Vled

#define V_DIV_R1 32 // 32k R1 in divider
#define V_DIV_R2 10 //  10k R1 in divider

#define VDIV_RATIO 0.2381 // regular voltage divider ratio : (R2) / (R1 + R2)
#define VDIV_RATIO_INV 4.2   // inverted voltage divider ratio : (R1 + R2) / (R2) 

#define V_REF_ADC 3.3 // 3v3 is Vref for ADC



/*
Vout / Vin = ( (R2) / (R1 + R2))
so
Vout = Vin*( (R2) / (R1 + R2)) " regular" voltage divider ratio to calculate Vout
and
Vin = Vout*((R1 + R2)/ (R2) ) " inverted" voltage divider ratio to calculate Vin
*/

/*--EEPROM: 24AA02 type*/
#define EEPROM_ADDR // I2C EEProm adress 

/*--Acceleromter + Gyro : LSM330DLC */
// Accelerometer = 001100xb
#define LSM330D_A_ADDR0     0b00011000  // SA0=0(GND)
#define LSM330D_A_ADDR1     0b00011001  // SA0=1(VDD)

// gyro = 110101xb
#define LSM330D_G_ADDR0     0b01101010  // SA0=0(GND)
#define LSM330D_G_ADDR1     0b01101011  // SA0=1(VDD)
 
#define IMU_ADDR_ACC LSM330D_A_ADDR0 // I2C Acc adress 
#define IMU_ADDR_GYR LSM330D_G_ADDR0 // I2C Gyro adress 


/*Structure and Enum definitions*/

/*what mode the PSU can be in*/
enum powerModeEnum
{
	POWER_EXT,
	POWER_5V,
	POWER_12V,
};

/*what mode  Wifi starts up as*/
enum wifiSettingsEnum
{
	WIFI_DEFAULT,	// Set as an AP
	WIFI_EEPROM,	// get config from EEPROM, failover to DEFUALT
	WIFI_SD,		// get config form SD, failover to DEFUALT
	WIFI_AP,		// host an Access point 
};
wifiSettingsEnum wifiSettings_e = WIFI_DEFAULT;

/*what colour palette we use*/
enum colourSettingsEnum
{
	COL_DEFAULT,// no palette, regular HSV
	COL_EEPROM,	// get a colour palette from EEPROM, failover to COL_DEFAULT
	COL_SD,		// get palette from SD, failover to COL_DEFAULT
};
colourSettingsEnum colourSettings_e = COL_DEFAULT;


/*instances of libraries*/

// Setup a new OneButton for User buton, active low.  
OneButton userButton(BUTTON_USR, true);
// Setup a new OneButton for Wifi control, active low.  
OneButton wifiButton(BUTTON_WIFI_RESET, true);

// Define the array of adressable LEDs
CRGB leds[MAX_LEDS];
// LED controller - so we can change the amount of LEDs we speak to up to the MAX
CLEDController* controller;
/* Global brightness adjustment */
uint8_t ledBrightness = DEFAULT_BRIGHTNESS;
// how many LEDs we will be using (must be <= MAX_LEDS )
uint16_t numLEDs = NUM_LEDS_DEFAULT;
/*index for meteors*/
uint16_t idex = 0;
// List of patterns to cycle through.  Each is defined as a separate function in the LED_patterns.ino
// ATT : if you add more patterns here, adjust MAX_PATTERN accordingly, default is 6 ( 0 to 5 )
typedef void(*SimplePatternList[])();

uint8_t gPatternNumber = 0; // Index number of which pattern is displayed - buttonpress will change this
			  
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//using palettes is a 768 - byte cost in RAM to build the lookup table.
CRGBPalette16 currentPalette; // takes up 64 bytes. - 16 entry palette ( will linear intepolate to a 256 entry table)





// LSM330D Register Map - should go into a Library TODO

// Accelerometer
#define LSM330D_CTRL_REG1_A     0x20
#define LSM330D_CTRL_REG2_A     0x21
#define LSM330D_CTRL_REG3_A     0x22
#define LSM330D_CTRL_REG4_A     0x23
#define LSM330D_CTRL_REG5_A     0x24

#define LSM330D_OUT_X_L_A       0x28
#define LSM330D_OUT_X_H_A       0x29
#define LSM330D_OUT_Y_L_A       0x2A
#define LSM330D_OUT_Y_H_A       0x2B
#define LSM330D_OUT_Z_L_A       0x2C
#define LSM330D_OUT_Z_H_A       0x2D

// gyro
#define LSM330D_WHO_AM_I_G      0x0F
#define LSM330D_WHOAMI_G_VAL    0xD4

#define LSM330D_CTRL_REG1_G     0x20
#define LSM330D_CTRL_REG2_G     0x21
#define LSM330D_CTRL_REG3_G     0x22
#define LSM330D_CTRL_REG4_G     0x23
#define LSM330D_CTRL_REG5_G     0x24

#define LSM330D_OUT_X_L_G       0x28
#define LSM330D_OUT_X_H_G       0x29
#define LSM330D_OUT_Y_L_G       0x2A
#define LSM330D_OUT_Y_H_G       0x2B
#define LSM330D_OUT_Z_L_G       0x2C
#define LSM330D_OUT_Z_H_G       0x2D
