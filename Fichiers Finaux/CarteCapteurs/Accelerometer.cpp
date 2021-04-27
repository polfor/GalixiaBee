//////////////////////////////////////////////////////////////////////
//////////////////////// Bee  -  Accéléromètre ///////////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "Accelerometer.h"

Accelerometer::Accelerometer()
{	
	Serial.begin(9600);
    Wire.begin();

}

int16_t* Accelerometer::getAcc()
{
  Wire.beginTransmission(0x68);                // reset the accValues !mettre en variable!
  Wire.write(0x6B);                       //mettre en variable
  Wire.write(0);    
  Wire.endTransmission(true);               
  
  Wire.beginTransmission(0x68);                // start the true communication
  Wire.write(0x3B);  
  Wire.endTransmission(false);              
  Wire.requestFrom(0x68,14,true);              // ask the accelerometer for 14 bytes
  accValues[0] = Wire.read()<<8|Wire.read();   // X axis of the accelerometer 
  accValues[1] = Wire.read()<<8|Wire.read();   // Y axis of the accelerometer
  accValues[2] = Wire.read()<<8|Wire.read();   // Z axis of the accelerometer  
  accValues[3] = Wire.read()<<8|Wire.read();   // Temperature
  accValues[4] = Wire.read()<<8|Wire.read();   // X axis of the gyroscope
  accValues[5] = Wire.read()<<8|Wire.read();   // Y axis of the gyroscope
  accValues[6] = Wire.read()<<8|Wire.read();   // Z axis of the gyroscope

  return(*accValues);
}
