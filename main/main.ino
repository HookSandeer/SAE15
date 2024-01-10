// Code By Antonin Michon & Lucas Colin
// https://github.com/HookSandeer
// Dépot du projet (Avec README.md): https://github.com/HookSandeer/SAE15

// IMPORTS DES LIBRAIRIES & CLASSES :

#include "carMotors.h"                
#include "DeviceDriverSet_xxx0.h"
#include "FastLED.h"
#define PIN_RGBLED 4
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
int lap = 1;            // Variable globale pour le nombre de tour
float seuil = 700.00;

CarMotors engine;   // Création Objet engine pour le controle du moteur      
DeviceDriverSet_ITR20001 AppITR20001;

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);      // Fonction couleur pour le RGB
}

void setup() {
  Serial.begin(9600);
  AppITR20001.DeviceDriverSet_ITR20001_Init();              // Initialise le line track
  FastLED.addLeds<NEOPIXEL, PIN_RGBLED>(leds, NUM_LEDS);   // Initialise la Led 
  FastLED.setBrightness(20);
  engine.init(140);                                       // Initialise le moteur avec une vitesse de 140
  FastLED.showColor(color(255, 0, 0));                    // Alume la led en rouge pendant 3s au debut du programme
  delay(3000);     // Couleur led en rouge pendant 3s
}


void motor(float left, float middle, float right){
  if(left<seuil && middle<seuil && right<seuil){       // Perte de la ligne
    engine.setSpeed(110);                                 // La ligne est souvent perdue au même endroit, cela permet d'essayer de la récupérer
    engine.goForward();
    delay(5);
    engine.turnLeft();
    delay(5);
  }else if(left<seuil && middle>=seuil && right<seuil){ // Tout droit
    engine.setSpeed(140);       // Vitesse
    engine.goForward();         // Avance
    delay(5);                   // Attend 5 ms avant de redemander des valeurs avec une nouvelle execution de la fonction
  }else if(left>=seuil && middle<seuil && right<700){   // Capteur Gauche sur Noir
    engine.setSpeed(110);
    engine.drive(0.9, 0.1);      // Tourne fortement pour récupérer la trajectoire
  }else if(left>=seuil && middle>=seuil && right<700){  // Capteur Gauche & Centre sur Noir
    engine.setSpeed(130);
    engine.drive(0.8, 0.2);     // Tourne pas très fort pour corriger légerement la trajectoire
    delay(5);
  }else if(left<seuil && middle>=seuil && right>=700){ //Capteur Droit & Centre sur Noir
    engine.setSpeed(130);
    engine.drive(0.2, 0.8);
    delay(5);
  }else if(left<seuil && middle<seuil && right>=seuil){ // Capteur Droit Sur Noir
    engine.setSpeed(130);
    engine.drive(0.1, 0.9);
    delay(5);
  }if(left>seuil && middle>seuil && right>seuil){
    lap++;          // Quand les trois capteurs voient du noir, lap est incrémenté de 1, ce qui permet de compter les tours
    delay(60);    // Delai pour éviter que le tour soit compter deux fois
  }
}

void ledControl(int nbrLap){
  if(nbrLap>0 && lap<3){
    FastLED.showColor(color(0, 255, 0));
  }else if(nbrLap>=3 && nbrLap<5){
    FastLED.showColor(color(0, 0, 255));
  }else if(nbrLap>=5 && nbrLap<7){
    FastLED.showColor(color(255, 128, 0));
  }else if(nbrLap>=7){
    FastLED.showColor(color(255, 0, 0));    // Allume la led en rouge a la fin des trois tours
    engine.stop();  // Arrete le moteur
    delay(10000);   // Arrete le programme et le véhicule pendant 10000ms, c'est la fin des trois tours
  }
}

void loop() {
  motor(AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R());   // Execute la fonction qui gere les moteurs
  ledControl(lap);    // Executer la fonction qui gère les leds.
}
