#include "FastLED.h"
#define NUM_LEDS 300
#define DATA_PIN A5
CRGB leds[NUM_LEDS];

int localMax = -1000;
int localMin = 1000;
int localMid = 0;
int localAverage;
int localDif;
int waitTime = 0;

int counter = 0;
int rainbowList [17] {15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255};
int rainbowSize = 17;
int type = 1;


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 100, 100);
  }
  FastLED.show();
}


void loop() {
  int a0 = analogRead(A0);

  if (a0 > localMax) {
    localMax = a0;
  }
  else if (a0 < localMin) {
    localMin = a0;
  }
  else {
    localAverage = (localAverage + a0) / 2;
  }
  localMid = localMax - localMin;

  localDif = localAverage - localMin;


  if (waitTime > 100) {
    if ((a0 > localDif + (a0 / 4)) || (a0 < localDif - (a0 / 4))) {
      changeColor();
      waitTime = 0;
    }

  }
  waitTime++;
}

void changeColor() {
  int r;
  if (type == 1) {
    if (counter < rainbowSize) {
      r = rainbowList[counter];

    }
  }
  else {
    counter = 0;
    r = rainbowList[counter];
  }

  FastLED.show();

}
