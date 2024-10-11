void setup() {
  Serial.begin(115200);  //Open Serial
}

void loop() {
  if(Serial.available() > 0){
      int command = Serial.readString().toInt();
      Serial.println(command);
  }
}
