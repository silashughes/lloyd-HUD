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
  tft.fillScreen(ILI9341_BLACK);
}


void loop(void) {
  textDisplay();
  delay(50);
}

unsigned long textDisplay() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(3);
  tft.println("Voltage: ");
  //tft.setTextColor(ILI9341_BLACK); tft.write((char)32); tft.setTextColor(ILI9341_WHITE);
  Serial.println("Voltage: ");
  tft.setTextSize(4);
  tft.print(controller.readVoltage());
  Serial.println(controller.readVoltage());
  tft.println("V");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Tempurature: ");
  Serial.println("Tempurature: ");
  tft.setTextSize(3);
  tft.print(controller.readTemp());
  Serial.println(controller.readTemp());
  tft.write((char)248); //degree symbol
  tft.println("C");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Current: ");
  Serial.println("Current: ");
  tft.setTextSize(3);
  tft.print(controller.readCurrent());
  Serial.println(controller.readCurrent());
  tft.println("A");
  tft.println("");
  tft.print(start);
  
  return micros() - start;
}


