/**
Przyklad realizacji nadajnika alfabetu Morse'a 
za pomocą buzzera

Buzzer: H -(Delay dot/Dash)-> L

*/
const int buzzerPin = 5;
const int dotDelay = 200;
const int dashDelay = 3 * dotDelay;


char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* digits[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void setup()                 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  char ch;
  if (Serial.available() > 0)
  {
    ch = Serial.read();
    //todo sendChar Morse
  }
}



