
#include "Arduino.h"
#include <Stepper_28BYJ.h>
//#include <LiquidCrystal.h>

 const int stepsPerRevolution = 4078;  // change this to fit the number of steps per revolution
                                     // for your motor
 const int Triger = 22; 
 const int EchoSound = 24;
 const int ledPin = 13;  // 13 – если будете использовать встроенный в Arduino светодиод
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  //unsigned 
  float time_us1=0;
  //unsigned
  float distance_sm1=0;
 //int time_us1=0;
 //int distance_sm1=0;
//unsigned int distAll(7);
  int xd1, xd2, xd3;
  
  //инициализируем библиотеку Stepper_28BYJ на выходы 8-11
 Stepper_28BYJ myStepper_28BYJ(stepsPerRevolution, 8,9,10,11);
  void setup() 
  { 
  pinMode(Triger, OUTPUT); 
  pinMode(EchoSound, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  myStepper_28BYJ.setSpeed(2);
   
  Serial.begin(19200);
  //lcd.begin(16, 2); 
   
  razvedka();
  }
 void loop() 
 { 
   xd2=dist();  //вперед
   if (xd2==0){xd2=400;}
   Serial.print(xd1);Serial.print("  ");
   Serial.print(xd2);Serial.print("  ");
   Serial.println(xd3);
   if (xd2 < 15)
   { motors_stop(); razvedka();
     motor(1, 150, 0);motor(2, 150, 0);delay(400);
     if (xd1 > xd3) 
     { povorot (1, 100);}
     else
     { povorot (-1, 100);}
   }
   else
   {
    if (xd2 > 50)
    {motor(1, 250, 1);motor(2, 250, 1);}
   else 
    {motor(1, xd2*5-5, 1);motor(2, xd2*5-5, 1);}
   delay(200);
   }
 }
 int dist()
 {
  int rast;
  
  /*digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);*/
  
  digitalWrite(Triger, HIGH); // Подаем сигнал на выход микроконтроллера 
  delayMicroseconds(10); // Удерживаем 10 микросекунд 
  digitalWrite(Triger, LOW); // Затем убираем 
  time_us1=pulseIn(EchoSound, HIGH); // Замеряем длину импульса 
  rast=time_us1/58; // Пересчитываем в сантиметры
  //rast=distance_sm1;
  delay(50);
  return rast;
  }
   
  int route(int i9)
  { myStepper_28BYJ.step(stepsPerRevolution/i9);
  }
  
  int motor ( int num_motor, int am_motor, int direkt_motor)
   { am_motor=abs(am_motor);
     if (num_motor==1) 
     { 
       if (direkt_motor == 1) {digitalWrite(7, LOW); analogWrite(6, am_motor);}
       else {digitalWrite(6, LOW); analogWrite(7, am_motor);}
     }
     else
     {
       if (direkt_motor == 1) {digitalWrite(5, LOW); analogWrite(4, am_motor);}
       else {digitalWrite(4, LOW); analogWrite(5, am_motor);}
     }
   }
  int povorot( int direkt_povorot, int ugol)
   { 
     if (direkt_povorot >0) 
       {digitalWrite(7, LOW); analogWrite(6, 140);digitalWrite(4, LOW); analogWrite(5, 140);}
     else
       {digitalWrite(6, LOW); analogWrite(7, 140);digitalWrite(5, LOW); analogWrite(4, 140);}
     delay(ugol*14);
     motors_stop();
   }  
   
   int razvedka()
   {
   myStepper_28BYJ.step(902);
   delay(100);
    xd1=dist();  //вправо
   myStepper_28BYJ.step(-900);
   delay(100);
    xd2=dist();  //вперед
   myStepper_28BYJ.step(-900);
   delay(100);
    xd3=dist();  //влево                                //вправо 60
   myStepper_28BYJ.step(902);
   delay(100);
   // xd2=dist();  //вперед
   }
   int motors_stop()
   {digitalWrite(7, LOW);digitalWrite(6, LOW);digitalWrite(5, LOW);digitalWrite(4, LOW);
   }
