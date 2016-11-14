#include <Adafruit_GFX.h>
#include <gfxfont.h>

/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SoftwareSerial.h> //Any Software Serial Based implementation needs this
#include "AlltraxSoftwareSerial.h" //Import the motor controller Library

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Variables
float volt_min = 35.0;
float volt_max = 55.0;

float curr_min = 0.0;
float curr_max = 300;

float temp_min = 0.0;
float temp_max = 100.0;

float batt_min = 0.0;
float batt_max = 100.0;

float voltage = 0;
float current = 0;
float temp = 0;
float battery = 0;

float prev_voltage = 0;
float prev_current = 0;
float prev_temp = 0;
float prev_battery = 0;


// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

SoftwareSerial mySerial(4, 5);//Rx, Tx
AlltraxSoftwareSerial controller(&mySerial);

void setup() {
  Serial.begin(9600);//sets up the arduino to communicate with the computer
  Serial.println("Starting Screen...");
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}


void loop(void) {
  fake_controller();
  updateVoltage();
  updateCurrent();
  updateBattery();
  textDisplay();
  //delay(50);
}

void read_controller(){
  prev_voltage = voltage;
  prev_current = current;
  prev_temp = temp;
  
  voltage = controller.readVoltage();
  current = controller.readCurrent();
  temp = controller.readTemp(); 
}

void fake_controller(){
  prev_voltage = voltage;
  prev_current = current;
  prev_temp = temp;
  prev_battery = battery;
  
  if (voltage >= volt_max){
    voltage = volt_min;
  }
  else{
    voltage++;
  }

  if (current >= curr_max){
    current = curr_min;
  }
  else{
    current=current+10;
  }
  
  if (temp >= temp_max){
    temp = temp_min;
  }
  else{
    temp++;
  }

  if (battery >= batt_max){
    battery = batt_min;
  }
  else{
    battery++;
  }
  
  delay(50);
}

unsigned long updateVoltage() {
  unsigned long start = micros();
  uint16_t color = ILI9341_WHITE;

  if(voltage < 40.0){
    color = ILI9341_RED;
  }
  else if (voltage < 48.0){
    color = ILI9341_YELLOW;
  }
  else{
    color = ILI9341_GREEN;
  }
  
  if(prev_voltage > voltage){
    uint16_t top = map(prev_voltage, volt_min, volt_max, 240, 0);
    uint16_t bot = map(voltage, volt_min, volt_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(0, top, 38, height ,ILI9341_BLACK);
  }
  else if (prev_voltage < voltage){
    uint16_t top = map(voltage, volt_min, volt_max, 240, 0);
    uint16_t bot = map(prev_voltage, volt_min, volt_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(0, top, 38, height ,color);
  }
  return micros() - start;
}

unsigned long updateCurrent() {
  unsigned long start = micros();
  uint16_t color = ILI9341_MAGENTA;
  
  if(prev_current > current){
    uint16_t top = map(prev_current, curr_min, curr_max, 240, 0);
    uint16_t bot = map(current, curr_min, curr_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(100, top, 80, height ,ILI9341_BLACK);
  }
  else if (prev_current < current){
    uint16_t top = map(current, curr_min, curr_max, 240, 0);
    uint16_t bot = map(prev_current, curr_min, curr_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(100, top, 80, height ,color);
  }
  return micros() - start;
}

unsigned long updateBattery() {
  unsigned long start = micros();
  uint16_t color = ILI9341_WHITE;

  if(battery < 25){
    color = ILI9341_RED;
  }
  else if (battery < 50){
    color = ILI9341_YELLOW;
  }
  else{
    color = ILI9341_GREEN;
  }
  
  if(prev_battery > battery){
    uint16_t top = map(prev_battery, batt_min, batt_max, 240, 0);
    uint16_t bot = map(battery, batt_min, batt_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(42, top, 38, height ,ILI9341_BLACK);
  }
  else if (prev_battery < battery){
    uint16_t top = map(battery, batt_min, batt_max, 240, 0);
    uint16_t bot = map(prev_battery, batt_min, batt_max, 240, 0);
    uint16_t height = bot-top;
    tft.fillRect(42, top, 38, height ,color);
  }
  return micros() - start;
}

unsigned long textDisplay() {
  unsigned long start = micros();  
  tft.setCursor(200, 0);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);  
  tft.print("Voltage:");

  tft.setTextSize(4);
  tft.setCursor(200, 25); tft.setTextColor(ILI9341_BLACK); tft.print((int)prev_voltage);
  tft.setCursor(200, 25); tft.setTextColor(ILI9341_WHITE);tft.print((int)voltage);

  tft.setCursor(200, 80);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);  
  tft.print("Current:");
  
  tft.setTextSize(4);
  tft.setCursor(200, 105); tft.setTextColor(ILI9341_BLACK); tft.print((int)prev_current);
  tft.setCursor(200, 105); tft.setTextColor(ILI9341_WHITE);tft.print((int)current);

  tft.setCursor(200, 160);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);  
  tft.print("Battery: ");
  
  tft.setTextSize(4);
  tft.setCursor(200, 185); tft.setTextColor(ILI9341_WHITE); tft.print("%");
  tft.setCursor(230, 185); tft.setTextColor(ILI9341_BLACK); tft.print((int)prev_battery);
  tft.setCursor(230, 185); tft.setTextColor(ILI9341_WHITE);tft.print((int)battery);

  /*
  tft.setTextSize(4);
  tft.setCursor(0, 25); tft.setTextColor(ILI9341_BLACK); tft.print(prev_voltage);
  tft.setCursor(0, 25); tft.setTextColor(ILI9341_WHITE);tft.print(voltage);
  tft.setTextSize(3);
  tft.setCursor(0, 100); tft.setTextColor(ILI9341_BLACK); tft.print(prev_current);
  tft.setCursor(0, 100); tft.setTextColor(ILI9341_WHITE);tft.print(current);
  tft.setCursor(0, 200); tft.setTextColor(ILI9341_BLACK); tft.print(prev_temp);
  tft.setCursor(0, 200); tft.setTextColor(ILI9341_WHITE);tft.print(temp);
*/
  
  return micros() - start;
}


