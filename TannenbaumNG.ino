/*
   TannenbaumNG (Tannenbaum Next Generation)
*/
#include "Adafruit_WS2801.h"
#include <Adafruit_NeoPixel.h>
#include "SPI.h" // Comment out this line if using Trinket or Gemma

Adafruit_WS2801 strip = Adafruit_WS2801(5);

#define PIN A1
#define NUMPIXELS 10
Adafruit_NeoPixel pix = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

volatile int LumVal = 0;
volatile bool IsDark = false;
volatile byte Red, Green, Blue;
int LastEL = 0;
int LEDLimit = 0;
int BrightLimit = 0;


//Timing
uint32_t ContLED = 0;
uint32_t ContPix = 0;
uint32_t ContPixFlash = 0;
uint32_t ContEL = 0;
uint32_t ContAD = 0;
uint32_t ContBoom = 0;
int LEDWait = 0;

#define EL_PAUSE 1500UL
#define LED_PAUSE 1500UL
#define PIX_PAUSE 2500UL
#define FLASH_PAUSE 1000UL
#define BOOM_PAUSE 23456UL
#define AD_PAUSE 666UL
#define LED_LONG_WAIT 50UL
#define LED_SHORT_WAIT 20UL
#define PIX_LONG_WAIT 50UL
#define PIX_SHORT_WAIT 20UL

#define MAX_PIX_HIGH 64
#define MAX_PIX_LOW 32
#define MAX_LED_HIGH 64
#define MAX_LED_LOW 16
#define STRING_LEN 5

typedef struct {
  byte Rot;
  byte Gruen;
  byte Blau;
  byte Status;
} LED;

LED OldLed[STRING_LEN];
LED NewLed[STRING_LEN];

LED OldPix[NUMPIXELS];
LED NewPix[NUMPIXELS];


void ELOff(void) {
  for (int i = 2; i < 10; i++)
    digitalWrite(i, LOW);
  delay(20);
}

void setup() {
  Serial.begin(115200);

  //EL-Interface
  pinMode(2, OUTPUT);  // channel A
  pinMode(3, OUTPUT);  // channel B
  pinMode(4, OUTPUT);  // channel C
  pinMode(5, OUTPUT);  // channel D
  pinMode(6, OUTPUT);  // channel E
  pinMode(7, OUTPUT);  // channel F
  pinMode(8, OUTPUT);  // channel G
  pinMode(9, OUTPUT);  // channel H

  //pinMode(PIN, OUTPUT); //NeoPixel

  //WS2801-Strip
  strip.begin();
  strip.show();
  //WS2811-Strip
  pix.begin();

  randomSeed(analogRead(A0));
  ELOff();
  StripOff();
  PixelOff();
  LastEL = 0;
}



void loop() {
  if (millis() > ContAD) {
    LumVal = analogRead(A0);
    if (LumVal < 200) {
      IsDark = true;
    }
    else if (LumVal > 300) {
      IsDark = false;
    }
    ContAD = millis() + AD_PAUSE;
    Serial.println("Licht");
  }
  //******** EL
  if (millis() > ContEL) {
    if (IsDark) {
      digitalWrite(LastEL, LOW);
      LastEL = (int)random(2, 10);
      delay(20);
      digitalWrite(LastEL, HIGH);
    }
    else {
      ELOff();
    }
    ContEL = millis() + EL_PAUSE + random(-500, 100);
  }

  //******* WS2801 Strip
  if (millis() > ContLED) {
    if (IsDark) {
      for (int i = 0; i < (STRING_LEN + NUMPIXELS); i++) {
        if (i < STRING_LEN) {
          while (!OldToNew(i)) {
            delay(LED_LONG_WAIT);
          }
        }
        else {
          while (!OldToNewPix(i - STRING_LEN)) {
            delay(LED_LONG_WAIT);
          }
        }
      }
    }
    else {
      for (int i = 0; i < (STRING_LEN + NUMPIXELS); i++) {
        if (i < STRING_LEN) {
          while (!OldToNew(i)) {
            delay(LED_SHORT_WAIT);
          }
        }
        else {
          while (!OldToNewPix(i - STRING_LEN)) {
            delay(LED_SHORT_WAIT);
          }
        }
      }
    }

    for (int i = 0; i < STRING_LEN; i++) {
      GetRandomLED();
    }
    for (int i = 0; i < NUMPIXELS; i++) {
      GetRandomPixel();
    }
    ContLED = millis() + LED_PAUSE + random(-500, 100);
  }

  //******** WS2811-Flash oder Boom!!
  if (millis() > ContPixFlash) {
    if (IsDark) {
      FlashFirework();
      ContPixFlash = millis() + PIX_PAUSE + random(-250, 500);
    }
    else {
      Serial.println(millis());
      Boom();
      ContPixFlash = millis() + (BOOM_PAUSE) + random(-2500, 5000);
    }
  }
}

