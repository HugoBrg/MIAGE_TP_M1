#include "OneWire.h"
#include "DallasTemperature.h"

OneWire oneWire(33);
DallasTemperature tempSensor(&oneWire);

void setup() {
  Serial.begin(9600);
  tempSensor.begin();
}

void loop() {
  float t;
  tempSensor.requestTemperaturesByIndex(0);

  t = tempSensor.getTempCByIndex(0);

  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print(" C\n");

  delay(1000);
}
