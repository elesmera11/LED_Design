#include "pins.h"
#include "distance_LEDs.h"
#include "circBufT.h"

// Constants
#define ECHO_TIMEOUT 50000 //50ms


static circBuf_t x_circ_buff;
static circBuf_t y_circ_buff;
  
void setup() {  
  pinMode(TRIG_PIN_1, OUTPUT); // Sets the TRIG_PIN_ as an Output
  pinMode(ECHO_PIN_1, INPUT); // Sets the ECHO_PIN_ as an Input
  pinMode(TRIG_PIN_2, OUTPUT); // Sets the TRIG_PIN_ as an Output
  pinMode(ECHO_PIN_2, INPUT); // Sets the ECHO_PIN_ as an Input
  Serial.begin(115200); // Starts the serial communication
  
  pinMode(DIG_PIN_0, OUTPUT);
  pinMode(DIG_PIN_1, OUTPUT);
  pinMode(DIG_PIN_2, OUTPUT);
  pinMode(DIG_PIN_3, OUTPUT);
  pinMode(DIG_PIN_4, OUTPUT);
  
  pinMode(ANA_PIN_0, OUTPUT);
  pinMode(ANA_PIN_1, OUTPUT);
  pinMode(ANA_PIN_2, OUTPUT);
  pinMode(ANA_PIN_3, OUTPUT);
  pinMode(ANA_PIN_4, OUTPUT);
  
  initCircBuf(&x_circ_buff, BUFF_SIZE);
  initCircBuf(&y_circ_buff, BUFF_SIZE);
}

// Read the distance from the ultrasonic sensors
int readDistance(int trig_pin, int echo_pin) {
  // Clears the trigPin
  digitalWrite(trig_pin, LOW);
  delay(10);
  
  // Sets the trigPin on HIGH state for 50 milli seconds
  digitalWrite(trig_pin, HIGH);
  delay(20);
  digitalWrite(trig_pin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(echo_pin, HIGH, ECHO_TIMEOUT);
  
  // Calculating the distance in cm
  float distance = duration*0.034/2;
  return distance;
}

// Reading 20 distance values, then take the average of the values read
int calcDistanceAve (int trig_pin, int echo_pin) {
  float distance;
  
  distance = readDistance(trig_pin, echo_pin);
  Serial.print("Ave Distance: ");
  Serial.println(trig_pin);
  Serial.println(round(distance));
  return distance;
}

void loop() {
  int x_distance = calcDistanceAve(TRIG_PIN_1, ECHO_PIN_1);
  int y_distance = calcDistanceAve(TRIG_PIN_2, ECHO_PIN_2);
  writeCircBuf(&x_circ_buff, x_distance);
  writeCircBuf(&y_circ_buff, y_distance);

  LEDControl(&x_circ_buff, &y_circ_buff); // Turn on the LEDs
}
