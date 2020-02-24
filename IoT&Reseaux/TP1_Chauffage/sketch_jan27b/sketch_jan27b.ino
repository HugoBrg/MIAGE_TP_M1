#include "OneWire.h"
#include "DallasTemperature.h"

const int luminosite = 13;
const int temperature = 23;
const int vert = 22;
const int rouge = 23;

OneWire oneWire(temperature);
DallasTemperature tempSensor(&oneWire);

int sensorValueTemp;
int sensorValueLumi;

void setup() {
  Serial.begin(9600);
  pinMode(vert, OUTPUT);
  pinMode(rouge, OUTPUT);
  tempSensor.begin();
}

void loop() {
  sensorValueLumi = analogRead(luminosite);
  
  tempSensor.requestTemperaturesByIndex(0);
  sensorValueTemp = tempSensor.getTempCByIndex(0);
  
  Serial.print("Temperature : ");
  Serial.print(sensorValueTemp);
  Serial.print(" | Luminosite : ");
  Serial.print(sensorValueLumi);
  Serial.print("\n");

  if(sensorValueTemp < 25 && sensorValueLumi < 1800){
      //NUIT
      Serial.print("NUIT");
      Serial.print("\n");
      digitalWrite(vert, HIGH);
      digitalWrite(rouge, LOW);
  }
  else if (sensorValueTemp > 25 && sensorValueLumi > 1800){
      //JOUR
      Serial.print("JOUR");
      Serial.print("\n");
      digitalWrite(vert, LOW);
      digitalWrite(rouge, HIGH);
  }
  
  delay(1000);
}
