#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

void setup()
{
    Serial.begin(9600);
    delay(10);

    wifiMulti.addAP("HugoBRG", "hugo1234");
    wifiMulti.addAP("s__Tempconn", "PierreS07");

    Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void loop()
{
    if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        delay(1000);
    }
}
