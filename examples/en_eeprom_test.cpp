#include "Arduino.h"
#include <en_eeprom.h>

EEPROM eeprom;

void setup(){
  SerialUSB.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  eeprom.init();
  delay(2000);
  SerialUSB.println("\nI2C eeprom test. Reboot\n");
}


void loop(){
  digitalWrite(LED_BUILTIN,HIGH);
  SerialUSB.println("Reboot counter:");
  uint8_t j;
  j = eeprom.readByte(1);
  SerialUSB.print(" Location 1:");
  SerialUSB.println(j);
  j++;

  eeprom.writeByte(1, j);
  delay(1000);
  digitalWrite(LED_BUILTIN,LOW);
  delay(5000);
}
