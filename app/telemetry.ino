#include <ArduinoJson.h>

#define M1A 10 //M1A is connected to Arduino pin 2
#define M1B 11 //M1B is connected to Arduio pin 3
#define M2A 4 //M1A is connected to Arduino pin 4
#define M2B 5 //M1B is connected to Arduio pin 5

#define rightSesnor1 6
#define leftSesnor1 7
#define rightSesnor2 2
#define leftSesnor2 3

#define APin1 18
#define BPin1 19
#define APin2 20
#define BPin2 21

volatile unsigned long ACount1 = 0;
volatile unsigned long BCount1 = 0;
volatile unsigned long ACount2 = 0;
volatile unsigned long BCount2 = 0;

int mode = 0;

//attachInterrupt(digitalPinToInterrupt(APin1), ATick, RISING);

bool tr = false;
bool tl = false;

bool ok = true;

char JsonOutput[192];
bool Auto;

class TelemetryData
{
  public:
    bool connected;
    int leftWheelSpeed;
    int rightWheelSpeed;
    bool isLeftSensorDark;
    bool isRightSensorDark;
    int distanceTravelled; 
};

TelemetryData data;

void setup() 
{
  Serial.begin(2000000);
  Serial.setTimeout(1000);
  attachInterrupt(digitalPinToInterrupt(rightSesnor2), tright, RISING);
  attachInterrupt(digitalPinToInterrupt(leftSesnor2), tleft, RISING);
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
  if(mode == 1)
  {
    lineFollowing();
    sendTelemetry();
  }

  else if(mode == 2)
  {
    ballPushing();
  }    
  else
  {
    recieveInstructions();
  }
  /*
  while(Auto)
  {
    sendTelemetry();
    delay (300);
  }
  while(!Auto)
  {
    
  }
  */
    
}


void lineFollowing()
{
    bool leftSensor1Value = digitalRead(leftSesnor1);
    bool rightSensor1Value = digitalRead(rightSesnor1); 


   if(leftSensor1Value == HIGH && rightSensor1Value == HIGH)
   {    
     mode = 2;  
     ACount1 = 0;
   }    
  
    if(leftSensor1Value)
    {
      tl=false;
    }
    if(rightSensor1Value)
    {
      tr=false;
    }
  
    if((leftSensor1Value == LOW  && rightSensor1Value == LOW) && (tr == false && tl == false))
    {
      int motor1Speed = 190;
      int motor2Speed = 190;
      
      //Both White
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0
    }
  
    else if((leftSensor1Value == LOW && rightSensor1Value == HIGH)||(tl == true))
    {
      int motor1Speed = 80;
      int motor2Speed = 40;
      
      //Left Black and Right White
      
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, motor2Speed); //Set M2A to ~10% PWM signal
      analogWrite(M2B, 0); //Set M1B to 0
    }
  
    else if((leftSensor1Value == HIGH && rightSensor1Value == LOW)||(tr == true))
    {
      int motor1Speed = 40;
      int motor2Speed = 80;
    
      //Left White and Right Black

     analogWrite(M1A, motor1Speed); //Set M1A to ~10% PWM signal
     analogWrite(M1B, 0); //Set M1B to 0

     analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
     analogWrite(M2B, motor2Speed); //Set M2B to 0
   }  
}

void ballPushing()
{
    
  if(ACount1 < 1600)
  {
      int motor1Speed = 60;
      int motor2Speed = 60;
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0        
  }

  else if(ACount1 < 3000)
  {
      int motor1Speed = 50;
      int motor2Speed = 50;
  
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

void serialiseData(TelemetryData data)
{
  JsonDocument doc;
  doc["connected"] = true;
  doc["leftWheelSpeed"] = data.leftWheelSpeed;
  doc["rightWheelSpeed"] = data.rightWheelSpeed;
  doc["isLeftSensorDark"] = data.isLeftSensorDark;
  doc["isRightSensorDark"] = data.isRightSensorDark;
  doc["distanceTravelled"] = data.distanceTravelled;

  serializeJson(doc, JsonOutput);
}

void deserialiseData(String input)
{
  JsonDocument doc;
  deserializeJson(doc, input);

  data.connected = doc["connected"];
  data.leftWheelSpeed = doc["leftWheelSpeed"];
  data.rightWheelSpeed = doc["rightWheelSpeed"];
  data.isLeftSensorDark = doc["isLeftSensorDark"];
  data.isRightSensorDark = doc["isRightSensorDark"];
  data.distanceTravelled = doc["distanceTravelled"];
}

void sendTelemetry()
{
  serialiseData(data);
  String output = String(JsonOutput);
  Serial.print(output.substring(0,64));
  delay(50);
  Serial.print(output.substring(64,128));
  delay(50);
  Serial.println(output.substring(128,192));
}

void recieveInstructions()
{
  Serial.println("{manual}");
  String instructions;
  //while (instructions == NULL)
  //{  }
  instructions = Serial.readStringUntil('\n');
  if (instructions == "{manual}")
  { }
  else if (instructions == "{auto}")
  { Auto = true; }
  else
  {
    deserialiseData(instructions);

    analogWrite(M1A, abs(constrain(data.rightWheelSpeed, -255, 0)));
    analogWrite(M1B, abs(constrain(data.leftWheelSpeed, 0, 255)));
  
    analogWrite(M2A, abs(constrain(data.leftWheelSpeed, -255, 0)));
    analogWrite(M2B, abs(constrain(data.leftWheelSpeed, 0, 255)));
  }
}

void tleft()
{
  tl = true;
  tr = false;
    
}

void tright()
{  
    tr = true;
    tl = false;
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