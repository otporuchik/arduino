void showNumber(int number) {
  switch(number) {
  case 0: digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  case 1: digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);
          break;
  case 2: digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
          digitalWrite(8, LOW);
          break;
  case 3: digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  case 4: digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);
          break;
  case 5: digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  case 6: digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  case 7: digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);
          break;
  case 8: digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  case 9: digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          digitalWrite(6, LOW);
          digitalWrite(7, HIGH);
          digitalWrite(8, HIGH);
          break;
  }
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  for(int i = 0; i <= 9; i++) {
    showNumber(i);
    delay(500);
    digitalWrite(9, HIGH);//point in 7-segment display
    delay(250);
    digitalWrite(9, LOW);
    delay(250);
  }
  for(int i = 8; i >= 1; i--) {
    showNumber(i);
    delay(500);
    digitalWrite(9, HIGH);
    delay(250);
    digitalWrite(9, LOW);
    delay(250);
  }
}
