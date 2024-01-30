#define APin 3
#define BPin 2
#define M1A 9
#define M1B 10

volatile unsigned long ACount = 1000;
volatile unsigned long BCount = 0;

void setup() {
    pinMode(APin, INPUT);
    pinMode(BPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(APin), ATick, RISING);
    attachInterrupt(digitalPinToInterrupt(BPin), BTick, RISING);
    analogWrite(M1A, 25);
    Serial.begin(9600);
}

void loop() 
{
  Serial.println(ACount);
}

void ATick(){
    ACount++;
    if (ACount % 2000 == 0)
    {
        analogWrite(M1A, 0);
        delay(500);
        analogWrite(M1B, 25);
    }
    else if (ACount % 1000 == 0)
    {
      analogWrite(M1B, 0);
        delay(500);
        analogWrite(M1A, 25);
      }
}
void BTick(){
    BCount++;
}
