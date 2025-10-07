/*
 * Distance.cpp - Library for flashing getting distance from HC-SR04.
 * Created by Toan Do, October 3, 2025.
 * Released into the public domain.
 */

#include "Arduino.h"
#include "Distance.h"

Distance::Distance(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
  _duration = 0;
  _distance = 0;
}

void Distance::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

int Distance::distance() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  _duration = pulseIn(_echoPin, HIGH);
  _distance = _duration * 0.034 / 2;

  return _distance;
}