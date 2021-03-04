#include <LiquidCrystal.h>

//initialize library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int backLight = 9;

void setup() {
  lcd.begin(16, 2);
  //lcd.print("Hello world!");
  pinMode(backLight, OUTPUT);
}

void loop() {
  //set backlight power from min = 0 to max = 255
  analogWrite(backLight, 75);
  
  lcd.setCursor(0, 0);
  lcd.print(millis() / 1000);
  lcd.setCursor(6, 0);
  lcd.print("Hello");
  lcd.setCursor(9, 1);
  lcd.print("world!");
}
