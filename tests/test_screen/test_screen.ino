  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_ST7789.h>
  
  
  //Pins connecting to display
  
  
  #define pot1 A0
  int potVal;
  
  // Player one values
  int direction1;
  int x1 = 160;
  int y1 = 120;
  #define left1 2
  #define right1 3
  
  //Player two values
  int x2 = 310;
  int y2 = 10;
  #define left2 4
  #define right2 5
  
  //Display Pins
  #define TFT_SCK 13
  #define TFT_MOSI 11
  #define TFT_CS 10
  #define TFT_RST 9
  #define TFT_DC 8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  
  //Serial.begin(9600);
  
  pinMode(left1, INPUT);
  pinMode(right1, INPUT);
  pinMode(left2, INPUT);
  pinMode(right2, INPUT);
  
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(tft.color565(0, 0, 0));
  tft.fillCircle(15, 15, 5, tft.color565(100,100,100));

}

void loop() {

  potVal = analogRead(pot1);
  //Serial.print("potval, ");
  //Serial.println(potVal);
  if (potVal >= 0 && potVal < 256) {
    direction1 = 3;
  } else if (potVal >= 256 && potVal < 512) {
    direction1 = 2;
  } else if (potVal >= 512 && potVal < 768) {
    direction1 = 1;
  } else if (potVal >= 768 && potVal <= 1023) {
    direction1 = 0;
  }
  
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
  
  tft.drawPixel(x1, y1, tft.color565(255, 255, 0));
  delay(50);

}
