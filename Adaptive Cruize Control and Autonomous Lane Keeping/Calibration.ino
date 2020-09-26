#include <Servo.h> //define the servo library
Servo esc; //define that esc is a servo

void setup() {
esc.attach(11); 
pinMode(13,OUTPUT); 
//******Vehicle Calibration******//
esc.write(90);  delay(10000); // Start during neutral
esc.write(180); delay(5000);  // Set the high limit
esc.write(0);   delay(5000);  // Set the low limit
esc.write(90);  delay(5000);  // Set neutral value
}

void loop() {
  digitalWrite(13,HIGH); // Calibration Over
  delay(1000);
  }


  
