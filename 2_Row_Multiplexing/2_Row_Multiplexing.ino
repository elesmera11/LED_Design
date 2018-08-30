// Pin definitions
#define DIG_PIN_0 2
#define DIG_PIN_1 3
#define DIG_PIN_2 4
#define DIG_PIN_3 5
#define DIG_PIN_4 6

#define ANA_PIN_0 A0
#define ANA_PIN_1 A1
#define ANA_PIN_2 A2
#define ANA_PIN_3 A3
#define ANA_PIN_4 A4

#define TRIG_PIN_1 8
#define ECHO_PIN_1 9
#define TRIG_PIN_2 10
#define ECHO_PIN_2 11

// Constants
#define ANA_HIGH 255
#define MAX_DISTANCE 300
#define BUFF_SIZE 10

  
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
int readDistance() {
  // Clears the trigPin
  digitalWrite(TRIG_PIN_1, LOW);
  delay(10);
  
  // Sets the trigPin on HIGH state for 50 milli seconds
  digitalWrite(TRIG_PIN_1, HIGH);
  delay(50);
  digitalWrite(TRIG_PIN_1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(ECHO_PIN_1, HIGH);
  
  // Calculating the distance
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
  Serial.print("Ave Distance: ");
  Serial.println(round(distanceAve));
  return distanceAve;
}

// Turning on and off the LED's as a function of distance from the distance sensor
void LEDControl (int distance) {
  /*
  digitalWrite(DIG_PIN_0, HIGH);
  digitalWrite(DIG_PIN_1, LOW);
  digitalWrite(DIG_PIN_2, LOW);
  digitalWrite(DIG_PIN_3, LOW);
  digitalWrite(DIG_PIN_4, LOW);
  
  analogWrite(ANA_PIN_0, ANA_HIGH);
  analogWrite(ANA_PIN_1, ANA_HIGH);
  analogWrite(ANA_PIN_2, ANA_HIGH);
  analogWrite(ANA_PIN_3, ANA_HIGH);
  analogWrite(ANA_PIN_4, ANA_HIGH);*/
  
 
  
  /*
  else if (distance < 60 && distance > 46) {
    analogWrite(ANA_PIN_1, LOW);
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_2, ANA_HIGH);
    analogWrite(ANA_PIN_3, ANA_HIGH);
    analogWrite(ANA_PIN_4, ANA_HIGH);  
  }
  else if (distance < 45 && distance > 31) {
    analogWrite(ANA_PIN_2, LOW);
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, ANA_HIGH);
    analogWrite(ANA_PIN_3, ANA_HIGH);
    analogWrite(ANA_PIN_4, ANA_HIGH);
  }
  else if (distance < 30 && distance > 16) {
    analogWrite(ANA_PIN_3, LOW);
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, ANA_HIGH);
    analogWrite(ANA_PIN_2, ANA_HIGH);
    analogWrite(ANA_PIN_4, ANA_HIGH);
  }
  else if (distance < 15 && distance > 0) {
    analogWrite(ANA_PIN_4, LOW);
    analogWrite(ANA_PIN_0, ANA_HIGH);
    analogWrite(ANA_PIN_1, ANA_HIGH);
    analogWrite(ANA_PIN_2, ANA_HIGH);
    analogWrite(ANA_PIN_3, ANA_HIGH);
  }*/
}


void loop() {
  
  int distanceAve = 0;
  distanceAve = calcDistanceAve();
  //LEDControl(distanceAve); // Turn on the LED's
  
//  digitalWrite(DIG_PIN_0, HIGH);
//  digitalWrite(DIG_PIN_1, HIGH);
//  digitalWrite(DIG_PIN_2, HIGH);
//  digitalWrite(DIG_PIN_3, HIGH);
//  digitalWrite(DIG_PIN_4, HIGH);
//  
//  analogWrite(ANA_PIN_0, ANA_HIGH);
//  analogWrite(ANA_PIN_1, ANA_HIGH);
//  analogWrite(ANA_PIN_2, ANA_HIGH);
//  analogWrite(ANA_PIN_3, ANA_HIGH);
//  analogWrite(ANA_PIN_4, ANA_HIGH);
  
  /*
  analogWrite(ANA_PIN_0, LOW);
  analogWrite(ANA_PIN_1, ANA_HIGH);
  analogWrite(ANA_PIN_2, LOW);
  analogWrite(ANA_PIN_3, ANA_HIGH);
  analogWrite(ANA_PIN_4, ANA_HIGH);
  delay(500);
  analogWrite(ANA_PIN_0, ANA_HIGH);
  analogWrite(ANA_PIN_1, LOW);
  analogWrite(ANA_PIN_2, LOW);
  analogWrite(ANA_PIN_3, ANA_HIGH);
  analogWrite(ANA_PIN_4, ANA_HIGH);
  delay(500);
  analogWrite(ANA_PIN_0, ANA_HIGH);
  analogWrite(ANA_PIN_1, ANA_HIGH);
  analogWrite(ANA_PIN_2, LOW);
  analogWrite(ANA_PIN_3, ANA_HIGH);
  analogWrite(ANA_PIN_4, ANA_HIGH);
  delay(500);
  analogWrite(ANA_PIN_0, ANA_HIGH);
  analogWrite(ANA_PIN_1, ANA_HIGH);
  analogWrite(ANA_PIN_2, LOW);
  analogWrite(ANA_PIN_3, LOW);
  analogWrite(ANA_PIN_4, ANA_HIGH);
  delay(500);
  analogWrite(ANA_PIN_0, ANA_HIGH);
  analogWrite(ANA_PIN_1, ANA_HIGH);
  analogWrite(ANA_PIN_2, LOW);
  analogWrite(ANA_PIN_3, ANA_HIGH);
  analogWrite(ANA_PIN_4, LOW);
  delay(500);*/
  
}
