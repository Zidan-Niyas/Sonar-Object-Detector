// Includes the Servo library
#include <Servo.h>

// Constants
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int SERVO_PIN = 12;
const int MIN_ANGLE = 15;
const int MAX_ANGLE = 165;
const int DELAY_TIME = 20;
const float SOUND_SPEED = 0.034;

Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(SERVO_PIN); // Defines on which pin is the servo motor attached
  Serial.println("Setup completed");
}

void loop() {
  static int direction = 1; // 1 for increasing angle, -1 for decreasing angle
  static int angle = MIN_ANGLE;
  angle += direction;
  if (angle >= MAX_ANGLE || angle <= MIN_ANGLE) {
    direction *= -1; // Change direction when reaching maximum or minimum angle
  }
  myServo.writeMicroseconds(map(angle, MIN_ANGLE, MAX_ANGLE, 500, 2500)); // Use writeMicroseconds() for more precise control

  // Measure distance using the ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) * SOUND_SPEED;

  // Print the distance to the serial monitor
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.println(".");

  delay(DELAY_TIME);
}
