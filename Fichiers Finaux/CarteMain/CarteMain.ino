#include <Wire.h>
#include "Conf.h"

Conf conf;
bool accDays[7];
bool gpsDays[7];
String daysOfTheWeek[7] = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
unsigned long timer;
int c = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  conf.setPreset(0);
  Serial.println("lundi");
  Serial.println(conf.getAccActivations());
  unsigned long gpsStartTime = (conf.getGPSWorkDayStartHr() * ((unsigned long)2500)) + (conf.getGPSWorkDayStartMn() * ((unsigned long)(2500/60)));
  unsigned long gpsEndTime = (conf.getGPSWorkDayEndHr() * ((unsigned long)2500)) + (conf.getGPSWorkDayEndMn() * ((unsigned long)(2500/60)));
  unsigned long accStartTime = (conf.getAccWorkDayStartHr() * ((unsigned long)2500)) + (conf.getAccWorkDayStartMn() * ((unsigned long)(2500/60)));
  unsigned long accEndTime = (conf.getAccWorkDayEndHr() * ((unsigned long)2500)) + (conf.getAccWorkDayEndMn() * ((unsigned long)(2500/60)));

  unsigned long gpsTab[conf.getGPSActivations()];
  gpsTab[0] = gpsStartTime;
  Serial.println(gpsTab[0]);
  for(int i=1; i<= (conf.getGPSActivations()-1); i++){
    gpsTab[i] = gpsTab[i-1] + ((gpsEndTime - gpsStartTime)/(conf.getGPSActivations() - 1));
  }
  unsigned long accTab[conf.getAccActivations()];
  accTab[0] = accStartTime;
  Serial.println(accTab[0]);
  for(int i=1; i<= (conf.getAccActivations()-1); i++){
    accTab[i] = accTab[i-1] + ((accEndTime - accStartTime)/(conf.getAccActivations() - 1));
  }
  
  accDays[0] = conf.getAccMondayWorked();
  accDays[1] = conf.getAccTuesdayWorked();
  accDays[2] = conf.getAccWednesdayWorked();
  accDays[3] = conf.getAccThursdayWorked();
  accDays[4] = conf.getAccFridayWorked();
  accDays[5] = conf.getAccSaturdayWorked();
  accDays[6] = conf.getAccSundayWorked();
  
  gpsDays[0] = conf.getGPSMondayWorked();
  gpsDays[1] = conf.getGPSTuesdayWorked();
  gpsDays[2] = conf.getGPSWednesdayWorked();
  gpsDays[3] = conf.getGPSThursdayWorked();
  gpsDays[4] = conf.getGPSFridayWorked();
  gpsDays[5] = conf.getGPSSaturdayWorked();
  gpsDays[6] = conf.getGPSSundayWorked();
  
  int gpsSize = sizeof(gpsTab)/4;
  int accSize = sizeof(accTab)/4;
  
  int g = 0;
  int a = 0;
  
  while(1){
    
  Serial.println(daysOfTheWeek[c]);

  timer = millis(); //utilisation de millis mais à éventuellement remplacer par la RTC

  
  while((g < gpsSize) || (a < accSize)){
    if(gpsTab[g] < accTab[a]){
      while((millis() - timer) <= gpsTab[g]);
    if(conf.getGPSActivated() && conf.getGPSMondayWorked()){
      Serial.println("activation du gps");
      digitalWrite(2, HIGH);
      Wire.beginTransmission(0x10);
      Wire.write(0b10000000);
      Wire.endTransmission();
      digitalWrite(2, LOW);
    }
      g++;
      
    }
    else{ 
      if(gpsTab[g] == accTab[a]){
        while((millis() - timer) <= gpsTab[g]);
        if(conf.getAccActivated() && conf.getAccMondayWorked())
          Serial.println("activation de l'accéléro");
        if(conf.getGPSActivated() && conf.getGPSMondayWorked())
          Serial.println("activation du gps");
        a++;
        g++;
      }
      else{
        while((millis() - timer) <= accTab[a]);
        if(conf.getAccActivated() && conf.getAccMondayWorked())
          Serial.println("activation de l'accéléro");
        a++;
      }
    }
  }

  g = a = 0;
  while((millis() - timer) < 60000);
  c++;
  if(c >= 7)
    c = 0;
  }
}

void loop() {
  
  
}
