/*low level functions that relate to LED manipulation go here*/


/*get a colour palette from SD card, EEPROM or use full spectrum HSV*/
void initColour(colourSettingsEnum settings) {
	switch (settings)
	{
	case COL_DEFAULT: // don't change the colour palette
		break;
	case COL_EEPROM: // read one from EEPROM
		//set currentPalette
		/*
		for (int i = 0; i < 16; i++) {
			currentPalette[i] = CHSV(random8(), 255, random8()); // set a colour palette
		}
		*/
		colourSettings_e = COL_DEFAULT; // fail over to defualt
		break;
	case COL_SD: // read one from SD


		colourSettings_e = COL_DEFAULT; // fail over to defualt
		break;
	default:
		break;
	}
	colourSettings_e = settings; // change the mode to fit what was passed to it
}

/*Wrapper for Fastled.show so it also outputs led[0] on  on PWM*/
void showLEDs() {
	FastLED.show();
	showAnalogRGB(leds[0]);
}


/*will return a colour that falls inside the lookup table ( if any )
uses the HUE value for loohup table index, brightness/ val is preserved
using palettes is a 768-byte cost in RAM.
*/
CRGB Colour(uint8_t hue, uint8_t sat, uint8_t val) {

	if (colourSettings_e != COL_DEFAULT) { // use a 
		return ColorFromPalette(currentPalette, hue, val, LINEARBLEND);
	}
	else { // straight up HSV conversion
		return CRGB(CHSV(hue,sat,val));
	}
}


// showAnalogRGB: this is like FastLED.show(), but outputs on 
// analog PWM output pins instead of sending data to an intelligent,
// pixel-addressable LED strip.
// 
// This function takes the incoming RGB values and outputs the values
// on three analog PWM output pins to the r, g, and b values respectively.
void showAnalogRGB( CRGB & rgb)
{
	analogWrite(PWM_RED, rgb.r);
	analogWrite(PWM_GREEN, rgb.g);
	analogWrite(PWM_BLUE, rgb.b);
}


/*set whetehr the onboard LED mimics the 12V strip output */
boolean onboardLEDcontrol(boolean enable) {
	if (enable){
		// enable onboard LED to show what's on the PWM strip
		digitalWrite(ONBOARD_LED_EN,HIGH);
	}
	else{
		// disable onboard LED
		digitalWrite(ONBOARD_LED_EN, LOW);
	}
	return digitalRead(ONBOARD_LED_EN);
}