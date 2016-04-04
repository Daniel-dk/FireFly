/*look at EEMPROMEx for really good functions*/

/*get Wifi and colour settings locations from EEPROM
fetch the following from EEPROM: 
wifiSettings_e - do we use defualt or get from SD. EEPROM
colourSettings_e  - do we use defualt or get from SD. EEPROM
ledBrightness - what was the last brightness at ?
*/
void initSystem() {

	wifiSettings_e = WIFI_DEFAULT;
	colourSettings_e = COL_DEFAULT;
	ledBrightness = DEFAULT_BRIGHTNESS;

}

/*get a colour palette from EEPROM*/
void getColorPaletteEEPROM() {

}
/*save a colour palette to EEPROM*/
void saveColorPaletteEEPROM() {

}

