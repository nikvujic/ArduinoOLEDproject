#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

int buttonUpPin = 8;
int buttonLeftPin = 9;
int buttonRightPin = 10;
int buttonDownPin = 11;

int locX = 20;
int locY = 15;

boolean directionRight = false;
boolean directionUp = false;
boolean directionLeft = false;
boolean directionDown = false;

void setup() {
  Serial.begin(9600);

  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void drawBox() {
  int j = 0;
  for (int i = 0; i < display.height(); i++) {
    display.drawPixel(0, i, WHITE);
    display.drawPixel(display.width() - 2, i, WHITE);
    
    display.drawPixel(j, 0, WHITE);
    display.drawPixel(j, display.height() - 1, WHITE);

    if (i < display.height() - 1) {
      display.drawPixel(j + 2, 0, WHITE);
      display.drawPixel(j + 2, display.height() - 1, WHITE);
    }
      
    j+=4;
  }
}

void drawCharacter() {
  display.drawPixel(locX, locY, WHITE);
  display.drawPixel(locX + 2, locY, WHITE);
  display.drawPixel(locX, locY + 1, WHITE);
  display.drawPixel(locX + 2 , locY + 1, WHITE);
}

void moveCharacter() {
  if (directionRight == true  && !testCollisionRight()) {
    locX += 3;
  }

  if (directionUp == true  && !testCollisionUp()) {
    locY -= 1;
  }

  if (directionLeft == true  && !testCollisionLeft()) {
    locX -= 3;
  }

  if (directionDown == true  && !testCollisionDown()) {
    locY += 1;
  }
}

boolean testCollisionLeft() {
  if (locX <= 3) {
    return true;
  }
  return false;
}

boolean testCollisionUp() {
  if (locY <= 1) {
    return true;
  }
  return false;
}

boolean testCollisionRight() {
  if (locX >= display.width() - 7) {
    return true;
  }
  return false;
}

boolean testCollisionDown() {
   if (locY >= display.height() - 3) {
    return true;
  }
  return false;
}

void resetMovement() {
  directionRight = false;
  directionUp = false;
  directionLeft = false;
  directionDown = false;
}

void readMovement() {
  if (!digitalRead(buttonUpPin)) {
    directionUp = true;
  }

  if (!digitalRead(buttonLeftPin)) {
    directionLeft = true;
    Serial.println("READ LEFT");
  }

  if (!digitalRead(buttonRightPin)) {
    directionRight = true;
  }

  if (!digitalRead(buttonDownPin)) {
    directionDown = true;
  }
}

void loop() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  drawBox();

  readMovement();

  moveCharacter();

  drawCharacter();

  resetMovement();
  
  display.display();
}
