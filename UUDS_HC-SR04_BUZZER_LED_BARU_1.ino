#include <HCSR04.h>
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// defines variables
long duration;
int distance;
int safetyDistance;

#include "SerialTransfer.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
SerialTransfer myTransfer;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //Serial.begin(9600); // Starts the serial communication
  Serial.begin(115200);
  mySerial.begin(9600);
  myTransfer.begin(mySerial);
}


void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  safetyDistance = distance;
  if (safetyDistance <= 5) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
  }

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  myTransfer.txObj(distance, sizeof(distance));
  myTransfer.sendData(sizeof(distance));
}

/*
  #include "SerialTransfer.h"
  #include <SoftwareSerial.h>
  #define ThermistorPin 0

  int Vo;
  float R1 = 1000;
  float logR2, R2, T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  SoftwareSerial mySerial(2, 3); // RX, TX
  SerialTransfer myTransfer;

  void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  myTransfer.begin(mySerial);
  }

  void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1*(1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  //Serial.print("Temperature: ");
  Serial.println(T);
  //Serial.println(" C");

    myTransfer.txObj(T, sizeof(T));
    myTransfer.sendData(sizeof(T));
    delay(5000);
  }
*/