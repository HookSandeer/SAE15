// Code By Antonin Michon & Lucas Colin
// https://github.com/HookSandeer
// Dépot du projet (Avec README.md): https://github.com/HookSandeer/SAE15

#include "carMotors.h"
#include "DeviceDriverSet_xxx0.h"
#include "FastLED.h"
#define PIN_RGBLED 4
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
int lap = 0;

CarMotors engine;   // Création Objet engine pourl le controle du moteur
DeviceDriverSet_ITR20001 AppITR20001;

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}

void setup() {
  Serial.begin(9600);
  AppITR20001.DeviceDriverSet_ITR20001_Init();
  FastLED.addLeds<NEOPIXEL, PIN_RGBLED>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  engine.init(50);
  FastLED.showColor(color(255, 0, 0));
  delay(3000);
}


void motor(float left, float middle, float right){
  if(left<700.00 && middle<700.00 && right<700.00){
    engine.stop();
  }else if(left<700.00 && middle>699.99 && right<700.00){
    engine.setSpeed(100);
    engine.goForward();
    delay(10);
  }else if(left>699.99 && middle<700.00 && right<700){
    engine.setSpeed(50);
    engine.turnLeft();
  }else if(left<700.00 && middle<700.00 && right>699.99){
    engine.setSpeed(50);
    engine.turnRight();
  }
}

void loop() {
  static unsigned long print_time = 0;
  if (millis() - print_time > 50){
    motor(AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R());
  }
  if (millis - print_time > 500){
    if(AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L()>700 && AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M()>700 && AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R()>700){
      lap++;
    }
    switch(lap){
      case 1 :
        FastLED.showColor(color(0, 255, 0));
        break;
      case 2 :
        FastLED.showColor(color(0, 0, 255));
        break;
      case 3 :
        FastLED.showColor(color(255, 128, 0));
        break;
      case 4 :
        FastLED.showColor(color(255, 0, 0));
        break;
    }
  }
  if(lap>=4){
      engine.stop();
    }
}
