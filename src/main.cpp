#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 
const String ssid = "Camp2023-open";
const String server = "162.55.160.183";
const int port = 5000;
const String uuid = String(ESP.getFlashChipId());
const int D1 = 5;  // Analoger Eingangspin für Button 1
const int D2 = 4;  // Analoger Eingangspin für Button 2
const int D5 = 14;  // Analoger Eingangspin für Button 5
void connectWifi(){
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid);
  Serial.begin(9600);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
void sendStatus(String status){
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
  
    HTTPClient http;
    WiFiClient client;
    String url =  "http://" + server + ":" + port + "/"+ status + "/" + uuid;
    Serial.println(url);
    http.begin(client,url); //Specify the URL
    int httpResponseCode = http.POST("");//Make the request
    if (httpResponseCode > 0) { //Check for the returning code
        String payload = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(payload);
      }
  
    else {
      Serial.println("Error on HTTP request");
    }
  
    http.end(); //Free the resources
  }
  
  delay(1000);
}
//To trigger if free button is pressed
void freePressed(){
  sendStatus("free");
}
//
void crowdedPressed(){
  sendStatus("crowded");
}
void showerOverflow(){
  sendStatus("overflow");
}
void setup() {
  // connects to wifi
  connectWifi();
  //Sets all pins to INPUT_PULLUP so they give a input signal
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // polls buttons every 20ms
  int free = digitalRead(D1);
  int crowded = digitalRead(D2);
  int overflow = digitalRead(D5);
  //OPTIONAL: Logs read values
  Serial.println(free);
  Serial.println(crowded);
  Serial.println(overflow);
  Serial.println("");
  //Triggers the method that tells the server which button is pressed.
  if (free == LOW){
    freePressed();
  } else if (crowded == LOW)
  {
    crowdedPressed();
  } else if (overflow ==LOW)
  {
    showerOverflow();
  }
  delay(20);
  
  
}

