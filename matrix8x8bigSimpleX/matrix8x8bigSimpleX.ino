//matrix 8x8
//paints simple big X
const int row[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int col[8] = {10, 11, 12, 13, A0, A1, A2, A3};

void writePixel(int thisRow, int thisCol) {
  //off to all catodes and anodes
  for(int i = 0; i < 8; i++) {
    digitalWrite(col[i], HIGH);
    digitalWrite(row[i], LOW);
  }
  digitalWrite(col[thisCol], LOW);
  digitalWrite(row[thisRow], HIGH);
  delay(1);
}

void setup() {
  for(int i = 0; i < 8; i ++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], HIGH);//initially all columns aren't ON (on = low).
  }
}

void loop() {
  for(int i = 0; i < 8; i++) {
    writePixel(i, i);
    writePixel(i, 7-i);
  }
}
