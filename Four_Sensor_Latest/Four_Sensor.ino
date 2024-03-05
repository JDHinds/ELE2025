#define M1A 10 //M1A is connected to Arduino pin 2
#define M1B 11 //M1B is connected to Arduio pin 3
#define M2A 4 //M1A is connected to Arduino pin 4
#define M2B 5 //M1B is connected to Arduio pin 5

#define IN_D01 7
#define IN_D02 6


#define IN_RIGHT 3
#define IN_LEFT 2

//attachInterrupt(digitalPinToInterrupt(APin1), ATick, RISING);

bool courseComplete = false;
bool tr = false;
bool tl = false;

void setup() 
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(IN_RIGHT), tright, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IN_LEFT), tleft, CHANGE);
  pinMode (M1A, OUTPUT);
  pinMode (M1B, OUTPUT);
  
  pinMode (M2A, OUTPUT);
  pinMode (M2B, OUTPUT);  
}

void loop() 
{  
    bool value_D01 = digitalRead(IN_D01);
    bool value_D02 = digitalRead(IN_D02);    
  
    if(value_D01)
    {
      tr=false;
    }
    if(value_D02)
    {
      tl=false;
    }
  
    if(courseComplete != true)
    {
      if((!value_D01  && !value_D02 )&&!(tr||tl))
    {
      int motor1Speed = 150;
      int motor2Speed = 150;
      
      //Both White
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0
    }
  
    else if((!value_D01  && value_D02)||(tl))
    {
      int motor1Speed = 100;
      int motor2Speed = 50;
      
      //Left Black and Right White
      
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
      analogWrite(M2B, 0); //Set M1B to 0
    }
  
    else if((value_D01  && !value_D02 )||(tr))
    {
      int motor1Speed = 50;
      int motor2Speed = 100;
    
      //Left White and Right Black

     analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
     analogWrite(M1B, 0); //Set M1B to 0

     analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
     analogWrite(M2B, motor2Speed); //Set M2B to 0
   }

   else if(!value_D01 && !value_D02)
   {    
     //Both Black

     courseComplete = true;    
   }    
  }  

  else if(courseComplete == true)
  {

    Serial.println(courseComplete);

    int motor1Speed = 0;
    int motor2Speed = 0;
    
    analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
    analogWrite(M1B, 0); //Set M1B to 0

    analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
    analogWrite(M2B, 0); //Set M2B to 0
  }
}

void tleft()
{
    tl=true;
    tr=false;  
}

void tright()
{  
    tr=true;  
    tl=false;  
}
