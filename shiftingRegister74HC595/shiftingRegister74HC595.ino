int data = 2;// set pin 14 of 74HC595 as data input 
int clock = 5;// set pin 11 of 74hc595 as clock
int latch = 4;// set pin 12 of 74hc595 as output latch
boolean states[8];//bitmask of 8 outputs 74HC595

//setting pin in needed state by creating and writing bitmask
void sendPin(int pin, boolean state) {
  byte value = 0;
  byte add = 1;
  states[pin] = state;//setting new state on this pin
  //creating new bitmask aka value
  for(int i = 0; i < 8; i++) {
    if(states[i] == HIGH) value += add;
    add *= 2;
  }
  digitalWrite(latch, LOW);//open write mode
  shiftOut(data, clock, LSBFIRST, value);//sending value wich is bitmask
  digitalWrite(latch, HIGH);//closing write mode
}

void setup() {
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  digitalWrite(latch, HIGH);//closing latch not to get any signal

  //clean all registers = setting all to LOW
  for(int i = 0; i < 8; i++) {
    sendPin(i, LOW);
  }
}
void loop() {
  /*
  digitalWrite(latch, LOW);//enable writing to registers
  shiftOut(data, clock, LSBFIRST, 0b10000001);//0b=prefix,next=data=>bitmask
  digitalWrite(latch, HIGH);//closing setting data
  */
  for(int i = 0; i < 8; i++) {
    sendPin(i, HIGH);
    delay(1000);
  }
  for(int i = 0; i < 8; i++) {
    sendPin(i, LOW);
    delay(1000);
  }
}
