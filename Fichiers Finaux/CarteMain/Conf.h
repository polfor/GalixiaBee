//////////////////////////////////////////////////////////////////////
/////////////////// Bee  -  Configuration / Preset ///////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////


#ifndef Conf_h
#define Conf_h
#define EEPROM_I2C_ADDRESS 0x50
#define PRESET_SIZE 12
#include "Arduino.h"
#include <Wire.h>

class Conf
{
	public:
		Conf();
		void setPreset(int);
		void editConf(byte[]);
		
		void editGPS(byte[]);
		void editAcc(byte[]);
		
		bool getGPSActivated();
		bool getAccActivated();

		bool getGPSMondayWorked();
		bool getGPSTuesdayWorked();
		bool getGPSWednesdayWorked();
		bool getGPSThursdayWorked();
		bool getGPSFridayWorked();
		bool getGPSSaturdayWorked();
		bool getGPSSundayWorked();
		
		bool getAccMondayWorked();
		bool getAccTuesdayWorked();
		bool getAccWednesdayWorked();
		bool getAccThursdayWorked();
		bool getAccFridayWorked();
		bool getAccSaturdayWorked();
		bool getAccSundayWorked();
			
		int  getGPSWorkDayStartHr();
    int  getGPSWorkDayStartMn();
		int  getAccWorkDayStartHr();
    int  getAccWorkDayStartMn();
		
		int  getGPSWorkDayEndHr();
    int  getGPSWorkDayEndMn();
		int  getAccWorkDayEndHr();
    int  getAccWorkDayEndMn();
		
		int  getGPSActivations();
		int	 getAccActivations();
	private:
		bool isGPSActivated, isAccActivated,
			 gpsMon, gpsTue, gpsWed, gpsThu, gpsFri, gpsSat, gpsSun,
			 accMon, accTue, accWed, accThu, accFri, accSat, accSun;
			 
		int gpsWorkDayStartHr, gpsWorkDayStartMn, gpsWorkDayEndHr, gpsWorkDayEndMn, gpsActivations, 
			  accWorkDayStartHr, accWorkDayStartMn, accWorkDayEndHr, accWorkDayEndMn, accActivations;
};

#endif
