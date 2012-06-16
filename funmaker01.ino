#include <Wire.h>

#include <math.h>
#include "nunchuck.h"

#define MAXANGLE 90
#define MINANGLE -90
#define SPKR 8

//musical note table
#define PAG 392
#define PAGb 370
#define PAF 349
#define PAE 330
#define PAD 294
#define PAC 262

WiiChuck chuck = WiiChuck();

int read_temperature() {
  return 48;
}

void make_noise(int n, int dur) {
  tone(SPKR, n);
  delay(dur);
  noTone(SPKR);
  delay(100);
}

void pips() {
  make_noise(440, 100);
  make_noise(320, 100);
  make_noise(440, 100);
  make_noise(320, 100);
  //delay(500);
}

void cry() {
  make_noise(PAG, 340);
  make_noise(PAGb, 390);
  make_noise(PAF, 340);
  make_noise(PAE, 500);
}
  
void setup() {
  cry();
  chuck.begin();
  chuck.update();
}

int sound = 0;
void loop() {
  delay(20);
  chuck.update();
  if (chuck.zPressed()) sound=!sound;
  if (chuck.cPressed()) pips();
  if (chuck.downJoy()) cry();
  int pitch = chuck.readPitch();
  if (pitch < 0) { pips(); return; }
  if (sound)
    tone(SPKR, pitch+50);
  else
    noTone(SPKR);
}
