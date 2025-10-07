#include <NewPing.h>

// #include <Distance.h>


/*
*  L298P Motor Shield
*  Code for exercising the L298P Motor Control portion of the shield
*  The low level motor control logic is kept in the function 'Motor'
*/
// The following pin designations are fixed by the shield
int const BUZZER = 4;
//  Motor A
int const ENA = 10;
int const INA = 12;
//  Motor B
int const ENB = 11;
int const INB = 13;

int const MIN_SPEED = 27;    // Set to minimum PWM value that will make motors turn
int const ACCEL_DELAY = 50;  // delay between steps when ramping motor speed up or down.

int const TRIGGER_PIN = 9;
int const ECHO_PIN =10;

NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, 400);
//===============================================================================
//  Initialization
//===============================================================================
void setup() {
  pinMode(ENA, OUTPUT);  // set all the motor control pins to outputs
  pinMode(ENB, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  // ultrasonic.begin();
  Serial.begin(9600);  // Set comm speed for serial monitor messages
}
//===============================================================================
//  Main
//===============================================================================

/* 
Motor A = left motor
Motor B = right motor

Forward
Backward
Turnleft
Turnright
Stop
 */
void loop() {
  // Run both motors Forward at 75% power
  // forward(75);
  // delay(3000);
  // turnLeft(75);
  // delay(3000);
  stop();
  // delay(4000);
  Serial.println(ultrasonic.ping_cm());
}

void stop() {
  Motor('C', 'F', 0);
}

void turnLeft(int speed) {
  Motor('A', 'F', speed);
  Motor('B', 'R', speed);
}

void turnRight(int speed) {
  Motor('A', 'R', speed);
  Motor('B', 'F', speed);
}

void backward(int speed) {
  Motor('A', 'R', speed);
  Motor('B', 'R', speed);
}

void forward(int speed) {
  Motor('A', 'F', speed);
  Motor('B', 'F', speed);
}

/*
 * Motor function does all the heavy lifting of controlling the motors
 * mot = motor to control either 'A' or 'B'.  'C' controls both motors.
 * dir = Direction either 'F'orward or 'R'everse
 * speed = Speed.  Takes in 1-100 percent and maps to 0-255 for PWM control.  
 * Mapping ignores speed values that are too low to make the motor turn.
 * In this case, anything below 27, but 0 still means 0 to stop the motors.
 */
void Motor(char mot, char dir, int speed) {
  // remap the speed from range 0-100 to 0-255
  int newspeed;
  if (speed == 0)
    newspeed = 0;  // Don't remap zero, but remap everything else.
  else
    newspeed = map(speed, 1, 100, MIN_SPEED, 255);

  switch (mot) {
    case 'A':  // Controlling Motor A
      if (dir == 'F') {
        digitalWrite(INA, HIGH);
      } else if (dir == 'R') {
        digitalWrite(INB, LOW);
      }
      analogWrite(ENA, newspeed);
      break;

    case 'B':  // Controlling Motor B
      if (dir == 'F') {
        digitalWrite(INB, HIGH);
      } else if (dir == 'R') {
        digitalWrite(INB, LOW);
      }
      analogWrite(ENB, newspeed);
      break;

    case 'C':  // Controlling Both Motors
      if (dir == 'F') {
        digitalWrite(INA, HIGH);
        digitalWrite(INB, HIGH);
      } else if (dir == 'R') {
        digitalWrite(INA, LOW);
        digitalWrite(INB, LOW);
      }
      analogWrite(ENA, newspeed);
      analogWrite(ENB, newspeed);
      break;
  }
  // Send what we are doing with the motors out to the Serial Monitor.

  // Serial.print ("Motor: ");
  // if (mot=='C')
  //     Serial.print ("Both");
  //   else
  //     Serial.print (mot);
  // Serial.print ("t Direction: ");
  // Serial.print (dir);
  // Serial.print ("t Speed: ");
  // Serial.print (speed);
  // Serial.print ("t Mapped Speed: ");
  // Serial.println (newspeed);
}