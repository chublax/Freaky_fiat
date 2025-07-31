#include "ultrasonic.h"

// Motor A
int RIGHT_SPEED = 9; // Speed pin, ranges from 0 to 255 (ENA)
int RIGHT_F = 14; // Pin to move motor forwards (IN1)
int RIGHT_R = 15; // Pin to move motor backwards (IN2)
// Motor B
int LEFT_SPEED = 10; // Speed pin, ranges from 0 to 255 (ENB)
int LEFT_F = 16; // Pin to move motor forwards (IN3)
int LEFT_R = 17; // Pin to move motor backwards (IN4)

// IR sensor setup
const int irPin = 4;
const int ledPin = 13;


unsigned long duration = 50;
float dist = 700;

void setup() {
  // Setting up the serial monitor
  delay(5000);
  Serial.begin (9600);
  Serial.println("Setting pins for motors");
  // Setup all the motor control pins to outputs
  pinMode (RIGHT_SPEED, OUTPUT); pinMode (RIGHT_F, OUTPUT); pinMode (RIGHT_R, OUTPUT);
  pinMode (LEFT_SPEED, OUTPUT); pinMode (LEFT_F, OUTPUT) ; pinMode (LEFT_R, OUTPUT);
  
  // Setup IR sensor pins
  pinMode(irPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.println("IR sensor initialized");
  
  // Setup ultrasonic sensor
  setupUltrasonic();
}

int whiteCount = 0;

void loop() {
  // Check IR sensor and display color detection
  checkColorSensor();
  if (digitalRead(irPin) == HIGH) {
    whiteCount++;
  } else {
    whiteCount = 0;
  }

  duration = measureDistance();
  dist = calculateDistanceCm(duration);

  if (whiteCount > 5) {
    driveBackward();
    delay(500);
  } else if (dist < 400) {
    // RAM!!!!!
    driveForward();
  } else {
    // Search
    turnRight();
  }
  // Small delay to prevent overwhelming the serial monitor
  delay(50);
}


void checkColorSensor() {
  int state = digitalRead(irPin);
  
  if (state == LOW) {
    // LOW typically means white/light surface detected
    digitalWrite(ledPin, HIGH);  // Turn on LED
    Serial.println("BLACK DETECTED");
  } else {
    // HIGH typically means dark/other color surface detected
    digitalWrite(ledPin, LOW);   // Turn off LED
    Serial.println("WHITE DETECTED");
  }
}

void driveForward() {
  //Serial.println("Driving forwards");
  digitalWrite(RIGHT_F, LOW);
  digitalWrite(RIGHT_R, HIGH);
  digitalWrite(LEFT_F, LOW);
  digitalWrite(LEFT_R, HIGH);
  // Setting the speeds using enA and enB
  analogWrite(RIGHT_SPEED, 255);
  analogWrite(LEFT_SPEED, 255);
}

void driveBackward() {
  Serial.println ("Driving backwards");
  digitalWrite(RIGHT_F, HIGH);
  digitalWrite(RIGHT_R, LOW);
  digitalWrite(LEFT_F, HIGH);
  digitalWrite(LEFT_R, LOW);
  // Setting the speeds using enA and enB
  analogWrite(RIGHT_SPEED, 200);
  analogWrite(LEFT_SPEED, 200);
}

void stop() {
  Serial.println ("Stop driving");
  digitalWrite(RIGHT_F, LOW);
  digitalWrite(RIGHT_R, LOW);
  digitalWrite(LEFT_F, LOW);
  digitalWrite(LEFT_R, LOW);
  // Setting the speeds using enA and enB
  analogWrite(RIGHT_SPEED, 0);
  analogWrite(LEFT_SPEED, 0);
}

void turnLeft() {
  Serial.println ("Turn Left");
  digitalWrite(RIGHT_F, LOW);
  digitalWrite(RIGHT_R, HIGH);
  digitalWrite(LEFT_F, HIGH);
  digitalWrite(LEFT_R, LOW);
  // Setting the speeds using enA and enB
  analogWrite(RIGHT_SPEED, 20);
  analogWrite(LEFT_SPEED, 20);
}

void turnRight() {
  Serial.println ("Turn Right");
  digitalWrite(RIGHT_F, HIGH);
  digitalWrite(RIGHT_R, LOW);
  digitalWrite(LEFT_F, LOW);
  digitalWrite(LEFT_R, HIGH);
  // Setting the speeds using enA and enB
  analogWrite(RIGHT_SPEED, 170);
  analogWrite(LEFT_SPEED, 170);
}
