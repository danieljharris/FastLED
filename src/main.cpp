#include <Arduino.h>
#include "FastLED.h"
#include "FastLED_RGBW.h"
#include "LED.h"
#include "OTA.h"

void setup() { 
  Serial.begin(115200);

  enableWiFi("OFVKAXMCJXJO", "2MAK=Tj%H3y4");
  enableOTA("RGBWW IC 1");

  LED_Setup();
  clearAll();
}

void loop() {
  clearAll();
  ArduinoOTA.handle();

  // Turn the LED on, then pause
  // leds[0] = CRGB::Red;
  // leds[0] = CRGB::Green;
  // leds[0] = CRGB::Blue;


  // // leds[0] = CRGBW(0, 0, 0, 255);
  // // leds[298] = CRGBW(0, 0, 0, 255);
  // // leds[299] = CRGBW(0, 0, 0, 255);

  // leds[0] = CRGBW(0, 0, 0, 1);
  // leds[298] = CRGBW(0, 0, 0, 1);
  // leds[299] = CRGBW(0, 0, 0, 1);

  // // leds[0] = CRGBW(0, 0, 0, 255);
  // // leds[1] = CRGBW(0, 0, 0, 255);
  // FastLED.show();
  // delay(500);

  // // Now turn the LED off, then pause
  // leds[0] = CRGB::Black;
  // leds[298] = CRGB::Black;
  // leds[299] = CRGB::Black;

  

  // FastLED.show();
  // delay(500);

  // rainbowLoop();


  // flow(CRGB(0, 0, 10));
  // flow(CRGBW(0, 0, 0, 0), 10, EndToStart);

  // bounce(CRGBW(255, 0, 255, 0));
  // bounce(CRGBW(0, 0, 0, 10), 10, EndToStart);

  // clearAll();
  // delay(500);


  // flow(CRGBW(255, 255, 255, 255));
  // flow(CRGB(255, 255, 255));
  // flow(CRGBW(255, 0, 255, 0));
  // fill(CRGBW(255, 0, 255, 0));
  // fill(CRGB(255, 0, 255));

  // delay(500);


  // clearAll();

  // delay(500);

  // delay(500000000);

    // set(0, CRGBW(0, 0, 0, 255));
    // set(298, CRGBW(0, 0, 0, 255));
    // set(299, CRGBW(255, 0, 0, 255));
    // set(299, CRGBW(255, 255, 255, 255));
    // set(227, CRGBW(0, 0, 5, 0));

    // delay(500);
    // clearAll();
    // delay(500);

    // moveWidth(CRGBW(0, 0, 0, 50), 5, 5, EndToStart);
    // moveWidth(CRGBW(255, 0, 255, 0), 5, 5, EndToStart);
    // bounce(CRGBW(0, 0, 0, 50), 10, EndToStart);

    // fill(CRGBW(10, 0, 10, 0));

    // alternate(CRGBW(10, 0, 0, 0), CRGBW(0, 10, 0, 0));
    // alternate(CRGBW(10, 0, 0, 0), CRGBW(0, 10, 0, 0), CRGBW(0, 0, 10, 0));
    // alternate(CRGBW(10, 0, 0, 0), CRGBW(0, 10, 0, 0), CRGBW(0, 0, 10, 0), CRGBW(0, 0, 0, 10));

    // clearAll();


    // adder(CRGBW(0, 0, 0, 10), 1);
    // adder(CRGBW(0, 0, 0, 10), 1, EndToStart);

    // adderWidth(CRGBW(0, 0, 0, 10), 100, 1);
    // adderWidth(CRGBW(0, 0, 0, 10), 10, 1, EndToStart);



    moveWidth(CRGBW(0, 0, 0, 50), random(5, 10), random(1, 3), EndToStart);
}