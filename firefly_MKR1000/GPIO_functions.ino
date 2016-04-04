
/*Initialise the non-library controlled GPIO*/
void initGPIO() {
	/*--- PWM LED Strip*/
	pinMode(PWM_RED, OUTPUT);
	pinMode(PWM_GREEN, OUTPUT);
	pinMode(PWM_BLUE, OUTPUT);
	pinMode(V_LED_MON, INPUT);
	/*--SD Card - on SPI0*/
	pinMode(CS_SD, OUTPUT);
	pinMode(SD_DETECT, INPUT);
	/*--Buttons*/
	pinMode(BUTTON_USR, INPUT);// 12 on EVKIT
	pinMode(BUTTON_WIFI_RESET, INPUT);
	/*---PSU control defaults to High-Z : External jumper control*/
	pinMode(PSU_MODE_SEL, INPUT);

	// set them to known states
	digitalWrite(PWM_RED, LOW);
	digitalWrite(PWM_GREEN, LOW);
	digitalWrite(PWM_BLUE, LOW);
	digitalWrite(CS_SD, HIGH); // deselct SD card
}

/*set the Powersupply to a specific mode
POWER_EXT : output is decided by the Jumper setting
POWER_5V : Jumper removed, PSU set to 5V
POWER_12V : Jumper removed, PSU set to 12V ( 5V pin will be GND )
Default mode is POWER_EXT*/
void setPowerMode(powerModeEnum mode) {
	switch (mode)
	{
	case POWER_EXT:
		pinMode(PSU_MODE_SEL, INPUT);
		break;
	case POWER_5V:
		pinMode(PSU_MODE_SEL, OUTPUT);
		digitalWrite(PSU_MODE_SEL, LOW);
		break;
	case POWER_12V:
		pinMode(PSU_MODE_SEL, OUTPUT);
		digitalWrite(PSU_MODE_SEL, HIGH);
		break;
	default:
		break;
	}
}

/*reads the LED supply voltage*/
double readVled() {
	//voltage line sense : 4096ADC | 3v3 = 14 VLED, ~ 1477ADC | 1.190V = 5Vled
	double voltage;
	uint16_t adcReading = analogRead( V_LED_MON);
	// compute voltage
	voltage = (( (double)adcReading/4096)*V_REF_ADC)*(VDIV_RATIO_INV);
	return voltage;
}