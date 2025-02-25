/**
ADC conversion triggered by INT0
ADC pin --> PC5
Button pin PD2
*/

volatile bool conversionCompleteFlag = false;

ISR(INT0_vect)
{
  //empty -- just to clear int flag
}

ISR(ADC_vect)
{
  //conversion complete
  conversionCompleteFlag = true;
}

void initInt0(void)
{
  EICRA |= (1<<ISC01) | (1<<ISC00); // rising edge detection
  EIMSK |= (1<<INT0); // enable INT0 interrupt
}

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

  // Select Auto Trigger Source
  ADCSRB |= (1<<ADTS1); //External interrupt request 0
  // enable auto triger mode
  ADCSRA |= (1<<ADATE);

  // enable ADC Interrupt
  ADCSRA |= (1<<ADIE);

  // disable Digital input buffer
  DIDR0 |= (1<<ADC5D);
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
  initInt0();
  initADC();
  sei();
  Serial.begin(115200);
}

void loop() {
  uint16_t adcRes;
  // put your main code here, to run repeatedly:
  if(true == conversionCompleteFlag)
  {
    conversionCompleteFlag = false;
    adcRes = getConversionValue();
    Serial.print("Conversion Value = ");
    Serial.println(adcRes);
  }
}
