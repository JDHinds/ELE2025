#define M1A 3 //M1A is connected to Arduino pin 3
#define M1B 5 //M1B is connected to Arduio pin 5
void setup() {
analogWrite(M1A, 25); //Set M1A to ~10% PWM signal
analogWrite(M1B, 0); //Set M1B to 0
}
void loop() {
}
