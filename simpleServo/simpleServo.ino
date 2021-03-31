#include <Servo.h>
/*
 * red wire = positive power
 * black = ground
 * yellow = control signal, digital output.
 * 
 * impuls frequency = 50Hz (20ms)
 * 500mks = 0 degrees
 * 2480mks = 180 degrees
 */

 //creating object to control
 Servo myservo;

void setup() {
  //attaching to 9 pin
  myservo.attach(9);  
}

void loop() {
  //move to start (left)
  myservo.write(0);
  delay(1000);
  //move to center
  myservo.write(90);
  delay(1000);
  //move to end (right)
  myservo.write(180);
  delay(1000);
}
