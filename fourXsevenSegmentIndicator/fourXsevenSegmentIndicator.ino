/*Counter from 0 to 9999 every second*/
int digit4 = A0;//just for test. it works as digital output.
int digit3 = 3;
int digit2 = 4;
int digit1 = 5;

int a = 6;
int b = 7;
int c = 8;
int d = 9;
int e = 10;
int f = 11;
int g = 12;
int dp = 13;

int number1 = 0;
int number2 = 0;
int number3 = 0;
int number4 = 0;

int counter = 0;

void showNumber(int number, int digit) {
  switch(number) {
    case 0: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, LOW);
            break;
    case 1: digitalWrite(a, LOW);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, LOW);
            break;
    case 2: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, LOW);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, LOW);
            digitalWrite(g, HIGH);
            break;
    case 3: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, HIGH);
            break;
    case 4: digitalWrite(a, LOW);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
    case 5: digitalWrite(a, HIGH);
            digitalWrite(b, LOW);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
    case 6: digitalWrite(a, HIGH);
            digitalWrite(b, LOW);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
    case 7: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, LOW);
            digitalWrite(e, LOW);
            digitalWrite(f, LOW);
            digitalWrite(g, LOW);
            break;
    case 8: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
    case 9: digitalWrite(a, HIGH);
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, LOW);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
            break;
  }
  switch(digit) {
    case 0: digitalWrite(digit1, LOW);
            digitalWrite(digit2, HIGH);
            digitalWrite(digit3, HIGH);
            digitalWrite(digit4, HIGH);
            break;
    case 1: digitalWrite(digit1, HIGH);
            digitalWrite(digit2, LOW);
            digitalWrite(digit3, HIGH);
            digitalWrite(digit4, HIGH);
            break;
    case 2: digitalWrite(digit1, HIGH);
            digitalWrite(digit2, HIGH);
            digitalWrite(digit3, LOW);
            digitalWrite(digit4, HIGH);
            break;
    case 3: digitalWrite(digit1, HIGH);
            digitalWrite(digit2, HIGH);
            digitalWrite(digit3, HIGH);
            digitalWrite(digit4, LOW);
            break;
  }
}

void setup() {
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);//unused
}

void loop() {
  
  for (int i = 0; i <= 10000; i++) {
    if(i % 50 == 0) {//4 delay * 5 = 20 * this.50 = 1000 = 1 sec.
      if(i == 0) continue;
      counter++;
      if(counter == 10000) counter = 0;
    }
    int temp = counter;
    showNumber(temp / 1000, 0);
    temp %= 1000;
    delay(5);
    showNumber(temp / 100, 1);
    temp %= 100;
    delay(5);
    showNumber(temp / 10, 2);
    temp %= 10;
    delay(5);
    showNumber(temp, 3);
    delay(5);
  }
  
}
