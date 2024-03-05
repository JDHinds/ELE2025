#include <ArduinoJson.h>

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
  attachInterrupt(digitalPinToInterrupt(IN_RIGHT), tright, HIGH);
  attachInterrupt(digitalPinToInterrupt(IN_LEFT), tleft, HIGH);
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

  /*
  while(Auto)
  {
    sendTelemetry();
    delay (300);
  }
  while(!Auto)
  {
    recieveInstructions();
  }
  */
    
}


void lineFollowing()
{
    bool value_D01 = digitalRead(IN_D01);
    bool value_D02 = digitalRead(IN_D02);    
    
    if(value_D01 == LOW && value_D02 == HIGH)
    {
    //Left Black and Right White
      
      analogWrite(M1A, 0);
      analogWrite(M1B, 60);
  
      analogWrite(M2A, 20);
      analogWrite(M2B, 0);
    }
  
    else if(value_D01 == HIGH && value_D02 == LOW)
    {
    //Left White and Right Black

     analogWrite(M1A, 20);
     analogWrite(M1B, 0);

     analogWrite(M2A, 0);
     analogWrite(M2B, 60);
   }

   else
   {
   //Both White
  
     analogWrite(M1A, 0);
     analogWrite(M1B, 100);
  
     analogWrite(M2A, 0);
     analogWrite(M2B, 100);
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
  }
}

void tleft()
{
  analogWrite(M1A, 0);
  analogWrite(M1B, 60);
  
  analogWrite(M2A, 60);
  analogWrite(M2B, 0);
  /*while(digitalRead(IN_LEFT) || digitalRead(IN_D02))
  {
    
  }
  analogWrite(M1A, 0);
  analogWrite(M1B, 100);
  
  analogWrite(M2A, 0);
  analogWrite(M2B, 100);*/
}

void tright()
{  
  analogWrite(M1A, 60);
  analogWrite(M1B, 0);
  
  analogWrite(M2A, 0);
  analogWrite(M2B, 60);
  /*while(digitalRead(IN_RIGHT) || digitalRead(IN_D01))
  {
    
  }
  analogWrite(M1A, 0);
  analogWrite(M1B, 100);
  
  analogWrite(M2A, 0);
  analogWrite(M2B, 100);*/
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