#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

#include <Adafruit_NeoPixel.h>

#define SECONDS // comment if not using seconds bar (6 LEDs below the other strips)

RTC_DS1307 RTC; // RTC connected via I2C (on atmega328 SDA: A4, SCL: A5)

// pins for WS2812 digital LEDs
int hours_pin = 9;
int minutes_pin = 8;
#ifdef SECONDS
  int seconds_pin = 7;
#endif

// WS2812 strips
Adafruit_NeoPixel hours = Adafruit_NeoPixel(8, hours_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minutes = Adafruit_NeoPixel(8, minutes_pin, NEO_GRB + NEO_KHZ800);


// pin for DST on / off switch
int dst = 2;

// color array for base and "on" color
//                              base                      on
uint32_t colors[] = {hours.Color(0,0,255), hours.Color(255, 0, 0)};


void setup() {
  Serial.begin(57600);

  // set up connection to RTC
  Wire.begin();
  RTC.begin();
  // set necessary pins modes
  pinMode(hours_pin, OUTPUT);
  pinMode(minutes_pin, OUTPUT);
  #ifdef SECONDS
    pinMode(seconds_pin, OUTPUT);
  #endif
  // the DST is input of course, but the PIN 3 (next to it) needs to be output
  // & high in order to be able to reliably detect the switch setting
  pinMode(dst, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}

void loop() {
  DateTime t = RTC.now();
  Serial.println("got time");

  // get hours and display them
  show_number(hours, t.hour());

  // get minutes and display them
  show_number(minutes, t.minute());

  delay(1000);
}

void show_number(Adafruit_NeoPixel strip, int number) {
  // separate 10 and 1 digits
  uint8_t tens = number / 10; // get the 10-digit
  uint8_t ones = number % 10; // get the 1-digit
  Serial.println();
  // show the ones
  for(int i = 0; i < 4; i++) {
    uint8_t bit = (ones >> i) % 2;
    strip.setPixelColor(i, colors[bit]);
  }
  // show the tens
  for(int i = 0; i < 4; i++) {
    uint8_t bit = (tens >> i) % 2;
    strip.setPixelColor(i + 4, colors[bit]);
  }
  // apply
  strip.show();
}
