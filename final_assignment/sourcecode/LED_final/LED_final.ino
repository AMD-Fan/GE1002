#include <stdlib.h>
#include <MsTimer2.h>

#include <Wire.h>
#include "TM1650.h"

TM1650 d;

//COUNTDOWN
char now_time[]="0000";
char num[1]="0";

int led = 3;
int input_time=5;//minutes

int buzzPin =  3;
int buzzcount = 0;

int signalpin=4;
int signalvalue=0;
int signalboompin=5;
int signalboomvalue=0;

int sec=0;
int min=input_time;

void setup() 
{
  pinMode(buzzPin, OUTPUT);
  pinMode(signalpin, INPUT);
  
  //I2C
  Wire.begin(); //Join the bus as master
  Serial.begin(9600); //Start serial communication at 9600 for debug statements
  d.init();

  //COUNTDOWN
//  MsTimer2::set(1000, clock_function);
//  MsTimer2::start();
  
  delay(1000);
  
}


void loop() 
{
  signalboomvalue=digitalRead(signalboompin);
  Serial.println(signalboomvalue);
  signalvalue=digitalRead(signalpin);
  if(signalboomvalue>0)
  {
    if(signalvalue>0)
    {
       if(min>=0)
      {
        
        
        if(sec<=0)
        {
          min--;
          sec=59;
        }
        else
        {
          sec--;
        }
      
        itoa(min/10,num,10);
        now_time[0]=num[0];
        itoa(min%10,num,10);
        now_time[1]=num[0];
        itoa(sec/10,num,10);
        now_time[2]=num[0];
        itoa(sec%10,num,10);
        now_time[3]=num[0];
      
      //  Serial.println(now_time);
      //  delay(2000);
        if(min<0)
        {
          return    ;
        }
      
        d.displayOn();
        d.displayString(now_time);
        delay(1000);

        if (min<1)
        {
          for(buzzcount=0;buzzcount<100;buzzcount++)
          {
            digitalWrite(buzzPin, HIGH);
            delay(1);
            digitalWrite(buzzPin, LOW);
            delay(1);
          }
        }
       
      }
      else
      {
        d.displayOn();
        d.displayString("0000");
        for(buzzcount=0;buzzcount<100;buzzcount++)
        {
          digitalWrite(buzzPin, HIGH);
          delay(10);
          digitalWrite(buzzPin, LOW);
          delay(10);
        }
      }
    }
    else
    {
      d.displayOn();
      d.displayString(now_time);
      delay(1000);
    }
  }
  else
  {
    while(1)
    {
      d.displayOn();
      d.displayString("0000");
      for(buzzcount=0;buzzcount<100;buzzcount++)
      {
        digitalWrite(buzzPin, HIGH);
        delay(10);
        digitalWrite(buzzPin, LOW);
        delay(10);
      }
    }

  }

  
}
