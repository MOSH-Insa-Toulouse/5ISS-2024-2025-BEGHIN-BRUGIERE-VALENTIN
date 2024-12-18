#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10,11);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  loraSerial.begin(57600);
  pinMode(7,OUTPUT);

  Serial.println("Initialisation du RN2483...");
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

  //Connexion
  sendCommand(F("mac join otaa"));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (loraSerial.available()){
    String response = loraSerial.readStringUntil('\n');
    Serial.println("RN2483: " + response);
  }

  if (Serial.available()){
    String command = Serial.readStringUntil('\n');
    sendCommand(command);
  }
}

void sendCommand(String command){
  loraSerial.println(command);
  Serial.println("Envoye : " + command);
  delay(200);
  if (loraSerial.available()){
    String response = loraSerial.readStringUntil('\n');
    Serial.println("RN2483: " + response);
  }
}
