#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

int locX = 20;
int locY = 15;

boolean directionRight = true;
boolean directionUp = false;
boolean directionLeft = false;
boolean directionDown = true;

void setup() {
  Serial.begin(9600);
  
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
  if (directionRight == true) {
    locX += 3;
  }

  if (directionUp == true) {
    locY -= 1;
  }

  if (directionLeft == true) {
    locX -= 3;
  }

  if (directionDown == true) {
    locY += 1;
  }
}

void testColision() {
  if (locX <= 3) {
    directionLeft = false;
    directionRight = true;
  }

  if (locX >= display.width() - 7) {
    directionLeft = true;
    directionRight = false;
  }

  if (locY <= 1) {
    directionUp = false;
    directionDown = true;
  }

  if (locY >= display.height() - 3) {
    directionUp = true;
    directionDown = false;
  }
}


void loop() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  drawBox();

  drawCharacter();

  testColision();

  moveCharacter();


  delay(100);
  
  display.display();
}
