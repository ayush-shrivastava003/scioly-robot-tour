#include "TimerOne.h"
const byte LEFT_ENCODER = 3;
const byte RIGHT_ENCODER = 2;
#define RIGHT_PWM 5 // pin for right motor's speed (pulse width modulation)
#define LEFT_PWM 6 // pin for left motor's speed (pulse width modulation)
#define DIR_RIGHT1 7 // 1 of 2 direction pins for the right motor
#define DIR_RIGHT2 8 // 2 of 2 direction pins for the right motor
#define DIR_LEFT1 9 // 1 of 2 direction pins for the left motor
#define DIR_LEFT2 10 // 2 of 2 direction pins for the left motor
unsigned int counterLeft = 0;
unsigned int counterRight = 0;
const float SLOTS = 20.0;
const float WHEEL_DIAMETER = 2.7; // in cm

void countLeft() {
  counterLeft++;
}

void countRight() {
  counterRight++;  
}

//void onInterrupt() {
//  Timer1.detachInterrupt();
//  Serial.print("Motor speed: ");
//  float rpm = (counterLeft / slots) * 60.0;
//  Serial.print(rpm); Serial.println(" rpm");
//  counter = 0;
//  Timer1.attachInterrupt(ISRTimerOne);
//}

int convertDist(int dist) {
  float circumference = WHEEL_DIAMETER * 3.14159265358979323846;
  float stepsPerTurn = SLOTS / circumference;
  return (int)(dist * stepsPerTurn);
}

void forward(int dist) {
  int counts = convertDist(dist);
  Serial.print("counts: "); Serial.println(counts);
  counterLeft = 0;
  counterRight = 0;

  digitalWrite(DIR_LEFT1, LOW);
  digitalWrite(DIR_LEFT2, HIGH);
  digitalWrite(DIR_RIGHT1, LOW);
  digitalWrite(DIR_RIGHT2, HIGH);

  while (counterLeft < counts && counterRight < counts) {
    Serial.print("left: "); Serial.println(counterLeft);
    if (counterLeft < counts) analogWrite(LEFT_PWM, 150);
    else analogWrite(LEFT_PWM, 0);

    Serial.print("right: "); Serial.println(counterRight);
    if (counterRight < counts) analogWrite(RIGHT_PWM, 150);
    else analogWrite(RIGHT_PWM, 0);
  }

  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
  counterLeft = 0;
  counterRight = 0;
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), counterLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), counterRight, RISING);
  
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(DIR_RIGHT1, OUTPUT);
  pinMode(DIR_RIGHT2, OUTPUT);
  pinMode(DIR_LEFT1, OUTPUT);
  pinMode(DIR_LEFT2, OUTPUT);

  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);

  forward(10);
 
}
void loop() {
  // put your main code here, to run repeatedly:

}
