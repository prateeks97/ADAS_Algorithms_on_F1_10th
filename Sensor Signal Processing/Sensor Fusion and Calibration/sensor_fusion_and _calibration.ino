#define trigPin 13               //defining trigger pin for prediction sensor(sensor1)
#define echoPin 12               //defining echopin (Reciever)for prediction sensor
#define trigPin1 11              //defining trigger pin for correction sensor(sensor2)
#define echoPin1 10              //defining echopin (Reciever)for correction sensor
int beep=5;                      //connect buzzer to pin 5
int LED=4;                       //connect LED to pin 4
float K,y_cor,y_prd,p_prd,y_cor1,p_prd1;    //defining variables for Kalman filter
float R1 = 30;                   //defining variance of the sensor1
float R2= 20;                    //defining variance of the sensor2
float p_cor= R1;                 //defining intial value of variance as sensor variance 
float duration1,duration2,z1,z2; //defining variables for distance and duration
float a1= 0.1757;                // slope of calibration equation sensor1
float b1= -6.8058;               // intercept of calibration equation sensor1 
float a2= 0.1759;                // slope of calibration equation sensor2
float b2= -4.8477;               // intercept of calibration equation sensor2 

void setup() {
  Serial.begin(9600);         //Serial communications at 9600 bps
  pinMode(trigPin,OUTPUT);    //initialize trigger pin 13
  pinMode(echoPin,INPUT);     //initialize echo pin 12
  pinMode(trigPin1,OUTPUT);   //initialize trigger pin 11
  pinMode(echoPin1,INPUT);    //initialize echo pin 10
  pinMode(beep, OUTPUT);      //initialize buzzer pin 5
  pinMode(LED, OUTPUT);       //initialize LED pin 4
  
}

void loop() {
    digitalWrite(trigPin, LOW);   //turn off trigger pin
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);  //turn off trigger pin
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);   //turn off trigger pin

    duration1 = pulseIn(echoPin,HIGH,10000);   //Read the HIGH pulse whose duration is the time (in microseconds)
    // piece wise calibration function
      if (z1>=800){               // conditions according to the distance
      z1 = a1*duration1 + b1+ 10; // calibration equation with correction in error
     }    
     else if (z2>=550 && z2<=650){
      z1 = a1*duration1 + b1;
     }
      else{
      z1 = a1*duration2 + b1-3;    // calibration equation for distance more than 800mm
     }
    delayMicroseconds(20);
    

     //Second sensor 
    digitalWrite(trigPin1, LOW);   //turn off trigger pin
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);  //turn on trigger pin
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);   //turn off trigger pin

    duration2 = pulseIn(echoPin1,HIGH,10000);   //Read the HIGH pulse whose duration is the time (in microseconds)
    
    if (z2>=750){                 // conditions according to the distance
      z2 = a2*duration2 + b2+ 9;  // calibration equation with correction in error
    }
     else if (z2>=550 && z2<=650){
      z2 = a2*duration2 + b2-3;
     }
    else{
      z2 = a2*duration2 + b2-6;      // calibration equation for distance more than 800mm
    }

//    Prediction
    y_prd= y_cor;                 // prediction of the measured distance
    p_prd= p_cor;                 // variance in measured distance

//    Correction 1
    
    K= p_prd/(p_prd+R1);            // value of kalman gain
    y_cor1= y_prd + (K*(z1-y_prd)); //correction in measured distance
    p_prd1= (1-K)*p_prd;            // variance in corrected value of distance

//    Correction 2

    K= p_prd1/(p_prd1+R2);          //value of kalman gain
    y_cor= y_cor1 + K*(z2-y_cor1);  //correction in measured distance
    p_cor= (1-K)*p_prd1;            //variance in corrected value of distance

    Serial.print(y_cor);          //print corrected distance in mm
    Serial.print("\t");
    Serial.println(p_cor);        //print variance

    if (p_cor<=0.03){             //value of variance after convergence
      digitalWrite(beep, HIGH);   //turn on buzzer
      digitalWrite(LED, HIGH);    //turn on LED
      delay(500);
      digitalWrite(beep, LOW);    //turn off buzzer
      digitalWrite(LED, LOW);     //turn off LED
      exit(0);                    // exit loop
    }
}
