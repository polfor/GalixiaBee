//////////////////////////////////////////////////////////////////////
////////////////// Bee  -  EEPROM Writing / Reading //////////////////
///////////////////// -------------------------- /////////////////////
/////////////////////// Paul FORSANS / GALIXIA ///////////////////////
///////////////////// pro.forsans.paul@gmail.com /////////////////////
//////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "EEPROMStorage.h"

EEPROMStorage::EEPROMStorage()
{								

}

void EEPROMStorage::initialiseEEPROM()
{
  Wire.begin();               // Start the I2C Bus
  
  byte lastAddressLSByte = readData(PRESETS_END+1); // Read the two parts of lastAddress
  byte lastAddressMSByte = readData(PRESETS_END+2);  // that are stored in the EEPROM
  
  lastAddress = lastAddressLSByte | (lastAddressMSByte << 8); // Assemble lastAddress
}


byte EEPROMStorage::readData(unsigned int address)
{
	byte result;										// Variable that will contain what's read
	
	Wire.beginTransmission(EEPROM_I2C_ADDRESS);			// Connect to the EEPROM
	
	Wire.write((int)(address >>8));						
	Wire.write((int)(address & 0xFF));					// Queue the request and the address we want to read
	
	Wire.endTransmission();								// Send the queue
	
	Wire.requestFrom(EEPROM_I2C_ADDRESS,1); 	
	result = Wire.read();								// Read what the EEPROM sends us
		
	return(result);
}

void EEPROMStorage::writeData(unsigned int address, byte data)
{
	Wire.beginTransmission(EEPROM_I2C_ADDRESS);			// Connect to the EEPROM
	
	Wire.write((int)(address >> 8));	
	Wire.write((int)(address & 0xFF));					// Queue the request and the address we want to write to
	
	Wire.write(data);									// Queue the Data
	
	Wire.endTransmission();								// Send the queue
	
	delay(10);
}

void EEPROMStorage::dynamicWrite(char identifier, int size, byte data)
{
	lastAddress++;
  		
  writeData(lastAddress, identifier);   // Write the identifier to the next free byte in the EEPROM              
  lastAddress++;		
  
  if(size <= 1)
  {			

  	writeData(lastAddress, data);			// Write the data to the next free byte in the EEPROM
  	
  	byte lastAddressLSByte = (byte)(lastAddress & 0xFF);				    // Separate the lastAddress' 2 bytes
  	byte lastAddressMSByte =  (byte)((lastAddress >> 8) & 0xFF);		// in order to write them on the EEPROM
  	
  	writeData(PRESETS_END+1, lastAddressLSByte);		
  	writeData(PRESETS_END+2, lastAddressMSByte);					// Store the last address written to
  }
  else
  {
    for(int i = 0; i < size; i++){
      writeData(lastAddress, (byte)(data >> (8*i)) & 0xFF);     // Write each byte on a different address(lowest byte to highest byte)
      lastAddress++;
    }
    
    byte lastAddressLSByte = (byte)(lastAddress & 0xFF);            // Separate the lastAddress' 2 bytes
    byte lastAddressMSByte =  (byte)((lastAddress >> 8) & 0xFF);    // in order to write them on the EEPROM
    
    writeData(PRESETS_END+1, lastAddressLSByte);    
    writeData(PRESETS_END+2, lastAddressMSByte);          // Store the last address written to
  }
}

unsigned int EEPROMStorage::getLastAddress()
{
  return(lastAddress);                                    
}
