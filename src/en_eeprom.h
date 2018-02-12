#include "Arduino.h"
#include <Wire.h>
// http://ww1.microchip.com/downloads/en/DeviceDoc/21709c.pdf
// Define 24LC02 I2C addressing
#define I2C_EEPROM_ADDRESS 0x50


void eepromInit();

void eepromWriteByte(uint8_t address, uint8_t data);
uint8_t eepromReadByte(uint8_t address);

void eepromWrite_uint32(uint8_t address, uint32_t data );
uint32_t eepromRead_uint32(uint8_t address);

void eepromWrite_uint64(uint8_t address, uint64_t data );
uint64_t eepromRead_uint64(uint8_t address);

void eepromWriteBuffer(uint8_t address, uint8_t data[], uint8_t length);
void eepromReadBuffer(uint8_t address, uint8_t * data, uint8_t length);
