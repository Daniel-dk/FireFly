

/*check the button states and handle any callbacks*/
void buttonTick() {
	userButton.tick();
	wifiButton.tick();
}


/*initialise the OneButton objects*/
void initButtons() {

	// link the User button functions.
	userButton.attachClick(clickUserButton);
	userButton.attachDoubleClick(doubleclickUserButton);
	//userButton.attachLongPressStart(longPressStartUserButton);
	userButton.attachLongPressStop(longPressStopUserButton);
	userButton.attachDuringLongPress(longPressUserButton);

	// link the WiFi button functions.
	//wifiButton.attachClick(clickWifiButton);
	//wifiButton.attachDoubleClick(doubleclickWifiButton);
	wifiButton.attachLongPressStart(longPressStartWifiButton); // notify about WiFi reset - flash RED : TODO
	wifiButton.attachLongPressStop(longPressStopWifiButton);   // set Wifi back to defualt and reset the system
	//wifiButton.attachDuringLongPress(longPressWifiButton);
}



/*Callbacks*/
/* Click User Button once*/
void clickUserButton() {
	Serial.println(F("clickUserButton()"));
	// add one to the current pattern number, and wrap around at the end
	//gPatternNumber = (gPatternNumber++) % MAX_PATTERN_IDX;
	gPatternNumber = (gPatternNumber + 1) % ARRAY_SIZE(gPatterns);
	Serial.println(F("pattern is now : "));
	Serial.println(gPatternNumber);
}

/* Click WiFi Button once*/
void clickWifiButton() {
	Serial.println(F("clickWifiButton()"));
}

/* Click User Button Twice*/
void doubleclickUserButton() {
	Serial.println(F("doubleclickUserButton()"));
}

/* Click WiFi Button Twice*/
void doubleclickWifiButton() {
	Serial.println(F("doubleclickWifiButton()"));
}


/*Long press is detected*/
void longPressStartUserButton() {
	Serial.println(F("longPressStartUserButton()"));
}

/* Long press is detected*/
void longPressStartWifiButton() {
	Serial.println(F("longPressStartWifiButton()"));
}



/*Long press is ongoing*/
void longPressUserButton() {
	 // change systen brightness and wrap around at the end
	ledBrightness = (ledBrightness + 1) % 255;

	FastLED.setBrightness(ledBrightness);
	showLEDs();
	Serial.print(F("Brightness changed to :"));
	Serial.print(ledBrightness);
}

/* Long press is ongoing*/
void longPressWifiButton() {
	Serial.println(F("longPressWifiButton()"));
}


/*Long press is ended*/
void longPressStopUserButton() {
	Serial.println(F("longPressStopUserButton()"));
}

/* Long press is ended*/
void longPressStopWifiButton() {
	Serial.println(F("longPressStopWifiButton()"));
	// set Wifi back to defualt and reset the system
	wifiSettings_e = WIFI_DEFAULT;
	// reset

}