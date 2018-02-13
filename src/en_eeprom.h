#include "Arduino.h"
#include <Wire.h>
// http://ww1.microchip.com/downloads/en/DeviceDoc/21709c.pdf
// Define 24LC02 I2C addressing
#define I2C_EEPROM_ADDRESS 0x50


class EEPROM {
  public:

    void init();

    void writeByte(uint8_t address, uint8_t data);
    uint8_t readByte(uint8_t address);

    void write_uint32(uint8_t address, uint32_t data );
    uint32_t read_uint32(uint8_t address);

    void write_uint64(uint8_t address, uint64_t data );
    uint64_t read_uint64(uint8_t address);

    void writeBuffer(uint8_t address, uint8_t data[], uint8_t length);
    void readBuffer(uint8_t address, uint8_t * data, uint8_t length);
  };
