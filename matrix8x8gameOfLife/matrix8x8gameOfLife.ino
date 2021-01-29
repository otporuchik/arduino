int startPin = 2;//pin to start game with startButton
int data = 3;//for 74HC95
int latch = 4;//for 74HC95
int clock = 5;//for 74HC95
static int rows[8] = {6, 7, 8, 9, 10, 11, 12, 13};//matrix 8x8 rows from top to bottom
boolean columns[8] = {1, 1, 1, 1, 1, 1, 1, 1};//bitmask of 8 outputs 74HC595
boolean currentStartButton = LOW;//actual state this moment
boolean lastStartButton = LOW;//last state of start button to compare with current
boolean startButtonFlag = LOW;
//joystick
int joystickYpin = A7;
int joystickXpin = A6;
int joystickButtonPin = A5;
boolean currentJoystickButton = LOW;//actual state at this moment
boolean lastJoystickButton = LOW;//last state of button to compare with current
boolean joystickFlag = LOW;
boolean stopJoystickAction = LOW;
boolean flashCursorFlag = LOW;
unsigned long flashCursorTimer = 0;
//coordinates
int x = 0;
int y = 0;
//8x8 LED matrix masks
boolean matrixMask[8][8];
//game of life frame
boolean gameFrameMask[8][8];
unsigned long cycleTimer = 0;

//********************func block start*********************************************************************

//setting particular pin in needed state by creating and writing bitmask to 74HC595. It's columns.
void sendPin(int pin, boolean state) {
  byte value = 0;//bitmask
  byte add = 1;
  columns[pin] = state;//setting new state on this pin
  //creating new bitmask aka value
  for(int i = 0; i < 8; i++) {
    if(columns[i] == HIGH) value += add;
    add *= 2;
  }
  digitalWrite(latch, LOW);//open write mode
  shiftOut(data, clock, MSBFIRST, value);//sending value wich is bitmask. MSB=most significant bit first.
  digitalWrite(latch, HIGH);//closing write mode
}

//switching on leds in 8x8 matrix
void writePixel(int thisColumn, int thisRow) {
  /*Firstly - rising all catodes (columns) and lowing all anodes (rows).
   * No one LED'll shine after that!
   */
  for(int i = 0; i < 8; i++) {
    sendPin(i, HIGH);
    digitalWrite(rows[i], LOW);
  }
  //Now writing LED (pixel) in needed coordinates
  sendPin(thisColumn, LOW);
  digitalWrite(rows[thisRow], HIGH);
  //wait a little before next possible calling, to prevent collapse.
  //delay(0.1);
}

//debouncing
boolean debounce(boolean last, int inputPin) {
  boolean current = digitalRead(inputPin);
  if(last != current) {
    delay(5);
    current = digitalRead(inputPin);
  }
  return current;
}

//switches flags relaying on button states
void rTriglFlag(bool* lastButton, bool* currentButton, bool* flag) {
  if(*lastButton == LOW && *currentButton == HIGH) {
    *flag = !*flag;
  }
  *lastButton = *currentButton;
}

//flash led
void flash(int x, int y) {
  if(flashCursorFlag) writePixel(y, x);
  if(millis() - 250 >= flashCursorTimer) {
    flashCursorFlag = !flashCursorFlag;
    flashCursorTimer = millis() + 250;
  }
}

//cursor moving handler
void moveCursor(String action) {
  if(stopJoystickAction) {
    if(action == "left") {
     x -= 1;
    if(x < 0) x = 7;
    } else if(action == "right") {
      x += 1;
      if(x > 7) x = 0;
    } else if(action == "down") {
      y -= 1;
      if(y < 0) y = 7;
    } else if(action == "up") {
      y += 1;
      if(y > 7) y = 0;
    }
    stopJoystickAction = LOW;
  }
}

//*** game of life conditions and handlers ***
int crossBorderProtect(int number) {
  if(number < 0) number = 7;
  if(number > 7) number = 0;
  return number;
}

int countNeighbours(int x, int y) {
  int neighbours = 0;
  int tempX;
  int tempY;
  tempX = crossBorderProtect(x - 1);
  tempY = crossBorderProtect(y - 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = x;
  tempY = crossBorderProtect(y - 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = crossBorderProtect(x + 1);
  tempY = crossBorderProtect(y - 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = crossBorderProtect(x + 1);
  tempY = y;
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = crossBorderProtect(x + 1);
  tempY = crossBorderProtect(y + 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = x;
  tempY = crossBorderProtect(y + 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = crossBorderProtect(x - 1);
  tempY = crossBorderProtect(y + 1);
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  tempX = crossBorderProtect(x - 1);
  tempY = y;
  if(gameFrameMask[tempX][tempY]) neighbours += 1;
  return neighbours;
}

void liveCell(int x, int y, int neighbours) {
  if(neighbours < 2 || neighbours > 3) matrixMask[x][y] = LOW;
}

void deadCell(int x, int y, int neighbours) {
  if(neighbours == 3) matrixMask[x][y] = HIGH;
}

//********************func block end*********************************************************************

void setup() {
  Serial.begin(9600);
  pinMode(startPin, INPUT);
  pinMode(joystickButtonPin, INPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  for(int i = 0; i < 8; i++) pinMode(rows[i], OUTPUT);//initializing matrix 8x8 rows from top to bottom
  digitalWrite(latch, HIGH);//closing latch not to get any signal
  //filling matrix masks with LOW
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 0; j++) {
      matrixMask[i][j] = LOW;
      gameFrameMask[i][j] = LOW;
    }
  }
}

void loop() {
  //startButton handler
  currentStartButton = debounce(lastStartButton, startPin);//watching startPin with debouncing
  rTriglFlag(&lastStartButton, &currentStartButton, &startButtonFlag);

  //selecting cells to initialize game of life.
  while(!startButtonFlag) {
    //joystick handler
    currentJoystickButton = debounce(lastJoystickButton, joystickButtonPin);//watching joystickButton pin with debouncing
    rTriglFlag(&lastJoystickButton, &currentJoystickButton, &joystickFlag);

    if(analogRead(joystickXpin) >= 700) {
        moveCursor("right");
      }
      if(analogRead(joystickXpin) <= 300) {
        moveCursor("left");
      }
      if(analogRead(joystickYpin) >= 700) {
        moveCursor("down");
      }
      if(analogRead(joystickYpin) <= 300) {
        moveCursor("up");
    }

     if((analogRead(joystickXpin) > 300 && analogRead(joystickXpin) < 700) && 
       (analogRead(joystickYpin) > 300 && analogRead(joystickYpin) < 700)) {
      //flashing cursor 
      flash(y, x);//x and y here and in the matrixMask aren't the same. sadly.
      //readiness to move cursor
      stopJoystickAction = HIGH;
    }

    //joystickButton pressed action
    if(joystickFlag) {
      matrixMask[x][y] = !matrixMask[x][y];
      joystickFlag = !joystickFlag;       
    }
  
    //matrix 8x8 mask drawing 
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        if(matrixMask[i][j]) {
          writePixel(i, j);
          //delay(10);
        }
      }
    }//end of matrix 8x8 mask drawing loop
    //startButton handler
    currentStartButton = debounce(lastStartButton, startPin);//watching startPin with debouncing
    rTriglFlag(&lastStartButton, &currentStartButton, &startButtonFlag);
  }//end of while loop in selecting cells

  //game of life
  while(startButtonFlag) {
    //startButton handler
    currentStartButton = debounce(lastStartButton, startPin);//watching startPin with debouncing
    rTriglFlag(&lastStartButton, &currentStartButton, &startButtonFlag);

    //snapshot of current matrixMask (copying to gameFrameMask)
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        gameFrameMask[i][j] = matrixMask[i][j];
      }
    }//end of matrix arrays copying

    if(millis() - cycleTimer >= 500) {
      //loop throug all matrix 8x8 mask to play game of life
      for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
          int neighbours = countNeighbours(i, j);
          if(gameFrameMask[i][j]) {
            liveCell(i, j, neighbours);
          } else {
            deadCell(i, j, neighbours);
          }
        }
      }//end of matrix 8x8 looping to play
      cycleTimer = millis();
    }
    
    //matrix 8x8 gameFrame drawing 
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        if(gameFrameMask[i][j]) {
          writePixel(i, j);
        }
      }
    }//end of matrix 8x8 gameFrame drawing loop
    
  }//end of game of life while loop
  
}//end or main loop
//Julia's comment to game:
//мустик кот
