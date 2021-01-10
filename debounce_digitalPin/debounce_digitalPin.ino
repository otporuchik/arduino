int switchPin=7;
int ledPin=11;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup() {
  pinMode(ledPin,OUTPUT);
  pinMode(switchPin,INPUT);
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
    ledOn = !ledOn;
  }

  lastButton = currentButton;
  digitalWrite(ledPin, ledOn);
}
