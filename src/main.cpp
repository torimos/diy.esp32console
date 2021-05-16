#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the ESP-WROVER_KIT, these are the default.

#define TFT_MOSI 23 //pink
#define TFT_MISO 19 //green
#define TFT_CLK  18 //white
#define TFT_CS   5  //orange
#define TFT_DC   26//2 //black
#define TFT_RST  33//15 //blue

#define RIGHT_BTNS 36
#define LEFT_VX 4
#define LEFT_VY 0

#define UP_BTN 1
#define LEFT_BTN 1<<4
#define DOWN_BTN 1<<3
#define RIGHT_BTN 1<<2
#define CENTER_BTN 1<<5
#define JOY_BTN 1<<6

SPIClass tftSPI(VSPI);
Adafruit_ILI9341 tft = Adafruit_ILI9341(&tftSPI, TFT_DC, TFT_CS, TFT_RST);

void calibrate();

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_YELLOW); 
  tft.setTextSize(1);

}
void loop(void) {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0,0);
  long val_X = (analogRead(LEFT_VX) - 1880)/6;
  long val_Y = 215 - (analogRead(LEFT_VY) - 2940);
  tft.print(val_X); 
  tft.print(" : ");
  tft.println(val_Y);
  tft.drawLine(0, 120-val_Y/1.5, 319, 120-val_Y/1.5, ILI9341_GREEN);
  tft.drawLine(160-val_X/1.2, 0, 160-val_X/1.2, 239, ILI9341_GREEN);
  delay(50);
}

// X:  330 / 313 / 294     -17 | +19
// Y:   87 / 188 / 293       -101  | +105