void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("***START ou RESET***");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("TOP");
  delay(2000);
  Serial.println("MIDDLE");
  delay(2000);
  Serial.println("BOT");
}
