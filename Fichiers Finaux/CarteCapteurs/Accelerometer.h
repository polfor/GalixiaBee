//////////////////////////////////////////////////////////////////////
//////////////////////// Bee  -  Accéléromètre ///////////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#ifndef Accelerometer_h
#define Accelerometer_h

#include "Arduino.h"
#include <Wire.h>

class Accelerometer
{
	public:
		Accelerometer();
		int16_t* getAcc();
    void printer(int16_t);
	private:
  int16_t* accValues[7];
  
};

#endif
