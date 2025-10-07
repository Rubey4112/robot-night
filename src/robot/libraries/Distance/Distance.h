/*
 * Distance.h - Library for flashing getting distance from HC-SR04.
 * Created by Toan Do, October 3, 2025.
 * Released into the public domain.
 */

#ifndef Distance_h
#define Distance_h

#include "Arduino.h"

class Distance {
  public:
    Distance(int trig, int echo);
    void begin();
    int distance();
  private:
    int _trigPin;
    int _echoPin;
    long _duration;
    int _distance;
};

#endif