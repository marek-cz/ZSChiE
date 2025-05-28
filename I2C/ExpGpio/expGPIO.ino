#include "expGPIO.h"

void setup() {
  // put your setup code here, to run once:
  ExpGpio exp = ExpGpio();
  exp.writeReg(0x00, 0xFE);
  exp.writeReg(0x09,0x01);
}

void loop() {
  // put your main code here, to run repeatedly:

}
