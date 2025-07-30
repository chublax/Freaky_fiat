#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

// Ultrasonic sensor pin definitions
const int TRIG_PIN = 2;    // Changed from 9 to avoid conflict with RIGHT_SPEED
const int ECHO_PIN = 3;
const int ULTRASONIC_LED_PIN = 12;  // Using pin 12 instead of 13 to avoid conflict with IR sensor LED
const int DISTANCE_THRESHOLD = 2000; // Threshold in microseconds

// Function declarations
void setupUltrasonic();
void checkUltrasonicSensor();
unsigned long measureDistance();
float calculateDistanceCm(unsigned long duration);

// Function to initialize ultrasonic sensor
void setupUltrasonic() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ULTRASONIC_LED_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_LED_PIN, LOW);
  digitalWrite(TRIG_PIN, LOW);  // Ensure trigger starts LOW
  Serial.println("Ultrasonic sensor initialized");
}

// Function to measure distance and control LED
void checkUltrasonicSensor() {
  unsigned long duration = measureDistance();
  float distance_cm = calculateDistanceCm(duration);
  
  // Display distance information
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print(" cm (");
  //Serial.print(duration);
  //Serial.print(" microseconds)");
  
  if (duration > DISTANCE_THRESHOLD) {
    digitalWrite(ULTRASONIC_LED_PIN, HIGH);
    Serial.println(" - FAR");
  } else {
    digitalWrite(ULTRASONIC_LED_PIN, LOW);
    Serial.println(" - CLOSE");
  }
}

// Function to measure distance using ultrasonic sensor
unsigned long measureDistance() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, HIGH);   
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  
  return duration;
}

// Function to calculate distance in centimeters from duration
float calculateDistanceCm(unsigned long duration) {
  // Convert duration to distance in cm
  // Speed of sound = 343 m/s = 0.0343 cm/microsecond
  // Distance = (duration * speed) / 2 (divide by 2 for round trip)
  // Simplified: distance_cm = duration * 0.017
  return duration * 0.017;
}

#endif 