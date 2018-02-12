#include "en_eeprom.h"
#ifndef en_eeprom_h
#define en_eeprom_h

TwoWire WireSercom3(&sercom3, 20, 21);

union ArrayToInteger {
 uint8_t array[4];
 uint32_t integer;
};

union ArrayToInteger64 {
 uint8_t array[8];
 uint32_t integer;
};

void eepromInit(){
  WireSercom3.begin();
  WireSercom3.setClock(10000);
}

void eepromWriteBuffer(uint8_t address, uint8_t data[], uint8_t length ){
  // Todo: blocking should only write 8 bytes at a time....
  // See page 8 of http://ww1.microchip.com/downloads/en/DeviceDoc/21709c.pdf
  WireSercom3.beginTransmission(I2C_EEPROM_ADDRESS);
  WireSercom3.write(address);
  uint8_t dataIndex = 0;
  while( dataIndex < length ){
    WireSercom3.write(data[dataIndex]);
    dataIndex++;
  }
  WireSercom3.endTransmission();
  // Writing in I2C EEPROM takes ~5ms (even if I2C writing already done)
  delay(5);
}

void eepromWriteByte(uint8_t address, uint8_t data){
  WireSercom3.beginTransmission(I2C_EEPROM_ADDRESS);
  WireSercom3.write(address);
  WireSercom3.write(data);
  WireSercom3.endTransmission();
  // Writing in I2C EEPROM takes ~5ms (even if I2C writing already done)
  delay(5);
}

void eepromWrite_uint32(uint8_t address, uint32_t data ){
  ArrayToInteger tempVal;
  tempVal.integer = data;
  eepromWriteBuffer(address,tempVal.array, sizeof(tempVal) );
}

uint32_t eepromRead_uint32(uint8_t address){
  ArrayToInteger returnValue;
  eepromReadBuffer(address,returnValue.array,sizeof(returnValue) );
  return returnValue.integer;
}

void eepromWrite_uint64(uint8_t address, uint64_t data ){
  ArrayToInteger64 tempVal;
  tempVal.integer = data;
  eepromWriteBuffer(address,tempVal.array, sizeof(tempVal) );
}

uint64_t eepromRead_uint64(uint8_t address){
  ArrayToInteger64 returnValue;
  eepromReadBuffer(address,returnValue.array,sizeof(returnValue) );
  return returnValue.integer;
}


void eepromReadBuffer(uint8_t address, uint8_t* data, uint8_t length){
  WireSercom3.beginTransmission(I2C_EEPROM_ADDRESS);
  WireSercom3.write(address);
  WireSercom3.endTransmission();

  uint8_t dataIndex = 0;
  WireSercom3.requestFrom(I2C_EEPROM_ADDRESS, length);
  while( dataIndex < length ){
    if (WireSercom3.available()) {
      data[dataIndex] = (uint8_t) WireSercom3.read();
      dataIndex++;
    }
  }
}

uint8_t eepromReadByte(uint8_t address){
  uint8_t read_data = 0x00;
  WireSercom3.beginTransmission(I2C_EEPROM_ADDRESS);
  WireSercom3.write(address);
  WireSercom3.endTransmission();

  // Request 1 byte from device
  WireSercom3.requestFrom(I2C_EEPROM_ADDRESS, 1);
  if (WireSercom3.available()) {
    read_data = (uint8_t) WireSercom3.read();
  }
  return read_data;
}
#endif
