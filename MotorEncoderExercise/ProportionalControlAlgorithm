#define M1A 9
#define EncoderA 3

volatile unsigned long ACounter = 0;

int maxPWM = 100;
int targetTicks = 5;
int timePeriod = 10;
int proportionalGain = maxPWM/targetTicks;
int output;
int error;

void setup() {
  pinMode(EncoderA, INPUT);
  attachInterrupt(digitalPinToInterrupt(EncoderA), ATick, RISING);
}

void loop() {
  unsigned long startingTicks = ACounter;
  delay(timePeriod);
  unsigned long tickDifference = ACounter - startingTicks;
  error = targetTicks - tickDifference;
  output = error * proportionalGain;
  PWMMotor(output);
}

void PWMMotor(int PWMValue){
  int writeValue;
  if(PWMValue > 0){
    writeValue = 255/100 * PWMValue;
  }
  else{writeValue = 0;}
  analogWrite(M1A, writeValue);
}

void ATick(){
  ACounter++;
}
