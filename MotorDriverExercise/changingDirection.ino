#define M1A 3 //M1A is connected to Arduino pin 3
#define M1B 5 //M1B is connected to Arduio pin 5

void setup() {
    analogWrite(M1B, 0);
    }

void loop() {
analogWrite(M1A, 51); //Set M1A to ~10% PWM signal
delay(5000);
analogWrite(M1A, 0);
delay(500);
analogWrite(M1B, 51);
delay(5000);
analogWrite(M1B, 0);
delay(5000);
}
