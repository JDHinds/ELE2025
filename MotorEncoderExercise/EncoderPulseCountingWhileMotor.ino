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
    Serial.begin(9600);
    analogWrite(M1A, 25);
}

void loop() {
    Serial.print("A: " + String(ACount));
    Serial.print(" B: " + String(BCount) + "\n");
}

void ATick(){
    ACount++; //Increment ACount
}
void BTick(){
    BCount++; //Increment BCount
}
