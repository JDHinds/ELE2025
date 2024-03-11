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

bool tr = false;
bool tl = false;

bool ok = true;

char JsonOutput[192];

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
  Serial.begin(115200);
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
    delay(50);
  }

  else if(mode == 2)
  {
    ballPushing();
    sendTelemetry();
    delay(50);
  }    
  else
  {
    recieveInstructions();
  } 
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

      int motor1Speed = 0;
      int motor2Speed = 0;
      
      if(ACount1 < 13800)
      {
         motor1Speed = 220;
         motor2Speed = 220;
         
         data.connected = true;
         data.leftWheelSpeed = 220;
         data.rightWheelSpeed = 220;
         data.isLeftSensorDark = false;
         data.isRightSensorDark = false;
         data.distanceTravelled = ACount2;
      }

      else
      {
         motor1Speed = 90;
         motor2Speed = 90;

         data.connected = true;
         data.leftWheelSpeed = 90;
         data.rightWheelSpeed = 90;
         data.isLeftSensorDark = false;
         data.isRightSensorDark = false;
         data.distanceTravelled = ACount2;
      }
      
      
      
      //Both White
  
      analogWrite(M1A, 0); //Set M1A to ~10% PWM signal
      analogWrite(M1B, motor1Speed); //Set M1B to 0
  
      analogWrite(M2A, 0); //Set M2A to ~10% PWM signal
      analogWrite(M2B, motor2Speed); //Set M2B to 0
    }
  
    else if((leftSensor1Value == LOW && rightSensor1Value == HIGH)||(tl == true))
    {
      int motor1Speed = 70;
      int motor2Speed = 60;
      
      //Left Black and Right White
      
      analogWrite(M1A, 0);
      analogWrite(M1B, motor1Speed);
  
      analogWrite(M2A, motor2Speed);
      analogWrite(M2B, 0);

      data.connected = true;
      data.leftWheelSpeed = -70;
      data.rightWheelSpeed = 60;
      data.isLeftSensorDark = true;
      data.isRightSensorDark = false;
      data.distanceTravelled = ACount2;
    }
  
    else if((leftSensor1Value == HIGH && rightSensor1Value == LOW)||(tr == true))
    {
      int motor1Speed = 60;
      int motor2Speed = 70;
    
      //Left White and Right Black

     analogWrite(M1A, motor1Speed);
     analogWrite(M1B, 0);

     analogWrite(M2A, 0);
     analogWrite(M2B, motor2Speed);

      data.connected = true;
      data.leftWheelSpeed = 60;
      data.rightWheelSpeed = -70;
      data.isLeftSensorDark = false;
      data.isRightSensorDark = true;
      data.distanceTravelled = ACount2;
   }  
}

void ballPushing()
{
    
  if(ACount1 < 1700)
  {
      int motor1Speed = 70;
      int motor2Speed = 70;
  
      analogWrite(M1A, 0);
      analogWrite(M1B, motor1Speed);
  
      analogWrite(M2A, 0);
      analogWrite(M2B, motor2Speed);

      data.connected = true;
      data.leftWheelSpeed = 70;
      data.rightWheelSpeed = 70;
      data.isLeftSensorDark = false;
      data.isRightSensorDark = false;
      data.distanceTravelled = ACount2;
  }

  else if(ACount1 < 3000)
  {
      int motor1Speed = 100;
      int motor2Speed = 100;
  
      analogWrite(M1A, motor1Speed);
      analogWrite(M1B, 0);
  
      analogWrite(M2A, motor2Speed);
      analogWrite(M2B, 0);
      
      data.connected = true;
      data.leftWheelSpeed = 100;
      data.rightWheelSpeed = 100;
      data.isLeftSensorDark = false;
      data.isRightSensorDark = false;
      data.distanceTravelled = ACount2;
  }

  else
  {
      analogWrite(M1A, 0);
      analogWrite(M1B, 0);
  
      analogWrite(M2A, 0);
      analogWrite(M2B, 0);

      data.connected = true;
      data.leftWheelSpeed = 0;
      data.rightWheelSpeed = 0;
      data.isLeftSensorDark = false;
      data.isRightSensorDark = false;
      data.distanceTravelled = ACount2;
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
  delay(25);
  Serial.print(output.substring(64,128));
  delay(25);
  Serial.println(output.substring(128,192));
}

void recieveInstructions()
{
  Serial.println("{manual}");
  String instructions;
  instructions = Serial.readStringUntil('\n');
  if (instructions == "{manual}")
  { }
  else if (instructions == "{auto}")
  { mode = 1; }
  else
  {
    deserialiseData(instructions);

    analogWrite(M1A, abs(constrain(data.rightWheelSpeed, -255, 0)));
    analogWrite(M1B, abs(constrain(data.rightWheelSpeed, 0, 255)));
  
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