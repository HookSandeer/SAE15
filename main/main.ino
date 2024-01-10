// Code By Antonin Michon & Lucas Colin
// https://github.com/HookSandeer
// Dépot du projet (Avec README.md): https://github.com/HookSandeer/SAE15

// IMPORTS DES LIBRAIRIES & CLASSES :

#include "carMotors.h"                
#include "DeviceDriverSet_xxx0.h"
#include "FastLED.h"
#define PIN_RGBLED 4                                          // Définit le pin de Sortie de la Led
#define NUM_LEDS 1                                            // Définie le nombre de Leds a gérer, une seule dans notre cas
CRGB leds[NUM_LEDS];                                          // Initialise le nombre de led, une seule dans notre cas.
int lap = 1;                                                  // Variable globale pour le nombre de tour
float seuil = 700.00;                                         // Variable globale pour le seuil de détection de la ligne noir au sol.
char last;                                                    // Variable globale pour le stockage de la dernère action réalisée

CarMotors engine;                                             // Création de l'Objet engine pour le controle du moteur      
DeviceDriverSet_ITR20001 AppITR20001;                         // Création de l'Object AppITR20001 pour le controle du capteur

uint32_t color(uint8_t r, uint8_t g, uint8_t b) {             
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);      // Fonction couleur pour le RGB, pour l'affichage plus simple des couleurs
}

void setup() {
  Serial.begin(9600);
  AppITR20001.DeviceDriverSet_ITR20001_Init();                // Initialise le line track
  FastLED.addLeds<NEOPIXEL, PIN_RGBLED>(leds, NUM_LEDS);      // Initialise la Led 
  FastLED.setBrightness(10);                                  // Intensité lumineuse de la Led
  engine.init(255);                                           // Initialise le moteur avec une vitesse de 255 (Vitesse maximum)
  FastLED.showColor(color(255, 0, 0));                        // Allume la Led en rouge pendant 3s au debut du programme
  delay(3000);                                                // 3 seconde avant le départ
}

void correction(char lst){                                    // Fonction qui corrige la trajectoire en fonction de la denère action effectué
  if(lst == "d"){                                             // Si la dernière action était de tourner a droite,
    engine.drive(0.3, 0.9);                                   // Alors il faut tourner a gauche
  }else if(lst == "g"){                                       // Même principe ici.
    engine.drive(0.9, 0.3);
  }
}


void motor(float left, float middle, float right){         // Fonction pour la gestion des moteurs en fonction des valeurs des capteurs
  if(left<seuil && middle<seuil && right<seuil){          // Perte de la ligne
    correction(last);                                     // Appelle la fonction correction pour corriger la trajectoire
  }else if(left<seuil && middle>=seuil && right<seuil){   // Tout droit
    engine.goForward();                                   // Avance
  }else if(left>=seuil && middle<seuil && right<seuil){   // Capteur Gauche sur Noir
    engine.drive(0.9, 0.3);                               // Tourne fortement pour récupérer la trajectoire
    last = "d";                                           // Enregistre la dernière action effectué
  }else if(left>=seuil && middle>=seuil && right<seuil){  // Capteur Gauche & Centre sur Noir
    engine.drive(0.9, 0.6);                               // Tourne pas très fort pour corriger légerement la trajectoire
  }else if(left<seuil && middle>=seuil && right>=seuil){  // Capteur Droit & Centre sur Noir
    engine.drive(0.6, 0.9);                               // Tourne légerement a droite
  }else if(left<seuil && middle<seuil && right>=seuil){   // Capteur Droit Sur Noir
    engine.drive(0.3, 0.9);                               // Tourne fortement à droite
    last = "g";                                           // Enregistre la dernière action
  }if(left>seuil && middle>seuil && right>seuil){         // Les trois capteurs sont sur la ligne noir
    lap++;                                                // Ajoute un tour a la variable
    delay(50);                                            // Delai pour éviter que le tour soit compté deux fois
  }
}

void ledControl(int nbrLap){                              // Fonction qui gère la Led Multicolor
  if(nbrLap>0 && lap<3){                                  // Le nombre de tour est compris entre 1 et 2, car le capteur compte 2 passage sur la ligne en un tour, en raison du croisement
    FastLED.showColor(color(0, 255, 0));                  
  }else if(nbrLap>=3 && nbrLap<5){
    FastLED.showColor(color(0, 0, 255));                  // Même principe, en fonction du nombre de tour la bonne couleur s'affiche
  }else if(nbrLap>=5 && nbrLap<7){
    FastLED.showColor(color(255, 128, 0));
  }else if(nbrLap>=7){                                    // Si les trois tours sont terminé alors :
    FastLED.showColor(color(255, 0, 0));                  // Allume la Led en rouge a la fin des trois tours
    engine.setSpeed(100);                                 // Ralentit pour la marche arrière pour revenir sur la ligne d'arrivée
    engine.goBackward();                                  // Reviens sur la ligne d'arrivée
    delay(150);                                           // Recule pendant 150 ms
    engine.stop();                                        // Arrete le moteur
    delay(10000);                                         // Arrete le programme  pendant 10000ms, c'est la fin des trois tours
  }
}

void loop() {                                             // Programme principal, qui appelle les fonctions en boucle sans delai.
  motor(AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_L(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_M(), AppITR20001.DeviceDriverSet_ITR20001_getAnaloguexxx_R());   // Execute la fonction qui gere les moteurs, avec en parametre les valeurs des trois capteurs.
  ledControl(lap);                                        // Executer la fonction qui gère les leds.
}
