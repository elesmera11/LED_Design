#include "pins.h"
#include "distance_LEDs.h"

// Constants
#define ECHO_TIMEOUT 50000 //50ms
#define ANA_HIGH 255
#define BUFF_SIZE 5
  
void setup() {
  pinMode(TRIG_PIN_1, OUTPUT); // Sets the TRIG_PIN_ as an Output
  pinMode(ECHO_PIN_1, INPUT); // Sets the ECHO_PIN_ as an Input
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
}

// Read the distance from the ultrasonic sensor
// Note that sensor 1 is for x-distance, sensor 2 is for y-distance.
int readDistance() {
  // Clears the trigPin
  digitalWrite(TRIG_PIN_1, LOW);
  delay(10);
  
  // Sets the trigPin on HIGH state for 50 milli seconds
  digitalWrite(TRIG_PIN_1, HIGH);
  delay(20);
  digitalWrite(TRIG_PIN_1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(ECHO_PIN_1, HIGH, ECHO_TIMEOUT);
  
  // Calculating the distance in cm
  float distance = duration*0.034/2;
  return distance;
}

// Reading 20 distance values, then take the average of the values read
int calcDistanceAve () {
  float distance;
  float distanceSum;
  float distanceAve;
  float distanceBuffer[BUFF_SIZE];
  
  for (int i = 0; i < BUFF_SIZE; i++) {
    distance = readDistance();
    if (distance <= MAX_DISTANCE) { //remove outliers and/or noise
      distanceBuffer[i] = distance;
    } else {
      distanceBuffer[i] = distanceBuffer[i-1]; //replace with close number for averaging
    }
  }
  
  for (int i = 0; i < BUFF_SIZE; i++) {
    distanceSum += distanceBuffer[i];
  }
  distanceAve = distanceSum / BUFF_SIZE;
  if (distanceAve > MAX_DISTANCE + 2 || distanceAve < MIN_DISTANCE - 2) {
    distanceAve = 0; //if object out of range, reset to zero. 
  }
  Serial.print("Ave Distance: ");
  Serial.println(round(distanceAve));
  return distanceAve;
}

void loop() {
  
  int distanceAve = 0;
  distanceAve = calcDistanceAve();
  if (distanceAve != 0) {
    LEDControl((int)distanceAve); // Turn on the LED's
  }
}
