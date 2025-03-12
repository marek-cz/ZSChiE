/**
  Example of drawing chars and strings
*/

#include <SPI.h>
#include "PCD8544.h"
#include "font5x7.h"

 // all pins in PORTB
const uint8_t resetPin = (1<<0);
const uint8_t nChipSelect = (1<<2);
const uint8_t nCmdData = (1<<1);
const uint8_t sclk = (1<<5);
const uint8_t mosi = (1<<3);

void initGpio(void);
void resetPCD8544(void);
void sendCmd(uint8_t cmd);
void sendData(uint8_t byte);
void clearScreen(void);
void setAddr(uint8_t x, uint8_t y);
void initDisplay(void);
void drawChar(uint8_t c);
void drawString(uint8_t* str);


void setup() {
  // put your setup code here, to run once:
  initGpio();
  delay(5);
  resetPCD8544();
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  Serial.begin(115200);

  initDisplay();
  setAddr(10, 2);
  drawString("KSEMWETIPG");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void resetPCD8544(void)
{
  PORTB &= ~(resetPin);
  delay(100);
  PORTB |= resetPin;
}

void initGpio(void)
{
  DDRB |= resetPin | nChipSelect | nCmdData | sclk |mosi;
  PORTB |= nChipSelect | resetPin;
}

void sendCmd(uint8_t cmd)
{
  PORTB &= ~(nCmdData | nChipSelect);
  SPI.transfer(cmd);
  PORTB |= nChipSelect;
}

void sendData(uint8_t byte)
{
  PORTB &= ~ (nChipSelect);
  PORTB |= nCmdData;
  SPI.transfer(byte);
  PORTB |= nChipSelect;
}

void clearScreen(void)
{
  for(uint16_t i = 0; i < 504; i++)
  {
    sendData(0x00);
  }
}

void setAddr(uint8_t x, uint8_t y)
{
  sendCmd(setAddrY | y);
  sendCmd(setAddrX | x); 
}

void initDisplay(void)
{
  sendCmd(0x21); // function set H = 1
  sendCmd(0x13); // set Bias 1:48
  sendCmd(0x90 | 50); // set Vop
  sendCmd(0x20); // function set H = 0
  sendCmd(0x0C); // display normal mode
  //set addr
  setAddr(0, 0);
  clearScreen();
  setAddr(0, 0);
}

void drawChar(uint8_t c)
{
  uint8_t dataByte;

  for(uint8_t i = 0; i < numberOfBytesInChar;i++)
  {
    dataByte = font5x7[(c*numberOfBytesInChar)+i];
    sendData(dataByte);
    Serial.println(dataByte);
  }
}

void drawString(uint8_t* str)
{
  while( 0 != (*str))
  {
    drawChar(*str);
    sendData(0x00); // space between letters
    str++;
  }
}