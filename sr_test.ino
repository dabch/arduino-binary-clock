#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC; // RTC connected via I2C

// Pin connected to ST_CP of 74HC595
int latch = 12;
// Pin connected to SH_CP of minutes
int clockMin = 8;
// Pin connected to SH_CP of hours
int clockHrs = 9;
// Pin connected to DS of 74HC595
int data = 11;

void setup() {
  Serial.begin(57600);

  // set up connection to RTC
  Wire.begin();
  RTC.begin();
  //set pins to output so you can control the shift register
  pinMode(latch, OUTPUT);
  pinMode(clockMin, OUTPUT);
  pinMode(clockHrs, OUTPUT);
  pinMode(data, OUTPUT);

  Serial.println(clockMin);
  Serial.println(clockHrs);

}

void loop() {
  DateTime t = RTC.now();
  Serial.println("got time");

  // get hours and shift them out
  uint8_t hrs = t.hour();
  uint8_t hrs_10 = hrs / 10; // get the 10-digit
  uint8_t hrs_1 = hrs % 10; // get the 1-digit
  Serial.print(hrs_10);
  Serial.print(" ");
  Serial.print(hrs_1);
  Serial.print(" : ");
  // shift those out

  shiftOut(data, clockHrs, MSBFIRST, hrs_10);
  shiftOut(data, clockHrs, MSBFIRST, hrs_1);

  // get minutes and shift them out
  uint8_t min = t.minute();
  uint8_t min_10 = min / 10; // get the 10-digit
  uint8_t min_1 = min % 10; // get the 1-digit
  Serial.print(min_10);
  Serial.print(" ");
  Serial.println(min_1);
  // shift those out
  shiftOut(data, clockMin, MSBFIRST, min_10);
  shiftOut(data, clockMin, MSBFIRST, min_1);

  // display all of it
  pulse(latch);

  delay(1000);
}

/*
* provides a pulse (HIGH-LOW) on one pin
* frequently needed with shift registers
*/
void pulse(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}
