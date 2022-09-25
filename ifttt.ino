//Written by Rupak Poddar
//www.youtube.com/RupakPoddar
//www.github.com/RupakPoddar

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//------- Replace the following! ------//
char ssid[] = "Change this";       // your network SSID (name)
char password[] = "Change this";  // your network password

String key = "Change this"; //your webhooks key
String event_name = "Change this"; //your webhooks event name
String value1 = "Change this"; //value1 that you want to send when the event is triggered
String value2 = "Change this"; //value2 that you want to send when the event is triggered
String value3 = "Change this"; //value3 that you want to send when the event is triggered

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


  //triggerEvent takes an Event Name and then you can optional pass in up to 3 extra Strings
  HTTPClient http;
  http.begin("http://maker.ifttt.com/trigger/"+event_name+"/with/key/"+key+"?value1="+value1+"&value2="+value2+"&value3="+value3);
  http.GET();
  http.end();
  Serial.print("done");

  //https://maker.ifttt.com/trigger/{event}/with/key/{my_key}?value1={value 1}&value2={value 2}&value3={value 3}
}

void loop() {
}
