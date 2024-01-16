#define M1A 3 //M1A is connected to Arduino pin 3
#define M1B 5 //M1B is connected to Arduino pin 5

void setup() {
    analogWrite(M1B, 0);
    int i = 0;
    for (i < 256; i++;)
    {
        analogWrite(M1A, i);
        delay(200);
    }
    for (i > -1; i--;)
    {
        analogWrite(M1A, i);
        delay(200);
    }
}
void loop() {}
