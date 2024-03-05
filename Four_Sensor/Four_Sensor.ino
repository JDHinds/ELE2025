#define M1A 10 //M1A is connected to Arduino pin 2
#define M1B 11 //M1B is connected to Arduio pin 3
#define M2A 4 //M1A is connected to Arduino pin 4
#define M2B 5 //M1B is connected to Arduio pin 5

#define IN_D01 6
#define IN_D02 7
#define IN_RIGHT 2
#define IN_LEFT 3

#define APin1 18
#define BPin1 19
#define APin2 20
#define BPin2 21

volatile unsigned long ACount1 = 0;
volatile unsigned long BCount1 = 0;
volatile unsigned long ACount2 = 0;
volatile unsigned long BCount2 = 0;

//attachInterrupt(digitalPinToInterrupt(APin1), ATick, RISING);

bool tr = false;
bool tl = false;

bool ok = true;

void setup() 
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(IN_RIGHT), tright, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IN_LEFT), tleft, CHANGE);
  pinMode (M1A, OUTPUT);
  pinMode (M1B, OUTPUT);
  
  pinMode (M2A, OUTPUT);
  pinMode (M2B, OUTPUT);  

  pinMode(APin1, INPUT);
  pinMode(BPin1, INPUT);
  pinMode(APin2, INPUT);
  pinMode(BPin2, INPUT);

  attachInterrupt(digitalPinToInterrupt(APin1), ATick1, RISING);
  attachInterrupt(digitalPinToInterrupt(BPin1), BTick1, RISING);
  attachInterrupt(digitalPinToInterrupt(APin2), ATick2, RISING);
  attachInterrupt(digitalPinToInterrupt(BPin2), BTick2, RISING);
}

void loop() 
{  

  lineFollowing();

  //ballPushing();
    
}


void lineFollowing()
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
  
    if((value_D01 == LOW  && value_D02 == LOW)&& (tr == false && tl == false))
    {
      int motor1Speed = 150;
      int motor2Speed = 150;
      
      //Both White
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0
    }
  
    else if((value_D01 == LOW && value_D02 == HIGH)||(tl == true))
    {
      int motor1Speed = 60;
      int motor2Speed = 20;
      
      //Left Black and Right White
      
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
      analogWrite(M2B, 0); //Set M1B to 0
    }
  
    else if((value_D01 == HIGH && value_D02 == LOW)||(tr == true))
    {
      int motor1Speed = 20;
      int motor2Speed = 60;
    
      //Left White and Right Black

     analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
     analogWrite(M1B, 0); //Set M1B to 0

     analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
     analogWrite(M2B, motor2Speed); //Set M2B to 0
   }

   else if(!value_D01 && !value_D02)
   {    
     //Both Black  
   }    
}

void ballPushing()
{

  Serial.println(ACount1);
    
  if(ACount1 < 1500)
  {
      int motor1Speed = 150;
      int motor2Speed = 150;
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0        
  }

  else if(ACount1 < 3000)
  {
      int motor1Speed = 150;
      int motor2Speed = 150;
  
      analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
      analogWrite(M1B, 0); //Set M1B to 0
  
      analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
      analogWrite(M2B, 0); //Set M2B to 0
  }

  else
  {
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, 0); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
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

void ATick1()
{
    ACount1++;
}
void BTick1()
{
    BCount1++;
}

void ATick2()
{
    ACount2++;
}
void BTick2()
{
    BCount2++;
} 
