#include <Servo.h>              //define the servo library
//#include "Filter.h"             //define the filter
#define trigPin1 13             //defining trigger pin for lane keeping sensor
#define echoPin1 12             //defining echopin for lane keeping sensor
#define trigPin2 7              //defining trigger pin for adaptive cruise control (ACC) sensor
#define echoPin2 6              //defining echopin pin for adaptive cruise control (ACC) sensor

Servo ssm;                      //create an instance of the servo object called ssm
Servo esc;                      //create an instance of the servo object called esc
ExponentialFilter<long> ADCFilter1(80, 30);       // Create a new exponential filter with a weight of 80 and an initial value of 30(for ACC)
ExponentialFilter<long> ADCFilter2(70, 41);       // Create a new exponential filter with a weight of 70 and an initial value of 41(for Lane Keeping)

int steering=90;                                  //defining global variables for steering to use later
int throttle=90;                                  //defining global variables for throttle to use later
float duration1,duration2,distance1,distance2;    //defining the variables for duration and distance of both the sensors
float fil_d1, fil_d2;                             //......................
int   d1=40, d2= 120, d3=70, d4=90;               //defining the variables for different delays

// For Steering Control
float e_s = 0, e1_s = 0, e2_s = 0;
float u_s = 90;
float kp_s = 2, ki_s =0, kd_s = 0.5;              // Define PID parameters for steering controls
float k1_s = kp_s + ki_s + kd_s; 
float k2_s = -kp_s - 2*kd_s;
float k3_s = kd_s;

// For Adaptive Cruize Control
float e_a = 0, e1_a = 0, e2_a = 0;
float u_a = 90;
float kp_a = 0.8, ki_a =0, kd_a =0;              // Define PID parameters for throttle controls
float k1_a = kp_a + ki_a + kd_a;
float k2_a = -kp_a - 2*kd_a;
float k3_a = kd_a;

void setup() {
  Serial.begin(9600);              //start serial connection. Uncomment for PC
  ssm.attach(10);                  //define that ssm is connected at pin 10
  esc.attach(11);                  //define that esc is connected at pin 11
  Serial.begin(9600);              //Serial communications at 9600 bps
  pinMode(trigPin1,OUTPUT);        //initialize trigger pin 13
  pinMode(echoPin1,INPUT);         //initialize echo pin 12
  pinMode(trigPin2,OUTPUT);        //initialize trigger pin 7
  pinMode(echoPin2,INPUT);         //initialize echo pin 6
}

void loop() {
    // For Steering Controls
    digitalWrite(trigPin1, LOW);          //turn off trigger pin
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);         //turn on trigger pin
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);          //turn off trigger pin
     
    duration1 = pulseIn(echoPin1,HIGH);   //Read the HIGH pulse whose duration is the time (in microseconds)  
    distance1= (duration1/2)*0.03435;     //Converting duration into distance 
    ADCFilter1.Filter(distance1);         //Applying exponential filter on the distance measured.............
    fil_d1 = ADCFilter1.Current();        //................

    
    // For Adaptive Cruize Control
    digitalWrite(trigPin2, LOW);          //turn off trigger pin
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);         //turn off trigger pin
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);          //turn off trigger pin 
    duration2 = pulseIn(echoPin2,HIGH);   //Read the HIGH pulse whose duration is the time (in microseconds)
    distance2= (duration2/2)*0.03435;     //Converting duration into distance
    ADCFilter2.Filter(distance2);         //Applying exponential filter on the distance measured............
    fil_d2 = ADCFilter2.Current();        //...............
    
    // PID Controller for Steering control
    e2_s = e1_s;
    e1_s = e_s;
    e_s= 30-fil_d1;                       //defining current error as the difference of filtered distance and 31cm(distance from wall considering sensor placement)
    u_s = u_s + k1_s*e_s + k2_s*e1_s + k3_s*e2_s;   //PID controller steering output stored in u_s variable

    // PID Controller for Throttle control
    e2_a = e1_a;
    e1_a = e_a;
    e_a = fil_d2-41;                      //defining current error as the difference of filtered distance and 41cm (distance from from object considering sensor placement)
    
    if (fil_d2>=40.5 && fil_d2<=41.5){    //defining a dead zone for the vehicle for stable stopping point for adaptive cruize control
      u_a=90;                             //giving signal for zero throttle input for the dead zone
      e_a=0;                              //defining zero error for the dead zone
    }
    else {
      e_a= fil_d2-41;                     //defining current error for normal conditions 
    }
    u_a = u_a + k1_a*e_a + k2_a*e1_a + k3_a*e2_a;   //PID controller throttle output stored in u_a variable
    
    setVehicle(u_s, u_a);                 //defining PID controller outputs to set steering and throttle
    
    //implementing if case for different delays for accurate behaviour of the vehicle for forward and reverse motion
    if (fil_d2<=41){                      
       delay(d3);
    }
    else{
      delay(d1);
    }
    setVehicle(u_s,90);
    if (fil_d2<=41){
      delay(d4);
    }
    else{
      delay (d2);
    }
}

//********************** Vehicle Control **********************//
//***************** Do not change below part *****************//
void setVehicle(int s, int v) 
{
  s=min(max(0,s),180);  //saturate steering command
  v=min(max(80,v),105); //saturate velocity command
  ssm.write(s); //write steering value to steering servo
  esc.write(v); //write velocity value to the ESC unit
}


//***************** Do not change above part *****************//
