char receivedChar;
int sensorValue;
int coeff = 1;

void setup(){
  Serial.begin(9600);
  Serial.println("Serial prêt");
}

void loop(){
  sensorValue=analogRead(13);
  pinMode(19, OUTPUT);
  Serial.print(sensorValue,DEC);
  Serial.print("\n");

  if(Serial.available() > 0){
    receivedChar = Serial.read();
    Serial.print("\nRecu : ");
    Serial.print(receivedChar);
    if(receivedChar =='1')
      digitalWrite(19, HIGH);
    else
      digitalWrite(19, LOW);
  }
  delay(1000);
}
