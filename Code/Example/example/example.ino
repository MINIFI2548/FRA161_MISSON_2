int parameter[5];

void setup() {
  Serial.begin(115200);
}

void  loop() {
  if(Serial.available()) {
    int funcCase = Serial.read();
    Serial.print("function name : ");
    Serial.println(funcCase);
    int index = 0;
    while (Serial.available() > 0) {
      parameter[index] = Serial.read() << 8 | Serial.read();
      Serial.print("parameter ");
      Serial.print(index + 1);
      Serial.print(" : ");
      Serial.println(parameter[index]);
      index += 1; 
    }
  }
}