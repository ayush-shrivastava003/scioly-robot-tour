/*
 * Code to check that the ultrasonic sensor is connected and working. 
 * 
 * The ultrasonic sensor emits ultrasonic sounds and waits for them to be bounced back by an obstacle. Based on the
 * time it takes for those sounds to come back, the distance of an
 * obstacle ahead of the robot can be determined.
 */

#define US_ECHO 2 // pin for the ultrasonic's RECEIVER
#define US_TRIG 3 // pin for the ultrasonic's EMITTER

void setup() {
  pinMode(US_TRIG, OUTPUT); // indicate that we're only using the trigger pin to output stuff
  pinMode(US_ECHO, INPUT); // indicate that we're only using the echo pin to receive stuff

  Serial.begin(9600);
}

void loop() {
  digitalWrite(US_TRIG, LOW); // send a low voltage to the trigger to deactivate it
  delayMicroseconds(5); // make sure that it's off for a bit
  digitalWrite(US_TRIG, HIGH); // send a low voltage to the trigger to emit ultrasonic waves
  delayMicroseconds(15); // emit ultrasonic sound for 10 microseconds
  digitalWrite(US_TRIG, LOW); // turn off the emitter

  long echoTime = pulseIn(US_ECHO, HIGH); // measure the time it takes (in microseconds) for the sensor to detect the ultrasonic sound
  int dist = (echoTime * 0.0343) / 2; // 0.0343 is the speed of sound in cm/microsecond. divide by 2 to get the one-way distance
  Serial.print(dist); Serial.println(" cm");
}
