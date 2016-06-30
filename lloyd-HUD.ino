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
#include "Alltrax.h" //Import the motor controller Library

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

Alltrax controller;

void setup() {
  controller.begin(&Serial);
  tft.begin();
}


void loop(void) {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    //tft.setRotation(rotation);
    testText();
    delay(1000);
  }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  tft.fillScreen(ILI9341_RED);
  tft.fillScreen(ILI9341_GREEN);
  tft.fillScreen(ILI9341_BLUE);
  tft.fillScreen(ILI9341_BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Voltage: ");
  tft.setTextSize(4);
  tft.print(controller.readVoltage());
  tft.println("V");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Tempurature: ");
  tft.setTextSize(3);
  tft.print(controller.readTemp());
  tft.write(0x00B0); //degree symbol
  tft.println("C");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Current: ");
  tft.setTextSize(3);
  tft.print(controller.readCurrent());
  tft.println("A");
  tft.println("");
  tft.print(start);
  
  return micros() - start;
}


