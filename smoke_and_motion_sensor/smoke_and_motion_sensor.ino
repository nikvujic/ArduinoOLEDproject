// ================= CODE FOR SMOKE DETECTOR RATIO =================
//void setup() { 
// Serial.begin(9600); 
//} 
//void loop() { 
// float sensor_volt;  
// float RS_air; //  Rs in clean air 
// float R0;  // R0 in 1000 ppm LPG 
// float sensorValue; 
////Average   
//   for(int x = 0 ; x < 100 ; x++) 
// { 
//   sensorValue = sensorValue + analogRead(A0); 
// } 
// sensorValue = sensorValue/100.0; 
////-----------------------------------------------/ 
// sensor_volt = (sensorValue/1024)*5.0; 
// RS_air = (5.0-sensor_volt)/sensor_volt; // Depend on RL on yor module 
// R0 = RS_air/9.9; // According to MQ9 datasheet table 
// Serial.print("sensor_volt = "); 
// Serial.print(sensor_volt); 
// Serial.println("V");
// Serial.print("R0 = "); 
// Serial.println(R0); 
// delay(1000); 
//}
// ===================================================

#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);

int inputPin = 2;
int pirState = LOW;
int val = 0;

String oledText = "detecting...";
 
void setup() {
  Serial.begin(9600);
  
  pinMode(inputPin, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}
 
void loop(){
  // smoke detector variables
  int alarm = 0; 
  float sensor_volt; 
  float RS_gas; 
  float ratio; 
  float R0 = 0.1; 
  int sensorValue = analogRead(A0); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
  RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module 
  ratio = RS_gas / R0; // ratio = RS/R0 

//  Serial.print("sensor_volt = "); 
//  Serial.println(sensor_volt); 
//  Serial.print("RS_ratio = "); 
//  Serial.println(RS_gas); 
//  Serial.print("Rs/R0 = "); 
//  Serial.println(ratio);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  
  if (ratio > 130) {
    String message = "Air clean!";
    message += " (";
    message += ratio;
    message += ")";
    display.println(message);
  } else {
    String message = "Gas detected!";
    message += " (";
    message += ratio;
    message += ")";
    display.println(message);
  }
  
  display.setCursor(0, 16);
  display.println(oledText);
  
  val = digitalRead(inputPin);
  Serial.print("PIR INPUT: ");
  Serial.println(val);
  if (val == HIGH) {
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      oledText = "> Motion detected!";
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      oledText = "Motion ended!";
      pirState = LOW;
    }
  }

  display.display();
}
