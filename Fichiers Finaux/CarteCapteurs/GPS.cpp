//////////////////////////////////////////////////////////////////////
///////////////////////////// Bee  -  GPS ////////////////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "GPS.h"

GPS::GPS()
{

  Serial.begin(9600);			
    
//start the gpsSerial port for the GPS
}

double* GPS::getGPS()
{
  bool a = false;
  bool b = false;
  bool c = false;
  bool d = false;
    while(Serial.available() == 0);
  while(!a || !b || !c || !d){
    gps.encode(Serial.read());
    if(gps.date.isUpdated()){
      *gpsValues[0] = (double)gps.date.year();
      *gpsValues[1] = (double)gps.date.month();
      *gpsValues[2] = (double)gps.date.day();
      a = true;
    }
    
    if(gps.time.isUpdated()){
      *gpsValues[3] = (double)gps.time.hour();
      *gpsValues[4] = (double)gps.time.minute();
      b = true;
    }
    
    if(gps.location.isUpdated()){
      *gpsValues[5] = (double)gps.location.lng();
      *gpsValues[6] = (double)gps.location.lat();
      c = true;
    }

    if(gps.altitude.isUpdated()){
      *gpsValues[7] = (double)gps.altitude.meters();
      d = true;
    }
  
	}

return(*gpsValues);

	}
