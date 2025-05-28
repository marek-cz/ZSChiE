
#include "expGPIO.h"

ExpGpio::ExpGpio()
{
  Wire.begin();
}

void ExpGpio::writeReg(uint8_t regAddr, uint8_t value)
{
  Wire.beginTransmission(addrI2C_);
  Wire.write(regAddr);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t ExpGpio::readReg(uint8_t regAddr)
{
  Wire.beginTransmission(addrI2C_);
  Wire.write(regAddr);
  Wire.endTransmission();
  Wire.requestFrom((int)addrI2C_, 1); // request 1 byte
  while(Wire.available() == 0);
  return Wire.read();
}