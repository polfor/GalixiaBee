//////////////////////////////////////////////////////////////////////
////////////////// Bee  -  EEPROM Writing / Reading //////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#ifndef EEPROMStorage_h
#define EEPROMStorage_h

#define EEPROM_I2C_ADDRESS 0x50		// EEPROM's I2C address
#define PRESETS_END 23				// Last byte occupied by the presets

#include "Arduino.h"				
#include <Wire.h>					//Arduino's I2C library

class EEPROMStorage
{
	public:
		EEPROMStorage();

    void initialiseEEPROM();    // Reads lastAddress from the EEPROM and starts the I2C Connection
    
		void writeData(unsigned int, byte);	// Writes one byte of data to the chosen address within the EEPROM
		
		byte readData(unsigned int);		// Reads one byte of data contained in the chosen address
		
		void dynamicWrite(char,int,byte);		// Writes dynamically on the EEPROM

    unsigned int getLastAddress();        // returns lastAddress
	private:
		unsigned int lastAddress;			// The last address something was dynamically written to
};

#endif
