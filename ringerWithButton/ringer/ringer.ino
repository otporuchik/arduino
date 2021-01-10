int buzzer = 8;
int switchPin = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(switchPin, INPUT);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(switchPin);
  if(last != current) {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH) {
    Serial.println("din-dilin ");
    while(currentButton == HIGH) {
      for(int i=0;i<80;i++) {
        digitalWrite(buzzer,HIGH);
        delay(1);
        digitalWrite(buzzer,LOW);
        delay(1);
      } 
      for(int i=0;i<100;i++) {
        digitalWrite(buzzer,HIGH);
        delay(2);
        digitalWrite(buzzer,LOW);
        delay(2);
      }
      currentButton = debounce(currentButton);
    }
  }
  lastButton = currentButton;
} 
