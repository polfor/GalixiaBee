//////////////////////////////////////////////////////////////////////
//////////////////// Bee  -  Main  Carte Capteurs ////////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#include <avr/sleep.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include "Accelerometer.h"
#include "GPS.h"
#include "EEPROMStorage.h"

Accelerometer accelero;
GPS gps;
EEPROMStorage storage;

volatile bool wokenUp = false;
bool received;
byte receivedData = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
  storage.initialiseEEPROM();
}

void loop() {
  // put your main code here, to run repeatedly:
    if(wokenUp){
      Wire.begin(0x10);
      Serial.begin(9600);
      
      Wire.onReceive(receiveEvent);
      unsigned long timeOut = millis();
      while(!received || ((millis() - timeOut) < 10000));
      if(received){
        if(receivedData & 0b10000000)
          Serial.println("Envoi du gps");
          //Envoyer GPS Par SigFox

        if(receivedData & 0b01000000){
          int* accValues = accelero.getAcc();
          Serial.println("Envoi de l'accéléro :");
          for(int i=0; i<=6; i++){
            Serial.println(accValues[i]);
            storage.dynamicWrite('A', 2, accValues[i]);
          }
          //Envoyer accelero avec sigfox
        }

        if(receivedData & 0b00100000)
          Serial.println("Envoi de l'appui : Bouton 1");
          
        if(receivedData & 0b00010000)
          Serial.println("Envoi de l'appui : Bouton 2");
          
        if(receivedData & 0b00001000)
          Serial.println("Envoi de l'appui : Bouton 3");
      }
      else
        Serial.println("Error, I2C timed out !");

      wokenUp = false;
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
}

void wakeUp(){
  wokenUp = true;
}

void receiveEvent(int bytes){
  receivedData = Wire.read();
  received = true;
}
