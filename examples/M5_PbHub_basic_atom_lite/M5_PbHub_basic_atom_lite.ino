

// Le code de base pour le M5Stack Atom
#include <M5Atom.h> // Inclure la librairie M5 (version pour M5Atom) https://github.com/m5stack/M5Atom
CRGB pixel; // CRGB est défini par FastLed https://github.com/FastLED/FastLED/wiki/Pixel-reference#crgb-reference
unsigned long monChronoMessages; // Utilisé dans loop() plus bas pour limiter la vitesse d'envoi des messages

#include <M5_PbHub.h>
M5_PbHub myPbHub;

#define ANGLE_UNIT_CHANNEL 0
#define LIGHT_UNIT_CHANNEL 1
#define MOTION_UNIT_CHANNEL 2
#define KEY_UNIT_CHANNEL 5

void setup() {
  M5.begin(false, false, false); // Démarrer la libraire M5 avec toutes les options désactivées
  Serial.begin(115200); // Démarrer la connexion sérielle avec l'ordinateur
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(&pixel, 1); // Ajouter le pixel du M5Atom à FastLED

  // Animation de démarrage
  while ( millis() < 5000) {
    // Allumer le pixel et attendre 100 millisecondes
    pixel = CRGB(255,255,255);
    FastLED.show();
    delay(100);
    // Éteindre le pixel et attendre 100 millisecondes
    pixel = CRGB(0,0,0);
    FastLED.show();
    delay(100);
  } 

  // Démarrer la connexion Wire utilisée par M5_PbHub:
  Wire.begin();
  myPbHub.begin();
  // Initialiser le pixel du Key Unit
  myPbHub.setPixelCount(KEY_UNIT_CHANNEL, 1);
}

void loop() {
   M5.update();  // Toujours inclure M5.update() au début de loop()
  if ( millis() - monChronoMessages >= 50 ) { // Si 50 millisecondes se sont écoulées
    monChronoMessages = millis(); // Repartir le compteur

    Serial.print("KEY: ");
    int maValeurKey = myPbHub.digitalRead(KEY_UNIT_CHANNEL);
    Serial.print(maValeurKey);

    // Allumer le pixel du KEY si son bouton est appuyé
    myPbHub.setPixelColor(KEY_UNIT_CHANNEL, 0, maValeurKey * 255, maValeurKey * 255, maValeurKey * 255);

    Serial.print(" ANGLE: ");
    int maValeurAngle = myPbHub.analogRead(ANGLE_UNIT_CHANNEL);
    Serial.print(maValeurAngle);

    Serial.print(" MOTION: ");
    int maValeurMotion = myPbHub.digitalRead(MOTION_UNIT_CHANNEL);
    Serial.print(maValeurMotion);

    Serial.print(" LIGHT: ");
    int maValeurLight = myPbHub.analogRead(LIGHT_UNIT_CHANNEL);
    Serial.print(maValeurLight);
    Serial.println();
  }

}