#define button 2
int condition;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  condition = digitalRead(button);
  Serial.println(condition);
  delay(5);
}
