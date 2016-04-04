
/*LED patterns / animations for addressable strip*/
void LEDanimations() {
	// TODO : // keep the framerate modest

	// Call the current pattern function once, updating the 'leds' array
	gPatterns[gPatternNumber]();

	// send the 'leds' array out to the actual LED strip
	showLEDs(); // uses PWM pins and Fastled.show()
	 // NOTE : could use EVERY_N_MILLISECONDS here to control framerate without using delay

	 // FastLED.delay(1000 / FRAMES_PER_SECOND);
	EVERY_N_MILLISECONDS(20) { gHue++; } // slowly cycle the "base color" through the rainbow
}

/*LED patterns - they must be non- blocking - do not use "delay" in them*/
/*default set is from  FastLed's 100 line demoreel  example*/

/* Rainbow */
void pattern_0() {
	// FastLED's built-in rainbow generator
	fill_rainbow(leds, numLEDs, gHue, 7);
}

/* Rainbow with glitter */
void pattern_1() {
	// built-in FastLED rainbow, plus some random sparkly glitter
	fill_rainbow(leds, numLEDs, gHue, 7);
	/* add some glitter*/
	addGlitter(80);
}

/*Confetti*/
void pattern_2() {
	// random colored speckles that blink in and fade smoothly
	fadeToBlackBy(leds, numLEDs, 10);
	int pos = random16(numLEDs);
	leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

/*sinelon*/
void pattern_3() {
	// a colored dot sweeping back and forth, with fading trails
	fadeToBlackBy(leds, numLEDs, 20);
	int pos = beatsin16(13, 0, numLEDs);
	leds[pos] += CHSV(gHue, 255, 192);
}

/*bpm*/
void pattern_4() {
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
	uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
	for (int i = 0; i < numLEDs; i++) { 
		// leds[i] = CHSV( gHue + (i * 2), beat - gHue + (i * 10),255 );
		leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
	}
}

/*juggle*/
void pattern_5() {
	// eight colored dots, weaving in and out of sync with each other
	fadeToBlackBy(leds, numLEDs, 20);
	byte dothue = 0;
	for (int i = 0; i < 8; i++) {
		leds[beatsin16(i + 7, 0, numLEDs)] |= CHSV(dothue, 200, 255);
		dothue += 32;
	}
}


/*some "primitive" animatiosn used in others*/
void addGlitter(fract8 chanceOfGlitter)
{
	if (random8() < chanceOfGlitter) {
		leds[random16(numLEDs)] += CRGB::White;
	}
}


void meteorShower(byte meteorLength) {

	// show, delay

	// slide all the pixels down one in the array
	memmove8(&leds[1], &leds[0], (numLEDs - 1) * 3 );

	// increment the meteor display frame
	idex++;
	// make sure we don't drift into space
	if (idex > meteorLength) {
		idex = 0;
		// cycle through hues in each successive meteor tail
		gHue += 32;
	}

	// this switch controls the actual meteor animation, i.e., what gets placed in the
	// first position and then subsequently gets moved down the strip by the memmove above
	switch (idex) {
	case 0:
		leds[0] = CRGB(200, 200, 200);
		break;
	case 1:
		leds[0] = CHSV((gHue - 20), 255, 210);
		break;
	case 2:
		leds[0] = CHSV((gHue - 22), 255, 180);
		break;
	case 3:
		leds[0] = CHSV((gHue - 23), 255, 150);
		break;
	case 4:
		leds[0] = CHSV((gHue - 24), 255, 110);
		break;
	case 5:
		leds[0] = CHSV((gHue - 25), 255, 90);
		break;
	case 6:
		leds[0] = CHSV((gHue - 26), 160, 60);
		break;
	case 7:
		leds[0] = CHSV((gHue - 27), 140, 40);
		break;
	case 8:
		leds[0] = CHSV((gHue - 28), 120, 20);
		break;
	case 9:
		leds[0] = CHSV((gHue - 29), 100, 20);
		break;
	default:
		leds[0] = CRGB::Black;
	}

}