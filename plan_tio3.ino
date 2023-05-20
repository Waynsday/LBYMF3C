#include <Wire.h>
#include <Servo.h>
//receiver


Servo pump;

void setup()
{ 
  pinMode(2, INPUT);
  pinMode(A0, OUTPUT);//killswitch
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A1, HIGH);
  
  pump.attach(13);
  pump.write(0);
  Wire.begin(6);
  Wire.onReceive(receiveEvent);
  attachInterrupt(digitalPinToInterrupt(2), ISroutine, CHANGE);
  Serial.begin(9600);
}

int slide = 0;
int temp;
int wateringTime = 0;
int watering = 0;

void loop()
{
  if(watering == 1){
    Serial.println("Watering...");
    pump.write(90);
  	delay(wateringTime*1000);
    pump.write(0);
    watering = 0;
    Serial.println("Finished Watering...");
  } 
}

void ISroutine(){
  if(slide == 0){
    digitalWrite(A3, HIGH);
    Serial.println("Kill switch on");
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    slide = 1;
  } else {
    digitalWrite(A3, LOW);
    Serial.println("Kill switch off");
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    slide = 0;
  }
}


void receiveEvent(int num){
  while(Wire.available() > 1){
    temp = Wire.read();
    Serial.println(temp);
  }
  char c = Wire.read();
  
  if(slide == 0){
    if(c == '1'){
      //water plant
      Serial.print("Watering for ");
      wateringTime = timingComputation(temp);
      watering = 1;
      Serial.print(timingComputation(temp));
      Serial.println(" seconds");
      //water();
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
    } else {
      Serial.println("Resetting...");
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
    }
  }
  
}

float timingComputation(int temp){
	return 0.2* abs(temp -27) + 2;
}



