#include <Servo.h>

#define US_ECHO 2 // pin (D2) for the ultrasonic sensor's echo
#define US_TRIG 3 // pin (D3) for the ultrasonic sensor's ???

#define SERVO 11 // pin for servo

#define RIGHT_PWM 5 // pin for right motor's speed (pulse width modulation)
#define LEFT_PWM 6 // pin for left motor's speed (pulse width modulation)
#define DIR_RIGHT1 7 // 1 of 2 direction pins for the right motor
#define DIR_RIGHT2 8 // 2 of 2 direction pins for the right motor
#define DIR_LEFT1 9 // 1 of 2 direction pins for the left motor
#define DIR_LEFT2 10 // 2 of 2 direction pins for the left motor

Servo servo;
int OBSTACLE_DIST = 20;

void setSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(LEFT_PWM, leftSpeed);
  analogWrite(RIGHT_PWM, rightSpeed);  
}

void stop() {
  digitalWrite(DIR_LEFT1, LOW);
  digitalWrite(DIR_LEFT2, LOW);

  digitalWrite(DIR_RIGHT1, LOW);
  digitalWrite(DIR_RIGHT2, LOW);
}

void forward() {
  digitalWrite(DIR_LEFT1, LOW);
  digitalWrite(DIR_LEFT2, HIGH);

  digitalWrite(DIR_RIGHT1, LOW);
  digitalWrite(DIR_RIGHT2, HIGH);
}

void forward(int t) {
  forward();
  delay(t);
  stop();
}

void backward() {
  Serial.write("BACK");
  digitalWrite(DIR_LEFT1, HIGH);
  digitalWrite(DIR_LEFT2, LOW);

  digitalWrite(DIR_RIGHT1, HIGH);
  digitalWrite(DIR_RIGHT2, LOW);    
}

void backward(int t) {
  backward();
  delay(t);
  stop();
}

void left() {
  digitalWrite(DIR_LEFT1, HIGH);
  digitalWrite(DIR_LEFT2, LOW);

  digitalWrite(DIR_RIGHT1, LOW);
  digitalWrite(DIR_RIGHT2, HIGH);
}

void left(int t) {
  left();
  delay(t);  
  stop();
}

void right() {
  digitalWrite(DIR_LEFT1, LOW);
  digitalWrite(DIR_LEFT2, HIGH);

  digitalWrite(DIR_RIGHT1, HIGH);
  digitalWrite(DIR_RIGHT2, LOW);  
}

void right(int t) {
  right();
  delay(t);
  stop();
}

// Calculates the distance ahead of the ultrasonic sensor in centimeters.
int usDistance() {
  digitalWrite(US_TRIG, LOW);
  delayMicroseconds(5); // ensure that NO signals are being emitted by keeping voltage low
  digitalWrite(US_TRIG, HIGH);
  delayMicroseconds(15); // emit ultrasonic sound for 10 microseconds
  digitalWrite(US_TRIG, LOW);
  
  long echoTime = pulseIn(US_ECHO, HIGH);
  int dist = (echoTime * 0.0343) / 2; // 0.0343 is the speed of sound in cm/microsecond
  Serial.println(dist);
  return dist;
}

boolean checkSides() {
  stop();
  servo.write(0);
  delay(250);
  
  if (usDistance() > OBSTACLE_DIST) {
    Serial.write("RIGHT");
    right(375);
    servo.write(90);
    return true;
  }
  
  servo.write(180);
  delay(400);
  if (usDistance() > OBSTACLE_DIST) {
    Serial.write("LEFT");
    left(375);
    servo.write(90);
    return true;
  }

  servo.write(90);
  return false;
}

void setup() {
  // ultrasonic sensor setup
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);

  // motor setup
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(DIR_RIGHT1, OUTPUT);
  pinMode(DIR_RIGHT2, OUTPUT);
  pinMode(DIR_LEFT1, OUTPUT);
  pinMode(DIR_LEFT2, OUTPUT);
  setSpeed(250, 250); // 200 is recommended as 100 is not enough voltage to move the motors

  // servo setup
  servo.attach(SERVO);
  servo.write(90);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (usDistance() > OBSTACLE_DIST) forward();
  if (usDistance() > OBSTACLE_DIST) return; // this might seem redundant, but sometimes there's a random 0 returned that breaks the loop
  
  Serial.println("STOP");
  if (checkSides()) return;
   else while (!checkSides()) backward(500);

}
