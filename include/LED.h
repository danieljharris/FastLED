#include <Arduino.h>
#include <ArduinoOTA.h>
#include "FastLED.h"
#include "FastLED_RGBW.h"

#define NUM_LEDS       300 // 400
// #define NUM_LEDS       600 // 131.6% UNO RAM useage...
#define LED_TYPE   WS2812B
#define COLOR_ORDER    RGB
// #define DATA_PIN        10
#define DATA_PIN        16


CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];


enum direction {
    StartToEnd,
    EndToStart
    };


void LED_Setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
}

int random(int min, int max) {
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void delayAndUpdate(unsigned long ms) {
    delay(ms);
    ArduinoOTA.handle();
}


void set(int index, CRGBW color) {
    if(index >= 0 && index < NUM_LEDS) {
        leds[index] = color;
        FastLED.show();
    }
}
void set(int index, CRGB color) {
    set(index, CRGBW(color));
}


void flow(CRGBW c, int stepSpeed = 10, direction dir = StartToEnd) {
    if (dir == StartToEnd) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = c;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
    }
    else {
        for (int i = NUM_LEDS - 1; i >= 0; i--) {
            leds[i] = c;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
    }
}
void flow(CRGB c, int stepSpeed = 10, direction dir = StartToEnd) {
    flow(CRGBW(c), stepSpeed, dir);
}


void bounce(CRGBW c, int stepSpeed = 10, direction dir = StartToEnd) {
    flow(c, stepSpeed, dir);
    flow(0, stepSpeed, dir == StartToEnd ? EndToStart : StartToEnd);
}
void bounce(CRGB c, int stepSpeed = 10, direction dir = StartToEnd) {
    bounce(CRGBW(c), stepSpeed, dir);
}


void move(CRGBW c, int stepSpeed = 10, direction dir = StartToEnd) {
    if (dir == StartToEnd) {
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = c;
            leds[i - 1] = 0;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
        leds[NUM_LEDS - 1] = 0;
    }
    else {
        for (int i = NUM_LEDS - 1; i >= 0; i--) {
            leds[i] = c;
            leds[i + 1] = 0;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
        leds[0] = 0;
    }
}


void moveWidth(CRGBW c, int width = 10, int stepSpeed = 10, direction dir = StartToEnd) {
    if (dir == StartToEnd) {
        for (int i = 0; i < NUM_LEDS + width; i++) {
            if (i < NUM_LEDS) leds[i] = c;
            if (i - width - 1 > 0) leds[i - width - 1] = 0;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
    }
    else {
        for (int i = NUM_LEDS; i >= 0 - width; i--) {
            if (i >= 0) leds[i] = c;
            if (i + width + 1 < NUM_LEDS) leds[i + width + 1] = 0;
            FastLED.show();
            delayAndUpdate(stepSpeed);
        }
    }
}


void adder(CRGBW c, int stepSpeed = 10, direction dir = StartToEnd) {
    if (dir == StartToEnd) {
        for (int max = NUM_LEDS; max > 0; max--) {
            for (int i = 0; i < max; i++) {
                leds[i] = c;
                if (i - 1 >= 0) leds[i - 1] = 0;
                FastLED.show();
                delayAndUpdate(stepSpeed);
            }
        }
    }
    else {
        for (int min = 0; min < NUM_LEDS; min++) {
            for (int i = NUM_LEDS; i >= min; i--) {
                leds[i] = c;
                if (i + 1 < NUM_LEDS) leds[i + 1] = 0;
                FastLED.show();
                delayAndUpdate(stepSpeed);
            }
        }
    }
}
void adderWidth(CRGBW c, int width = 10, int stepSpeed = 10, direction dir = StartToEnd) {
    if (dir == StartToEnd) {
        for (int max = NUM_LEDS; max > 0; max -= width) {
            for (int i = 0; i < max; i++) {
                if (i < NUM_LEDS) leds[i] = c;
                if (i - width - 1 >= 0) leds[i - width - 1] = 0;
                FastLED.show();
                delayAndUpdate(stepSpeed);
            }
        }
    }
    else {
        for (int min = 0; min < NUM_LEDS; min += width) {
            for (int i = NUM_LEDS; i >= min; i--) {
                if (i >= 0) leds[i] = c;
                if (i + width + 1 < NUM_LEDS) leds[i + width + 1] = 0;
                FastLED.show();
                delayAndUpdate(stepSpeed);
            }
        }
    }
}


void fill(CRGBW c) {
    for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = c;
    }
    FastLED.show();
}
void fill(CRGB c) {
    fill(CRGBW(c));
}


void clearAll() {
    fill(0);
}


void rainbow() {
	static uint8_t hue;
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i] = CHSV((i * 256 / NUM_LEDS) + hue, 255, 255);
	}
	FastLED.show();
	hue++;
}
void rainbowLoop() {
	long millisIn = millis();
	long loopTime = 5000; // 5 seconds
	while(millis() < millisIn + loopTime){
		rainbow();
		delayAndUpdate(5);
	}
}


void alternate(CRGBW c1, CRGBW c2, int stepSpeed = 200) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = i % 2 == 0 ? c1 : c2;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = i % 2 == 0 ? c2 : c1;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);
}
void alternate(CRGBW c1, CRGBW c3, CRGBW c2, int stepSpeed = 200) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 3 == 0) leds[i] = c1;
        else if (i % 3 == 1) leds[i] = c2;
        else leds[i] = c3;
    }
    
    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 3 == 1) leds[i] = c1;
        else if (i % 3 == 2) leds[i] = c2;
        else leds[i] = c3;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 3 == 2) leds[i] = c1;
        else if (i % 3 == 0) leds[i] = c2;
        else leds[i] = c3;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);
}
void alternate(CRGBW c1, CRGBW c4, CRGBW c3, CRGBW c2, int stepSpeed = 200) {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 4 == 0) leds[i] = c1;
        else if (i % 4 == 1) leds[i] = c2;
        else if (i % 4 == 2) leds[i] = c3;
        else leds[i] = c4;
    }
    
    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 4 == 1) leds[i] = c1;
        else if (i % 4 == 2) leds[i] = c2;
        else if (i % 4 == 3) leds[i] = c3;
        else leds[i] = c4;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 4 == 2) leds[i] = c1;
        else if (i % 4 == 3) leds[i] = c2;
        else if (i % 4 == 0) leds[i] = c3;
        else leds[i] = c4;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);

    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 4 == 3) leds[i] = c1;
        else if (i % 4 == 0) leds[i] = c2;
        else if (i % 4 == 1) leds[i] = c3;
        else leds[i] = c4;
    }

    FastLED.show();
    delayAndUpdate(stepSpeed);
}