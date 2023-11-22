  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_ST7789.h>
  
  //Player one values
  #define length1 215
  uint8_t direction1 = 1;
  uint8_t x1 = 30;
  uint8_t y1 = 120;
  boolean pressed1 = LOW;
  #define right1 2
  #define left1 3
  uint8_t beamX1[length1];
  uint8_t beamY1[length1];
  uint8_t arrayPosition1 = 0;
  uint8_t score1 = 0;

  //Player two values
  #define length2 215
  uint8_t direction2 = 3;
  uint8_t x2 = 220;
  uint8_t y2 = 120;
  boolean pressed2 = LOW;
  #define right2 5
  #define left2 4
  uint8_t beamX2[length1];
  uint8_t beamY2[length1];
  uint8_t arrayPosition2 = 0;
  uint8_t score2 = 0;
  
  //Display Pins
  #define TFT_SCK 13
  #define TFT_MOSI 11
  #define TFT_CS 10
  #define TFT_RST 9
  #define TFT_DC 8

  Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  pinMode(right1, INPUT_PULLUP);
  pinMode(left1, INPUT_PULLUP);
  pinMode(right2, INPUT_PULLUP);
  pinMode(left2, INPUT_PULLUP);
    
  tft.init(240, 240);
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0));
}

void loop() {

  /*
  Reads the turn buttons for each player and if one is pressed it changes that players direction
  The refresh rate of the arduino is so fast that to the player the turn button has no delay thus there's no requirement for an interrupt pin
  To avoid having the player turn multiple times in one push, the boolean "pressed" is switched to high so that the player cannot turn unless
  the arduino measure that they have let go of the button
  */

  //Bike one
  if (digitalRead(right1) == LOW && pressed1 == LOW) {
    if (direction1 == 3) {
        direction1 = 0;
        }
        else {
          direction1++;
          }
    pressed1 = HIGH;
    }
  
  if (digitalRead(left1) == LOW && pressed1 == LOW) {
    if (direction1 == 0) {
        direction1 = 3;
        }
        else {
          direction1--;
          }
    pressed1 = HIGH;
    }
    
  if (digitalRead(right1) == HIGH && digitalRead(left1) == HIGH && pressed1 == HIGH){
      pressed1 = LOW;
      }


  //Bike two
  if (digitalRead(right2) == LOW && pressed2 == LOW) {
    if (direction2 == 3) {
        direction2 = 0;
        }
        else {
          direction2++;
          }
    pressed2 = HIGH;
    }
  
  if (digitalRead(left2) == LOW && pressed2 == LOW) {
    if (direction2 == 0) {
        direction2 = 3;
        }
        else {
          direction2--;
          }
    pressed2 = HIGH;
    }
    
  if (digitalRead(right2) == HIGH && digitalRead(left2) == HIGH && pressed2 == HIGH){
      pressed2 = LOW;
      }


  //Calculates each bikes new location based on
  //it's current direction
  
  //Bike one
  if (direction1 == 0) {
    y1 = y1 - 1;
    }
    else if (direction1 == 1) {
      x1 = x1 + 1;
      }
    else if (direction1 == 2) {
      y1 = y1 + 1;
      }
    else if (direction1 == 3) {
      x1 = x1 - 1;
      }

  //Bike two
  if (direction2 == 0) {
    y2 = y2 - 1;
    }
    else if (direction2 == 1) {
      x2 = x2 + 1;
      }
    else if (direction2 == 2) {
      y2 = y2 + 1;
      }
    else if (direction2 == 3) {
      x2 = x2 - 1;
      }

  //This is where the code checks the last 50 pixels and if one
  //the bikers is currently in one of them then it resets
 for (int i = 0; i < length1; i++) {
   if ((x1 == beamX1[i] && y1 == beamY1[i]) || (x1 == beamX2[i] && y1 == beamY2[i]) || x1 > 320 || x1 < 0 || y1 > 240 || y1 < 0) {
     for (int i = 0; i < length1; i++) {
       beamX1[i] = 0;
       beamY1[i] = 0;
       beamX2[i] = 0;
       beamY2[i] = 0;
     }
     x1 = 30;
     y1 = 120;
     x2 = 290;
     y2 = 120;
     direction1 = 1;
     direction2 = 3;
     tft.fillScreen(tft.color565(0, 0, 0));
     score2++;
     }
   }

 for (int i = 0; i < length2; i++) {
   if ((x2 == beamX1[i] && y2 == beamY1[i]) || (x2 == beamX2[i] && y2 == beamY2[i]) || x2 > 320 || x2 < 0 || y2 > 240 || y2 < 0) {
     for (int i = 0; i < length2; i++) {
       beamX1[i] = 0;
       beamY1[i] = 0;
       beamX2[i] = 0;
       beamY2[i] = 0;
     }
     x1 = 30;
     y1 = 120;
     x2 = 290;
     y2 = 120;
     direction1 = 1;
     direction2 = 3;
     tft.fillScreen(tft.color565(0, 0, 0));
     score1++;
     }
   }
    
  //This is where the oldest pixel location turns itself black then the
  //Newest position for snake replaces the oldest position
  //if the array value is 149 it gets turned to 1 and if not it just adds 1
  
  tft.drawPixel(beamX1[arrayPosition1], beamY1[arrayPosition1], tft.color565(0, 0, 0));
  tft.drawPixel(beamX2[arrayPosition2], beamY2[arrayPosition2], tft.color565(0, 0, 0));
  beamX1[arrayPosition1] = x1;
  beamY1[arrayPosition1] = y1;
  beamX2[arrayPosition2] = x2;
  beamY2[arrayPosition2] = y2;
  
  if (arrayPosition1 == length1 - 1) {
    arrayPosition1 = 0;
      }
    else {
      arrayPosition1++;
      }

  if (arrayPosition2 == length1 - 1) {
    arrayPosition2 = 0;
      }
    else {
      arrayPosition2++;
      }
          
  tft.drawPixel(x1, y1, tft.color565(14, 248, 248));
  tft.drawPixel(x2, y2, tft.color565(255, 131, 0));

  //tft.drawChar(0, 0, 1, tft.color565(255, 255, 255), 0, 2);

  delay(15);
}
