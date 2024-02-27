void setup()
{
    Serial.begin(9600);
}

void loop(){
    Serial.print("Arduino Signalling");
    delay(200); //Delay to keep serial monitor readable
}

String telemetryString()
{}