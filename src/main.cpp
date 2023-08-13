#include <Arduino.h>
#include <ESP8266WiFi.h> 

void connectWifi(String ssid){
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
void setup() {
  // put your setup code here, to run once:
  connectWifi("Camp2023-open");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("test\n");
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
