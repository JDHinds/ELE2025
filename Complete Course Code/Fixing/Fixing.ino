#define M1A 2 //M1A is connected to Arduino pin 2
#define M1B 3 //M1B is connected to Arduio pin 3
#define M2A 4 //M1A is connected to Arduino pin 4
#define M2B 5 //M1B is connected to Arduio pin 5

#define IN_D01 6
#define IN_D02 7

bool courseComplete = false;

void setup() 
{
  Serial.begin(9600);
  
  pinMode (M1A, INPUT);
  pinMode (M1B, INPUT);
  
  pinMode (M2A, INPUT);
  pinMode (M2B, INPUT);  
}
void loop() 
{  
  int value_D01 = digitalRead(IN_D01);
  int value_D02 = digitalRead(IN_D02);

  Serial.println(value_D01);
  Serial.println(value_D02);

  if(value_D01 == LOW && value_D02 == LOW)
  {
    int motor1Speed = 100;
    int motor2Speed = 100;
    
    Serial.println("Both White");

    analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
    analogWrite(M1B, motor1Speed); //Set M1B to 0

    analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
    analogWrite(M2B, motor2Speed); //Set M2B to 0
  }

  else if(value_D01 == HIGH && value_D02 == LOW)
  {
    int motor1Speed = 50;
    int motor2Speed = 30;
    
    Serial.println("Left Black and Right White");
    
    analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
    analogWrite(M1B, motor1Speed); //Set M1B to 0

    analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
    analogWrite(M2B, 0); //Set M1B to 0
  }
  
  else if(value_D01 == LOW && value_D02 == HIGH)
  {
    int motor1Speed = 30;
    int motor2Speed = 50;
    
    Serial.println("Left White and Right Black");

    analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
    analogWrite(M1B, 0); //Set M1B to 0

    analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
    analogWrite(M2B, motor2Speed); //Set M2B to 0
  }

  else if(value_D01 == HIGH && value_D02 == HIGH)
  {    
    Serial.println("Both Black");

    courseComplete = true;    
  }

  else if(courseComplete == true)
  {
    int motor1Speed = 0;
    int motor2Speed = 0;
    
    analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
    analogWrite(M1B, 0); //Set M1B to 0

    analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
    analogWrite(M2B, 0); //Set M2B to 0
  }
}
