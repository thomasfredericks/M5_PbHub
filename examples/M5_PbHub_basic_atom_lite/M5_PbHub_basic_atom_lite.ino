

// Inclure la librairie M5 (version pour M5Atom) :
// https://github.com/m5stack/M5Atom
#include <M5Atom.h>

// Inclure la librairie FastLED qui va gérer le pixel :
// https://github.com/FastLED/FastLED
#include <FastLED.h>

// Un tableau qui contient une variable de type CRGB.
// Il y a un seul pixel, mais il doit être dans un tableau.
// CRGB est un type de couleur défini par la lirairie FastLed :
// https://github.com/FastLED/FastLED/wiki/Pixel-reference#crgb-reference
CRGB mesPixels[1];

#include <M5_PbHub.h>
M5_PbHub myPbHub;

#define KEY_UNIT_CHANNEL 4
#define ANGLE_UNIT_CHANNEL 3
#define PIR_UNIT_CHANNEL 2
#define LIGHT_UNIT_CHANNEL 1

unsigned long monChronoDepart = 0;

void setup() {
  // Démarrer la libraire M5 avec toutes les options de pré-configuration désactivées :
  M5.begin(false, false, false);

  // Démarrer la connexion sérielle :
  Serial.begin(115200);

  // Ajouter le pixel (il y en a un seul) du M5Atom à la librairie FastLED :
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(mesPixels, 1);

  myPbHub.begin();

  myPbHub.setPixelCount(KEY_UNIT_CHANNEL, 1);
}

void loop() {
  // TOUJOURS inclure M5.update() au début de loop() :
  M5.update();

  if (millis() - monChronoDepart >= 50) {  // SI LE TEMPS ÉCOULÉ DÉPASSE 50 MS...
    monChronoDepart = millis();            // ...REDÉMARRER LE CHRONOMÈTRE...

    Serial.print("KEY: ");
    int maValeurKey = myPbHub.digitalRead(KEY_UNIT_CHANNEL);
    Serial.print(maValeurKey);

    // Allumer le pixel du KEY si son bouton est appuyé
    myPbHub.setPixelColor(KEY_UNIT_CHANNEL, 0, maValeurKey * 255, maValeurKey * 255, maValeurKey * 255);

    Serial.print(" ANGLE: ");
    int maValeurAngle = myPbHub.analogRead(ANGLE_UNIT_CHANNEL);
    Serial.print(maValeurAngle);

    Serial.print(" PIR: ");
    int maValeurPir = myPbHub.analogRead(PIR_UNIT_CHANNEL);
    Serial.print(maValeurPir);

    Serial.print(" LIGHT: ");
    int maValeurLight = myPbHub.analogRead(LIGHT_UNIT_CHANNEL);
    Serial.print(maValeurLight);
    Serial.println();

  }
}