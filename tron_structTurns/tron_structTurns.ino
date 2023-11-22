  /* 
  This version is intended for the Arduino Uno, but can qucikly be adapted for nearly any arduino device
  */
  
  #include <SPI.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_ST7789.h>
  
  struct Point {
  int xPoint;
  int yPoint;
  struct Point *turn;
  };

  //Player one values
  int direction1 = 1;
  struct Point start = {20, 10, NULL};
  struct Point bike1 = {20, 10, &start};
  bool pressed1 = LOW;
  bool turned = false;
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
    turned = true;
    if (direction1 == 3) {
      direction1 = 0;
    } else {
      direction1++;
    }
    pressed1 = HIGH;

    // Creates a temporary struct representing the position the bike just turned at
    struct Point lastTurn = bike1;

    Serial.print("last turn: (");
    Serial.print(lastTurn.xPoint);
    Serial.print(", ");
    Serial.print(lastTurn.yPoint);
    Serial.print(")           ");


    Serial.print("Second last turn: (");
    Serial.print(lastTurn.turn->xPoint);
    Serial.print(", ");
    Serial.print(lastTurn.turn->yPoint);
    Serial.println(")");

    delay(1500);
    bike1.turn = &lastTurn;

  }
  
  
  // Does the same thing as the if statement above, but rotates the bike clockwise 90 degrees
  if (digitalRead(left1) == LOW && pressed1 == LOW) {
    turned = true;
    if (direction1 == 0) {
      direction1 = 3;
    } else {
      direction1--;
    }
    pressed1 = HIGH;

    struct Point lastTurn = bike1;

    Serial.print("last turn: (");
    Serial.print(lastTurn.xPoint);
    Serial.print(", ");
    Serial.print(lastTurn.yPoint);
    Serial.print(")         ");


    Serial.print("Second last turn: (");
    Serial.print(lastTurn.turn->xPoint);
    Serial.print(", ");
    Serial.print(lastTurn.turn->yPoint);
    Serial.println(")");

    delay(1500);
    bike1.turn = &lastTurn;
  }

  // If none of the turn buttons are currently being pressed it changes "pressed1" boolean so that the user can turn again
  // This prevents the user from rapidly turning mutliple times when they only press the button once
  if (digitalRead(right1) == HIGH && digitalRead(left1) == HIGH && pressed1 == HIGH){
    pressed1 = LOW;
  }

  // Calculates the bikes new location based on
  // It's direction

  switch (direction1){
    case 0:
      bike1.yPoint = bike1.yPoint - 1;
      break;
    case 1:
      bike1.xPoint = bike1.xPoint + 1;
      break;
    case 2:
      bike1.yPoint = bike1.yPoint + 1;
      break;
    case 3:
      bike1.xPoint = bike1.xPoint - 1;
      break;
  }


  // Serial.println(bike1.turn->turnNumber);

  if (!turned) {
    Serial.print("bike coordinates: (");
    Serial.print(bike1.xPoint);
    Serial.print(", ");
    Serial.print(bike1.yPoint);
    Serial.print(")           ");

    Serial.print("Last turn: (");
    Serial.print(bike1.turn->xPoint);
    Serial.print(", ");
    Serial.print(bike1.turn->yPoint);
    Serial.println(")           ");
  }

  if (turned) {
    Serial.print("bike coordinates: (");
    Serial.print(bike1.xPoint);
    Serial.print(", ");
    Serial.print(bike1.yPoint);
    Serial.print(")           ");

    Serial.print("Last turn: (");
    Serial.print(bike1.turn->xPoint);
    Serial.print(", ");
    Serial.print(bike1.turn->yPoint);
    Serial.print(")           ");

    Serial.print("2nd last turn: (");
    Serial.print(bike1.turn->turn->xPoint);
    Serial.print(", ");
    Serial.print(bike1.turn->turn->yPoint);
    Serial.println(")");
  }


  tft.drawChar(100, 10, bike1.turn->yPoint, tft.color565(255, 0, 0), 10, 5);
  tft.drawPixel(bike1.xPoint, bike1.yPoint, tft.color565(14, 248, 248));

  delay(2000);
}

