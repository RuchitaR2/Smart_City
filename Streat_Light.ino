void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int read1 = !digitalRead(8);
  if (read1 == 1){
    analogWrite(A0,200);
    delay(3000);
    digitalWrite(A0,LOW);
    delay(3000);
  }
  else{
    digitalWrite(A0,LOW);
  }
}
