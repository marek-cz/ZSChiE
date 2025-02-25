/**
* Interrupt UDRE
*/

#include <avr/interrupt.h>
#include <string.h>

volatile String str = "Test String\n\r";
volatile bool stringTxFlag = false;

ISR(USART_UDRE_vect)
{
  static uint8_t cnt = 0;

  if(cnt < str.length())
  {
    UDR0 = str[cnt++];
  }
  else
  {
    // disable USART Data Empty Interrupt
    UCSR0B ^= (1<<UDRIE0);
    stringTxFlag = true;
    cnt = 0;
  }
}

void USART_Init(uint16_t ubrr)
{
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0A |= (1<<U2X0);
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void uartEnableUDEInt(void)
{
  // enable USART Data Empty Interrupt
  UCSR0B |= (1<<UDRIE0);
}

void USART_Transmit(unsigned char data)
{
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)))
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

unsigned char USART_Receive(void)
{
  /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)))
  ;
  /* Get and return received data from buffer */
  return UDR0;
}

void uartSendBuffer(uint8_t* cstring_ptr)
{
  while( 0 != *cstring_ptr )
  {
    USART_Transmit(*cstring_ptr);
    cstring_ptr++; // arytmetyka wskaźnikow!
  }
}

void setup() {
  // put your setup code here, to run once:
  USART_Init(16); // 16MHz ->  115200
  sei();
  uartSendBuffer("Hallo World!\n\r");
  uartEnableUDEInt();
}

void loop() {
  // put your main code here, to run repeatedly:
  if( true == stringTxFlag )
  {
    stringTxFlag = false;
    delay(1000);
    uartEnableUDEInt();
  }
}
