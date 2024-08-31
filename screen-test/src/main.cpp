#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

void setup() 
{
  Serial.begin(115200);
  Serial.println(String("SPI_FREQUENCY: ") + SPI_FREQUENCY);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0,0,4);
  tft.setTextColor(TFT_WHITE);
  tft.println("Hello World!");
}

void loop() 
{
  Serial.println("Here 1");
  delay(5000);
}