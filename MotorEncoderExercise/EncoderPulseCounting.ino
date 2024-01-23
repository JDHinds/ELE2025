#define APin 3
#define BPin 2

volatile unsigned long ACount = 0;
volatile unsigned long BCount = 0;

void setup(){
    pinMode(APin, INPUT);
    pinMode(BPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(APin), ATick, RISING);
    attachInterrupt(digitalPinToInterrupt(BPin), BTick, RISING);
    Serial.begin(9600);
}

void loop(){
    Serial.print("A: " + String(ACount));
    Serial.print(" B: " + String(BCount) + "\n");
    delay(200); //Delay to keep serial monitor readable
}

void ATick(){
    ACount++; //Increment ACount
}

void BTick(){
    BCount++; //Increment BCount
}
