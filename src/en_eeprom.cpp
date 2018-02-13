#include "en_eeprom.h"
#ifndef en_eeprom_h
#define en_eeprom_h

// EEPROM::EEPROM() {}

union ArrayToInteger {
 uint8_t array[4];
 uint32_t integer;
};

union ArrayToInteger64 {
 uint8_t array[8];
 uint32_t integer;
};

void EEPROM::init(){
  Wire.begin();
}

void EEPROM::writeBuffer(uint8_t address, uint8_t data[], uint8_t length ){
  // Todo: blocking should only write 8 bytes at a time....
  // See page 8 of http://ww1.microchip.com/downloads/en/DeviceDoc/21709c.pdf
  Wire.beginTransmission(I2C_EEPROM_ADDRESS);
  Wire.write(address);
  uint8_t dataIndex = 0;
  while( dataIndex < length ){
    Wire.write(data[dataIndex]);
    dataIndex++;
  }
  Wire.endTransmission();
  // Writing in I2C EEPROM takes ~5ms (even if I2C writing already done)
  delay(5);
}

void EEPROM::writeByte(uint8_t address, uint8_t data){
  Wire.beginTransmission(I2C_EEPROM_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
  // Writing in I2C EEPROM takes ~5ms (even if I2C writing already done)
  delay(5);
}

void EEPROM::write_uint32(uint8_t address, uint32_t data ){
  ArrayToInteger tempVal;
  tempVal.integer = data;
  writeBuffer(address,tempVal.array, sizeof(tempVal) );
}

uint32_t EEPROM::read_uint32(uint8_t address){
  ArrayToInteger returnValue;
  readBuffer(address,returnValue.array,sizeof(returnValue) );
  return returnValue.integer;
}

void EEPROM::write_uint64(uint8_t address, uint64_t data ){
  ArrayToInteger64 tempVal;
  tempVal.integer = data;
  writeBuffer(address,tempVal.array, sizeof(tempVal) );
}

uint64_t EEPROM::read_uint64(uint8_t address){
  ArrayToInteger64 returnValue;
  readBuffer(address,returnValue.array,sizeof(returnValue) );
  return returnValue.integer;
}


void EEPROM::readBuffer(uint8_t address, uint8_t* data, uint8_t length){
  Wire.beginTransmission(I2C_EEPROM_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  uint8_t dataIndex = 0;
  Wire.requestFrom(I2C_EEPROM_ADDRESS, length);
  while( dataIndex < length ){
    if (Wire.available()) {
      data[dataIndex] = (uint8_t) Wire.read();
      dataIndex++;
    }
  }
}

uint8_t EEPROM::readByte(uint8_t address){
  uint8_t read_data = 0x00;
  Wire.beginTransmission(I2C_EEPROM_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  // Request 1 byte from device
  Wire.requestFrom(I2C_EEPROM_ADDRESS, 1);
  if (Wire.available()) {
    read_data = (uint8_t) Wire.read();
  }
  return read_data;
}
#endif
