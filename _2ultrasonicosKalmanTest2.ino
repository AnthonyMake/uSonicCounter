#include <Kalman.h>
#define echo1 6
#define trig1 7 
#define echo2 8
#define trig2 9

Kalman myFilter1(0.125,32,1023,0);
Kalman myFilter2(0.125,32,1023,0);

double sensor1, sensor2, thres=60;
boolean bajoSensor1=false;
boolean bajoSensor2=false;
String dir;
int cuenta=0;

void setup() {
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
  sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));

  while(sensor1<thres && sensor2>thres){
    
    sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
    sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));

    while(sensor1<thres && sensor2<thres){
      
      sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
      sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));  

      while(sensor1>thres && sensor2<thres){
        sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
        sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));  

        while(sensor1>thres && sensor2>thres){
            cuenta++;
            break;
        }
      }
    }
  }

  while(sensor1>thres && sensor2<thres){
    
    sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
    sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));

    while(sensor1<thres && sensor2<thres){
      
      sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
      sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));  

      while(sensor1<thres && sensor2>thres){
        sensor1=myFilter1.getFilteredValue(medicionUltrasonico(1));
        sensor2=myFilter2.getFilteredValue(medicionUltrasonico(2));  

        while(sensor1>thres && sensor2>thres){
            cuenta--;
            break;
        }
      }
    }
  }
  
  Serial.println(cuenta);
}

long medicionUltrasonico(int sensor){

  int echo,trig;
  
  if(sensor==1){
    echo=echo1;
    trig=trig1;  
  }
  if(sensor==2){
    echo=echo2;
    trig=trig2;
  }

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  long duration=pulseIn(echo,HIGH,100000);
  long distance=duration/58.0;

  return distance;
}
