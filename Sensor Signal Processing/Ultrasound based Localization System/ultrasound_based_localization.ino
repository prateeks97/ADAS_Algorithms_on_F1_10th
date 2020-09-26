int trigPin1= 13;                            //defining trigger pin for prediction sensor(sensor1)
int echoPin1= 12;                            //defining echopin (Reciever)for prediction sensor
int trigPin2= 11;                            //defining trigger pin for correction sensor(sensor2)
int echoPin2= 10;                            //defining echopin (Reciever)for correction sensor
float y_corx,y_cory,y_prdx,y_prdy,Kx,Ky;     //defining variables for Kalman filter
float p_corx=500,p_cory=500,p_prdx=500,p_prdy=500; //initializing value for kalman filter
float z1,z2,duration1,duration2;             //defining variables for distance and duration
float x,y;                                   // defining co-ordinates 
float Rx=10;                                 //defining variance of the sensor1
float Ry=15;                                 //defining variance of the sensor2
int beep=5;                                  //connect buzzer to pin 5
int LED=4;                                   //connect LED to pin 4
int l=80;                                    //distance between two sensors
float a1=0.1757;                             // slope of calibration equation sensor1
float b1= -3.8058;                           // intercept of calibration equation sensor1
float a2= 0.1759;                            // slope of calibration equation sensor2
float b2= -8.8477;                           // intercept of calibration equation sensor2
void setup() {
  Serial.begin(9600);          //Serial communications at 9600 bps
  pinMode(trigPin1,OUTPUT);    //initialize trigger pin 13
  pinMode(echoPin1, INPUT);    //initialize echo pin 12
  pinMode(trigPin2,OUTPUT);    //initialize trigger pin 11
  pinMode(echoPin2, INPUT);    //initialize echo pin 10
  pinMode(beep, OUTPUT);       //initialize buzzer pin 5
  pinMode(LED, OUTPUT);        //initialize LED pin 4

}

void loop() {

  digitalWrite(trigPin1, LOW);    //turn off trigger pin
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);   //turn off trigger pin
  delay(20);
  digitalWrite(trigPin1, LOW);    //turn off trigger pin
  delayMicroseconds(20);
  duration1=pulseIn(echoPin1, HIGH,10000);   //Read the HIGH pulse whose duration is the time (in microseconds)
  z1 = a1*duration1 + b1;              //calibration equation for sensor 1
  delayMicroseconds(1000);
  
  digitalWrite(trigPin2, LOW);    //turn off trigger pin
  delayMicroseconds(200);
  digitalWrite(trigPin2, HIGH);   //turn off trigger pin
  delay(10);
  digitalWrite(trigPin2, LOW);    //turn off trigger pin
  delayMicroseconds(20);
  duration2=pulseIn(echoPin2, HIGH,10000); //Read the HIGH pulse whose duration is the time (in microseconds)
  z2 = a2*duration2 + b2;         //calibration equation for sensor 2
  Serial.print(z1);   //print corrected x co-ordinate in mm
  Serial.print("\t");
  Serial.print(z2);   //print corrected y co-ordinate in mm
  Serial.print("\t");
  
  // equations for calculating co-ordinates from distances 
  x=(sq(z1)-sq(z2)+sq(l))/(2*l); 
  y=sqrt(sq(z1)-sq(x));
  x=sqrt(sq(z1)-sq(y));         //calculating x again to reduce variance 
  y=y+36;                       //adding value of radius to coordinates
  x=x+36-130;

  //Applying kalman filter to x co-ordinates
  y_prdx= y_corx;               // prediction of the measured distance in x direction
  p_prdx= p_corx;               // variance in measured distance in x direction

  Kx= p_prdx/(p_prdx + Rx);          // value of kalman gain
  y_corx= y_prdx+Kx*(x - y_prdx);    //correction in measured distance
  p_corx= (1-Kx)*p_prdx;             // variance in corrected value of distance

  //Applying kalman filter to x co-ordinates 
  y_prdy= y_cory;                    // prediction of the measured distance in y direction
  p_prdy= p_cory;                    // variance in measured distance in y direction

  Ky= p_prdy/(p_prdy + Ry);          //value of kalman gain
  y_cory= y_prdy+Ky*(y - y_prdy);    //correction in measured distance
  p_cory= (1-Ky)*p_prdy;             //variance in corrected value of distance

  Serial.print(y_corx);   //print corrected x co-ordinate in mm
  Serial.print("\t");
  Serial.print(y_cory);   //print corrected y co-ordinate in mm
  Serial.print("\t");
  Serial.print(p_corx);   //print variance for x co-ordinates
  Serial.print("\t");
  Serial.println(p_cory); //print variance for y co-ordinates
 
    if (p_corx<=0.05 && p_cory<=0.05){   //value of variance after convergence
    digitalWrite(beep, HIGH);            //turn on buzzer
    digitalWrite(LED, HIGH);             //turn on LED
    delay(1000);
  
    digitalWrite(beep, LOW);    //turn off buzzer
    digitalWrite(LED, LOW);     //turn off LED
    exit(0);                    // exit loop
  }
}
