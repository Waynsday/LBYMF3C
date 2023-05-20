#include <Wire.h>
//sender

void printNum(int a)
{
  
  if(a < 100 && a > 0){
    int o = a%10;
    int t = (a-o)/10;
    //ones printing
    switch(o){
      case 0:
      	digitalWrite(4, LOW);
      	digitalWrite(5, LOW);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
      	break;
      case 1:
      	digitalWrite(4, HIGH);
      	digitalWrite(5, LOW);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
      	break;
      case 2:
      	digitalWrite(4, LOW);
      	digitalWrite(5, HIGH);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
      	break;
      case 3:
      	digitalWrite(4, HIGH);
      	digitalWrite(5, HIGH);
      	digitalWrite(6, LOW);
      	digitalWrite(7, LOW);
      	break;
      case 4:
      	digitalWrite(4, LOW);
      	digitalWrite(5, LOW);
      	digitalWrite(6, HIGH);
      	digitalWrite(7, LOW);
      	break;
      case 5:
      	digitalWrite(4, HIGH);
      	digitalWrite(5, LOW);
      	digitalWrite(6, HIGH);
      	digitalWrite(7, LOW);
      	break;
      case 6:
      	digitalWrite(4, LOW);
      	digitalWrite(5, HIGH);
      	digitalWrite(6, HIGH);
      	digitalWrite(7, LOW);
      	break;
      case 7:
      	digitalWrite(4, HIGH);
      	digitalWrite(5, HIGH);
      	digitalWrite(6, HIGH);
      	digitalWrite(7, LOW);
      	break;
      case 8:
      	digitalWrite(4, LOW);
      	digitalWrite(5, LOW);
      	digitalWrite(6, LOW);
      	digitalWrite(7, HIGH);
      	break;
      case 9:
      	digitalWrite(4, HIGH);
      	digitalWrite(5, LOW);
      	digitalWrite(6, LOW);
      	digitalWrite(7, HIGH);
      	break;
    }
    //tens printing
    switch(t){
      case 0:
      	digitalWrite(8, LOW);
      	digitalWrite(9, LOW);
      	digitalWrite(10, LOW);
      	digitalWrite(11, LOW);
      	break;
      case 1:
      	digitalWrite(8, HIGH);
      	digitalWrite(9, LOW);
      	digitalWrite(10, LOW);
      	digitalWrite(11, LOW);
      	break;
      case 2:
      	digitalWrite(8, LOW);
      	digitalWrite(9, HIGH);
      	digitalWrite(10, LOW);
      	digitalWrite(11, LOW);
      	break;
      case 3:
      	digitalWrite(8, HIGH);
      	digitalWrite(9, HIGH);
      	digitalWrite(10, LOW);
      	digitalWrite(11, LOW);
      	break;
      case 4:
      	digitalWrite(8, LOW);
      	digitalWrite(9, LOW);
      	digitalWrite(10, HIGH);
      	digitalWrite(11, LOW);
      	break;
      case 5:
      	digitalWrite(8, HIGH);
      	digitalWrite(9, LOW);
      	digitalWrite(10, HIGH);
      	digitalWrite(11, LOW);
      	break;
      case 6:
      	digitalWrite(8, LOW);
      	digitalWrite(9, HIGH);
      	digitalWrite(10, HIGH);
      	digitalWrite(11, LOW);
      	break;
      case 7:
      	digitalWrite(8, HIGH);
      	digitalWrite(9, HIGH);
      	digitalWrite(10, HIGH);
      	digitalWrite(11, LOW);
      	break;
      case 8:
      	digitalWrite(8, LOW);
      	digitalWrite(9, LOW);
      	digitalWrite(10, LOW);
      	digitalWrite(11, HIGH);
      	break;
      case 9:
      	digitalWrite(8, HIGH);
      	digitalWrite(9, LOW);
      	digitalWrite(10, LOW);
      	digitalWrite(11, HIGH);
      	break;
    }
  }
}


void setup()
{
  //tens digit
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  //ones digit
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  //temp
  pinMode(A0, INPUT);
  
  //light
  pinMode(A1, INPUT);
  
  Wire.begin();
  Serial.begin(9600);
}

int x = 0;

void loop()
{
  float temp;
  do {
    delay(200);
    temp = tempRead();
    printNum(floor(temp));
    
    byte tmp = floor(temp);
    if(x == 0 && lightRead() >= 9){
      Serial.println("Sending signal...");
      
      Wire.beginTransmission(5); //slave 1
	  Wire.write(tmp); //temperature
      Wire.write('1'); //watering signal
      Wire.endTransmission();
      
      Wire.beginTransmission(6); //slave 2
	  Wire.write(tmp); //temperature
      Wire.write('1'); //watering signal
      Wire.endTransmission();
      
      x = 1;
      break;
    } else if(x == 1 && lightRead() <= 3){
      Serial.println("Priming...");
      
      Wire.beginTransmission(5); //slave 1
      Wire.write(tmp);
      Wire.write('0');
      Wire.endTransmission();
      
      Wire.beginTransmission(6); //slave 2
      Wire.write(tmp);
      Wire.write('0');
      Wire.endTransmission();
      
      //send UART reset
      x = 0;
    }
  } while(true); //light reading
  
  
  //UART Segment
  // send temp and light reading
  
  
}
    
float tempRead() {
  float temp = ((analogRead(A0) * (5.0/1024)) - 0.5)/0.01;
  return temp;
}

int lightRead() {
	return analogRead(A1);
}