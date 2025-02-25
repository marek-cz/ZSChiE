/**
Single conversion example
conversion triggered by serial port
ADC pin --> PC5
*/

void initADC(void)
{
  // PC5 as input
  DDRC &= ~(1 << PC5);
  // select Vref source - AVCC
  ADMUX = (1<<REFS0); 
  // select adjustment - right adjustment
  ADMUX &= ~(1<<ADLAR);
  // select analog input - ADC5
  ADMUX |= (1<<MUX2) | (1<<MUX0);
  // select prescaler. By default, the successive approximation circuitry requires
  // an input clock frequency between 50kHz and 200kHz to get maximum resolution
  // division factor 128 --> adc clock 125kHz
  ADCSRA = (1<< ADPS2) | (1<< ADPS1) | (1<< ADPS0);
  // enable ADC
  ADCSRA |= (1<<ADEN);
}

void waitForConversionEnd(void)
{
  while (ADCSRA & (1 << ADSC)); // Czekaj na zakończenie konwersji
}

void startConversion(void)
{
  ADCSRA |= (1 << ADSC); 
}

uint16_t getConversionValue(void)
{
  return ADC;
}

void setup() {
  // put your setup code here, to run once:
  initADC();
  Serial.begin(115200);
}

void loop() {
  uint16_t adcRes;
  // put your main code here, to run repeatedly:
  if( 0 != Serial.available() )
  {
    Serial.readString();
    startConversion();
    waitForConversionEnd();
    adcRes = getConversionValue();
    Serial.print("Conversion Value = ");
    Serial.println(adcRes);
  }
}
