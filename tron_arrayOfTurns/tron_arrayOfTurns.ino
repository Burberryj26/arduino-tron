  /* 
  This version is intended for the Arduino Uno, but can qucikly be adapted for nearly any arduino device
  */
  
  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_ST7789.h>

  bool restart = false;

  //Player one values
  int direction1 = 1;
  int x1 = 20;
  int y1 = 160;
  int turnX [300];
  int turnY [300]; 
  int turnPointer = 1;
  bool pressed1 = LOW;
  bool looped = LOW;
  #define right1 2
  #define left1 3
  
  //Display Pins
  #define TFT_SCK 13
  #define TFT_MOSI 11
  #define TFT_CS 10
  #define TFT_RST 9
  #define TFT_DC 8

  Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  Serial.begin(9600);

  pinMode(right1, INPUT_PULLUP);
  pinMode(left1, INPUT_PULLUP);
  // pinMode(right2, INPUT_PULLUP);
  // pinMode(left2, INPUT_PULLUP);
    
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0));

}

void loop() {


  // Rotates the bike counter clockwise 90 degrees
  // Creates a struct of the point of the turn and appends it to the linked list of past turns in the bike's struct
  if (digitalRead(right1) == LOW && pressed1 == LOW) {
    if (direction1 == 3) {
      direction1 = 0;
    } else {
      direction1++;
    }
    pressed1 = HIGH;


    // Updates the current position of the bike to the list of turn points
    switch (turnPointer) {
      case sizeof(turnX) / sizeof(turnX[0]):
        tft.drawLine(turnX[turnPointer], turnY[turnPointer], turnX[0], turnY[0], tft.color565(0, 0, 0));
      default:
        tft.drawLine(turnX[turnPointer], turnY[turnPointer], turnX[turnPointer + 1], turnY[turnPointer + 1], tft.color565(0, 0, 0));
    }
    turnX[turnPointer] = x1;
    turnY[turnPointer] = y1;
    if (turnPointer == (sizeof(turnX) / sizeof(turnX[0])-1)) {
      turnPointer = 0;
    } else {
      turnPointer++;
    }

  }
  
  
  // Does the same thing as the if statement above, but rotates the bike clockwise 90 degrees
  if (digitalRead(left1) == LOW && pressed1 == LOW) {
    if (direction1 == 0) {
      direction1 = 3;
    } else {
      direction1--;
    }
    pressed1 = HIGH;


    // Updates the current position of the bike to the list of turn points
    switch (turnPointer) {
      case (sizeof(turnX) / sizeof(turnX[0])):
        tft.drawLine(turnX[turnPointer], turnY[turnPointer], turnX[0], turnY[0], tft.color565(0, 0, 0));
        break;
      default:
        tft.drawLine(turnX[turnPointer], turnY[turnPointer], turnX[turnPointer + 1], turnY[turnPointer + 1], tft.color565(0, 0, 0));
        break;
    }
    turnX[turnPointer] = x1;
    turnY[turnPointer] = y1;
    if (turnPointer == (sizeof(turnX) / sizeof(turnX[0])-1)) {
      turnPointer = 0;
    } else {
      turnPointer++;
    }
  }

  // If none of the turn buttons are currently being pressed it changes "pressed1" boolean so that the user can turn again
  // This prevents the user from rapidly turning mutliple times when they only press the button once
  if (digitalRead(right1) == HIGH && digitalRead(left1) == HIGH && pressed1 == HIGH){
    pressed1 = LOW;
  }

  // Calculates the bikes new location based on
  // It's direction

  switch (direction1) {
    case 0:
      y1--;
      break;
    case 1:
      x1++;
      break;
    case 2:
      y1++;
      break;
    case 3:
      x1--;
      break;
  }

  // Iterates through the array of turn points and checks if the bike's position lies between any two points
  // The iterator, i, starts at the last turn point and iterates through backwards i equals which index it started at
  int i = turnPointer;
  do {
    if (turnX[i] == turnX[i + 1]) {
      if (turnY[i] > turnY[i + 1]) {
        if (x1 == turnX[i] && (y1 < turnY[i] && y1 > turnY[i])) {
          restart = true;
        }
      } else {
        if (x1 == turnX[i] && (y1 > turnY[i] && y1 < turnY[i])) {
          restart = true;
        }
      }
    } else {
      if (turnX[i] > turnX[i + 1]) {
        if (x1 == turnY[i] && (y1 < turnX[i] && y1 > turnX[i])) {
          restart = true;
        }
      } else {
        if (x1 == turnY[i] && (y1 > turnX[i] && y1 < turnX[i])) {
          restart = true;
        }
      }
    }

    switch (i) {
      case 0:
        i = (sizeof(turnX) / sizeof(turnX[0]))-1;
        break;
      default:
        i--;
        break;
    }
  } while (i != turnPointer);


  tft.drawPixel(x1, y1, tft.color565(14, 248, 248));

  delay(2000);
}