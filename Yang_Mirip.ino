#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "configurations/configKornburg.h"

const int trigPin2 = 15;  // D8
const int echoPin2 = 13;  // D7

const int trigPin1 = 5;  // D1
const int echoPin1 = 4;  // D2

String levelHeightServerLocation = levelHeightServerLocationHardcoded;

void setup() {
  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input
  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input
  
  Serial.begin(9600); // Starts the serial communication

  connectToWlan();
  resolveLevelHeightServerLocation();
}

void resolveLevelHeightServerLocation() { 
    while(true) {
      Serial.println("Start to resolving levelHeightServerLocation with " + String(configurationRessourceHost) + String(configurationRessourceUri));   
      
      if(WiFi.status()== WL_CONNECTED) {   //Check WiFi connection status
 
        HTTPClient http;    //Declare object of class HTTPClient
 
        http.begin(String(configurationRessourceHost) + String(configurationRessourceUri));      //Specify request destination
        // http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
        int httpCode = http.GET();   //Send the request


        if (httpCode > 0) {
        
          String payload = http.getString();                  //Get the response payload
 
          Serial.println(httpCode);   //Print HTTP return code
          Serial.println(payload);    //Print request response payload
          levelHeightServerLocation = payload;
          return;
        
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
        http.end();  //Close connection
 
      }
      else { 
        Serial.println("Error in WiFi connection");    
      } 
 
      delay(3000);  //Send a request every 3 seconds
      
    }
}





void loop() {   
 if(WiFi.status()== WL_CONNECTED) {   //Check WiFi connection status
  
   Serial.println("Sending Measurment to " + String(levelHeightServerLocation));    
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin(String(levelHeightServerLocation) + "/Measurements");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
   int httpCode = http.POST(createJsonPostBody());   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload           

   if (httpCode < 0) {
     Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }
 
   http.end();  //Close connection
 
 }
 else { 
    Serial.println("Error in WiFi connection");    
 } 
 
 delay(3000);  //Send a request every 3 seconds

}

String createJsonPostBody () {
  return "{\"distanceFromSensor1\": \"" + String(getDistance(trigPin1, echoPin1)) + "\",\"distanceFromSensor2\": \"" + getDistance(trigPin2, echoPin2) + "\"}";
}

int getDistance(const int trigPin, const int echoPin) {      
  // Clears the trigPin1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin1 on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin1, returns the sound wave travel time in microseconds
  // Calculating the distance
  return pulseIn(echoPin, HIGH)*0.034/2;
}

void connectToWlan() {
  delay(10);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wLanSsid);

 
  WiFi.begin(wLanSsid, wLanPasswort);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
