#ifndef EXPGPIO_H
#define EXPGPIO_H

#include <Arduino.h>
#include <Wire.h>

class ExpGpio
{
  public:
  ExpGpio(void);
  void writeReg(uint8_t regAddr, uint8_t value);
  uint8_t readReg(uint8_t regAddr);

  private:
  const uint8_t addrI2C_ = 0x40 >> 1;
};

#endif