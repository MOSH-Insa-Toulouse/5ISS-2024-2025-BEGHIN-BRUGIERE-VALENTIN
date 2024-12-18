#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10,11);

//----------------CONFIGURATION OLED----------------------//
// Taille de l'écran OLED (peut varier selon le modèle, ici 128x64)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Adresse I2C de l'écran OLED (par défaut : 0x3C)
#define OLED_ADDR 0x3C

// Déclaration de l'objet écran
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//---------------CONFIGURATION CAPTEUR GAZ---------------//
const float RL_VALUE = 10.0; // Résistance de charge (en kΩ)
const float RO_CLEAN_AIR_FACTOR = 6.5; // Facteur Ro pour l'air propre (selon la datasheet)

float Ro = 10.0; // Résistance Ro initiale
float COCurve[3] = {2.3, 0.72, -0.34}; // Courbe pour le CO

void setup() {
  
  //---------------------Init OLED---------------------------------//
  Serial.println(F("Initialisation de l'OLED..."));
  // Initialisation de l'écran OLED
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("Échec de l'initialisation de l'écran OLED !"));
    while (true); // Bloque si l'écran ne démarre pas
  }
  // Efface l'écran
  display.clearDisplay();
  // Affichage du message "Joyeux Noël"
  display.setTextSize(2);         // Taille du texte (1 = petit, 2 = moyen, etc.)
  display.setTextColor(SSD1306_WHITE); // Couleur du texte (blanc sur fond noir)

  display.setCursor(10, 20);     // Position du texte (x=10, y=20)
  display.println(F(" Joyeux"));
  display.setCursor(10, 40);     // Position pour la ligne suivante
  display.println(F("  Noel!"));

  display.display(); // Met à jour l'affichage
  
  //----------------------Init LoRa-----------------------//
  loraSerial.begin(57600);
  pinMode(7,OUTPUT);

  Serial.println(F("Initialisation du RN2483..."));
  delay(1000);
  
  //Configuration
  digitalWrite(7,LOW);
  delay(1000);
  digitalWrite(7,HIGH);

  sendCommand(F("sys get ver"));
  delay(1000);
  sendCommand(F("mac set deveui a201a835645792c1"));
  delay(1000);
  sendCommand(F("mac get deveui"));
  delay(1000);
  sendCommand(F("mac set appeui a330a043fa4c27d3"));
  delay(1000);
  sendCommand(F("mac get appeui"));
  delay(1000);
  sendCommand(F("mac set appkey c2166795d078edc076cb9e9cc7143140"));
  delay(1000);

  //Connection
  sendCommand(F("mac join otaa"));

  //----------Init Gurlande---------------//
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  //-----------Gas sensor------------------//
  Serial.println("Calibrating the sensor...");
  Ro = calibrateSensor();
  Serial.print("Calibration done! Ro = ");
  Serial.print(Ro);
  Serial.println(" kΩ");
}

void loop() {
  if (loraSerial.available()){
    String response = loraSerial.readStringUntil('\n');
    Serial.println("RN2483: " + response);
  }

  if (Serial.available()){
    String command = Serial.readStringUntil('\n');
    sendCommand(command);
  }
 
  float rs = readSensor(A0); // Lire Rs
  float ratio = rs / Ro; // Calculer Rs/Ro
  float ppm = getGasPPM(ratio, COCurve); // Convertir en ppm pour le CO
   
  display.clearDisplay();
  display.setCursor(10, 20);     // Position du texte (x=10, y=20)
  display.println(F(" CO:"));
  display.setCursor(10, 40);     // Position pour la ligne suivante
  display.println(ppm);

  display.display(); // Met à jour l'affichage

  //----------Guirlande------------//
  if (ppm<100){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
  } else if ((ppm>100) && (ppm<200)){
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
  } else if (ppm>200){
    digitalWrite(6,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }


  // Envoi de la valeur ppm via LoRa
  sendPPMData(ppm);

  delay(1000);

}

void sendCommand(String command){
  while (loraSerial.available()){
    loraSerial.read();
  }
  loraSerial.println(command);
  Serial.println("Envoye : " + command);
  delay(1000);
  if (loraSerial.available()){
    String response = loraSerial.readStringUntil('\n');
    Serial.println("RN2483: " + response);
  }
}


// Fonction pour lire la résistance Rs
float readSensor(int pin) {
  int rawValue = analogRead(pin);
  float voltage = (rawValue / 1023.0) * 5.0; // Convertir en tension
  float rs = (5.0 - voltage) / voltage * RL_VALUE; // Calculer Rs
  return rs;
}

// Fonction de calibration
float calibrateSensor() {
  float rs = 0.0;
  for (int i = 0; i < 50; i++) {
    rs += readSensor(A0);
    delay(500);
  }
  rs = rs / 50.0; // Moyenne des valeurs lues
  return rs / RO_CLEAN_AIR_FACTOR; // Calculer Ro
}

// Fonction pour calculer le ppm
float getGasPPM(float ratio, float *curve) {
  return pow(10, ((log10(ratio) - curve[1]) / curve[2]) + curve[0]);
}

void sendPPMData(float ppm) {
  // Convertir le ppm en entier pour l'envoyer via LoRa (arrondi si nécessaire)
  int ppmInt = (int)ppm;
  
  // Convertir la valeur en hexadécimal
  String hexPayload = String(ppmInt, HEX);
  
  // Assurez-vous que la longueur de la chaîne est pair (Le module LoRa nécessite des octets pairs)
  if (hexPayload.length() % 2 != 0) {
    hexPayload = "0" + hexPayload; // Ajouter un zéro au début si la longueur est impaire
  }

  // Préparer la commande pour l'envoi via LoRa
  String command = "mac tx cnf 1 " + hexPayload;
  sendCommand(command); // Envoi de la commande avec le payload hexadécimal
}
