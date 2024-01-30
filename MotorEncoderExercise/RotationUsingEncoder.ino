#define APin 3
#define BPin 2
#define M1A 9
#define M1B 10

volatile unsigned long ACount = 0;
volatile unsigned long BCount = 0;

void setup() {
    pinMode(APin, INPUT);
    pinMode(BPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(APin), ATick, RISING);
    attachInterrupt(digitalPinToInterrupt(BPin), BTick, RISING);
    analogWrite(M1A, 25);
}

void loop() {
}

void ATick(){
    ACount++;
    if (ACount % 948 == 0)
    {
        delay(500);
        analogWrite(M1A, analogRead(M1A) + analogRead(M1B)); //Swaps the 2 values with declaring a new variable.
        analogWrite(M1B, analogRead(M1A) - analogRead(M1B));
        analogWrite(M1A, analogRead(M1A) - analogRead(M1B));
    }
}
void BTick(){
    BCount++;
}