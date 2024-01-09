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
  engine.init(140);
  FastLED.showColor(color(255, 0, 0));    
  delay(3000);      // Couleur led en rouge pendant 3s
}


void motor(float left, float middle, float right){
  if(left<700.00 && middle<700.00 && right<700.00){       // Perte de la ligne, tentative pour la retrouver
    engine.setSpeed(50);
    engine.goForward();
    delay(5);
  }else if(left<700.00 && middle>=700.00 && right<700.00){ // Capteur Centre sur Noir
    engine.setSpeed(100);
    engine.goForward();
    delay(5);
  }else if(left>=700.00 && middle<700.00 && right<700){   // Capteur Gauche sur Noir
    engine.setSpeed(100);
    engine.drive(0.9, 0.1);
    delay(5);
  }else if(left>=700.00 && middle>=700.00 && right<700){  // Capteur Gauche & Centre sur Noir
    engine.setSpeed(120);
    engine.drive(0.8, 0.3);
    delay(5);
  }else if(left<700.00 && middle>=700.00 && right>=700){ //Capteur Droit & Centre sur Noir
    engine.setSpeed(120);
    engine.drive(0.3, 0.8);
    delay(5);
  }else if(left<700.00 && middle<700.00 && right>=700.00){ // Capteur Droit Sur Noir
    engine.setSpeed(100);
    engine.drive(0.1, 0.9);
    delay(5);
  }if(left>700.00 && middle>700.00 && right>700.00){
    lap++;
    FastLED.showColor(color(255, 255, 255));
    delay(60);
  }
}

void loop() {
  motor(AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R());
  if(lap>0 && lap<3){
    FastLED.showColor(color(0, 255, 0));
  }else if(lap>=3 && lap<5){
    FastLED.showColor(color(0, 0, 255));
  }else if(lap>=5 && lap<7){
    FastLED.showColor(color(255, 128, 0));
  }else if(lap>=7){
    FastLED.showColor(color(255, 0, 0));
    engine.stop();
    delay(10000);    // Pour pas que la boucle recommence tout de suite
  }
}
