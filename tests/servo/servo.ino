// This code verifies that the servo motor is properly connected and working.

#include <Servo.h>

#define SERVO_PIN 11 // for me this pin is 11 but it'll change based on which kit you're using.

Servo servo; // initialize the servo object

void setup() {
  servo.attach(SERVO_PIN); // tell the obj that the servo is connected to pin SERVO_PIN
  servo.write(90); // set the servo to 90 degrees to make it face forward.

  Serial.begin(9600); // start the serial monitor (button on top right)
}

void loop() {
  for (int i = 0; i <= 180; i++) {
    servo.write(i); // set the servo to i degrees
    Serial.println(i); // write it to the serial monitor
    delay(10); // wait a bit so the servo turns slowly
  }

  for (int i = 180; i >= 0; i++) {
    servo.write(i);
    Serial.println(i);
    delay(10);  
  }
  
}
