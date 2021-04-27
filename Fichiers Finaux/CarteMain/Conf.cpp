//////////////////////////////////////////////////////////////////////
/////////////////// Bee  -  Configuration / Preset ///////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#include "Conf.h"
#include "Arduino.h"

Conf::Conf()
{
	Wire.begin();
}

void Conf::setPreset(int presetNumber)
{
	byte result[12];
	for(int i=0; i<PRESET_SIZE;i++)
	{
		Wire.beginTransmission(EEPROM_I2C_ADDRESS);
		Wire.write((int)(((PRESET_SIZE*presetNumber)+i) >>8));
		Wire.write((int)(((PRESET_SIZE*presetNumber)+i) & 0xFF));
		Wire.endTransmission();
		Wire.requestFrom(EEPROM_I2C_ADDRESS,1); 
		result[i] = Wire.read();
	}
	
	isGPSActivated = (result[0] & 0b10000000);
	
	gpsMon = (result[0] & 0b01000000);
	gpsTue = (result[0] & 0b00100000);
	gpsWed = (result[0] & 0b00010000);
	gpsThu = (result[0] & 0b00001000);
	gpsFri = (result[0] & 0b00000100);
	gpsSat = (result[0] & 0b00000010);
	gpsSun = (result[0] & 0b00000001);
	
	gpsWorkDayStartHr = result[1];
	gpsWorkDayStartMn = result[2];
	gpsWorkDayEndHr   = result[3];
	gpsWorkDayEndMn   = result[4];
	
	gpsActivations  = result[5];
	
	isAccActivated = (result[6] & 0b10000000);
	
	accMon = (result[6] & 0b01000000);
	accTue = (result[6] & 0b00100000);
	accWed = (result[6] & 0b00010000);
	accThu = (result[6] & 0b00001000);
	accFri = (result[6] & 0b00000100);
	accSat = (result[6] & 0b00000010);
	accSun = (result[6] & 0b00000001);
	
	accWorkDayStartHr = result[7];
	accWorkDayStartMn = result[8];
	accWorkDayEndHr   = result[9];
	accWorkDayEndMn   = result[10];
	
	accActivations  = result[11];
}

void Conf::editConf(byte received[])
{
	switch (received[0])
	{
		case 0b01000111 :
			editGPS(received);
			break;
			
		case 0b01000001 :
			editAcc(received);
			break;
		
		case 0b01010000 :
			setPreset(received[1]);
			break;
	}
}

//paramétrage du gps selon la réception
void Conf::editGPS(byte received[])
{
	for(int i=1; i<= 7; i++)
	{
		switch (received[i])
		{
			case 0b01010011 :
				i++;
				gpsWorkDayStartHr = received[i];
				i++;
				gpsWorkDayStartMn = received[i];
				break;
			
			case 0b01000101 :
				i++;
				gpsWorkDayEndHr = received[i];
				i++;
				gpsWorkDayEndMn = received[i];
				break;
			
			case 0b01001110 :
				i++;
				gpsActivations = received[i];
				break;
				
			case 0b01010111 :
				i++;
				isGPSActivated = (received[i] & 0b10000000);
				gpsMon = (received[i] & 0b01000000);
				gpsTue = (received[i] & 0b00100000);
				gpsWed = (received[i] & 0b00010000);
				gpsThu = (received[i] & 0b00001000);
				gpsFri = (received[i] & 0b00000100);
				gpsSat = (received[i] & 0b00000010);
				gpsSun = (received[i] & 0b00000001);
				break;
		}
		
	}
}

//paramétrage de l'accéléromètre selon la réception
void Conf::editAcc(byte received[])
{
	for(int i=1; i<= sizeof(received); i++)
	{
		switch (received[i])
		{
			case 0b01010011 :
				i++;
				accWorkDayStartHr = received[i];
				i++;
				accWorkDayStartMn = received[i];
				break;
			
			case 0b01000101 :
				i++;
				accWorkDayEndHr = received[i];
				i++;
				accWorkDayEndMn = received[i];
				break;
			
			case 0b01001110 :
				i++;
				accActivations = received[i];
				break;
				
			case 0b01010111 :
				i++;
				isAccActivated = (received[i] & 0b10000000);
				accMon = (received[i] & 0b01000000);
				accTue = (received[i] & 0b00100000);
				accWed = (received[i] & 0b00010000);
				accThu = (received[i] & 0b00001000);
				accFri = (received[i] & 0b00000100);
				accSat = (received[i] & 0b00000010);
				accSun = (received[i] & 0b00000001);
				break;
		}
		
	}
}

//------------------------------------Accesseurs GPS---------------------------------

//GPS Activé ou non :
bool Conf::getGPSActivated()
{
	return(isGPSActivated);
}

//Jours Travaillés :
bool Conf::getGPSMondayWorked()
{
	return(gpsMon);
}

bool Conf::getGPSTuesdayWorked()
{
	return(gpsTue);
}

bool Conf::getGPSWednesdayWorked()
{
	return(gpsWed);
}

bool Conf::getGPSThursdayWorked()
{
	return(gpsThu);
}

bool Conf::getGPSFridayWorked()
{
	return(gpsFri);
}

bool Conf::getGPSSaturdayWorked()
{
	return(gpsSat);
}

bool Conf::getGPSSundayWorked()
{
	return(gpsSun);
}

//Heure d'activation et de fin chaque jour ( en heures puis minutes) :
int  Conf::getGPSWorkDayStartHr()
{
	return(gpsWorkDayStartHr);
}

int  Conf::getGPSWorkDayStartMn()
{
  return(gpsWorkDayStartMn);
}

int  Conf::getGPSWorkDayEndHr()
{
	return(gpsWorkDayEndHr);
}

int  Conf::getGPSWorkDayEndMn()
{
  return(gpsWorkDayEndMn);
}

//Nombre d'activations du GPS / jour :
int  Conf::getGPSActivations()
{
	return(gpsActivations);
}

//------------------------------------Accesseurs Accéléromètre-----------------------

//Accéléromètre activé ou non :

bool Conf::getAccActivated()
{
	return(isAccActivated);
}

//Jours Travaillés :

bool Conf::getAccMondayWorked()
{
	return(accMon);
}

bool Conf::getAccTuesdayWorked()
{
	return(accTue);
}

bool Conf::getAccWednesdayWorked()
{
	return(accWed);
}

bool Conf::getAccThursdayWorked()
{
	return(accThu);
}

bool Conf::getAccFridayWorked()
{
	return(accFri);
}

bool Conf::getAccSaturdayWorked()
{
	return(accSat);
}

bool Conf::getAccSundayWorked()
{
	return(accSun);
}

//Heure d'activation et de fin chaque jour ( en heures puis minutes) :
int  Conf::getAccWorkDayStartHr()
{
	return(accWorkDayStartHr);
}

int  Conf::getAccWorkDayStartMn()
{
  return(accWorkDayStartMn);
}

int  Conf::getAccWorkDayEndHr()
{
	return(accWorkDayEndHr);
}

int  Conf::getAccWorkDayEndMn()
{
  return(accWorkDayEndMn);
}

//Nombre d'activations de l'accéléromètre / jour :
int  Conf::getAccActivations()
{
	return(accActivations);
}
