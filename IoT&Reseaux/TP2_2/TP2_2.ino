#include <WiFi.h>

void print_ip_status() {
  Serial.print("\nWifi connectée\n");
  Serial.print("IP adresse");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void connect_wifi(){
  const char* ssid = "HugoBRG";
  const char *password = "hugo1234";

  Serial.println("\nConnecting Wifi to ");
  Serial.println(ssid);

  Serial.print("Tentative reconnection");
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  print_ip_status();
}

void setup(){
  Serial.begin(9600);
  while(!Serial);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  
}
