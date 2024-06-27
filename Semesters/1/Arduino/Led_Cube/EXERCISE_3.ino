int pin[] = {2, 6, 10};
int layer[] = {11, 12, 13};
unsigned long previousMillis;
unsigned long currentMillis = 0;
unsigned long interval = 300;

void setup() {
  for (int i =0;i<3; i++) {
     pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
     pinMode(layer[i], OUTPUT);
    digitalWrite(layer[i], HIGH);
}
}
void loop() {
  currentMillis = millis();
  
    
  for(int i = 0; i < 3; i++){
while(currentMillis - previousMillis <= interval)
    {
    previousMillis = millis();
      digitalWrite(pin[i], HIGH);
      digitalWrite(layer[i], LOW);  
      digitalWrite(pin[i], LOW);
      digitalWrite(layer[i], HIGH);
    }
  }
}
