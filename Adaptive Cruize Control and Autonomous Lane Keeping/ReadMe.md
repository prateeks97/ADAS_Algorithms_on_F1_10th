# Adaptive Cruise Control and Autonomous Lane Keeping

## Objective

The objective was to design and implement the vehicle control algorithms such that vehicle was able to maintain a distance of 30cm from any object placed ahead of it. It was also required to stop the vehicle 30cm away from a stationary obstacle placed ahead of it.
The second was to maintain a distance of 40cm from the side wall and remain in the center of the defined lane.

**Adaptive Cruize Control (ACC)**
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/acc_logic.jpg"  width="400"  height="200"  />
</p>

**Autonomous Lane Keeping**
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/lane_keeping_logic.png"  width="700"  height="200"  />
</p>

## Technical Approach
**For ACC**
 - Sampling the time data received from the sensor
 - Implementing Exponential Filter
 - PID Implementation
 - PWM Implementation

**For Lane Keeping**
 - Sampling the time data received from the sensor
 - Implementing Exponential Filter
 - PID Implementation

## Hardware Implementation
The hardware used for this task are: 
1.	Battery power supply for Arduino circuit board.
2.	Bread Board with series and parallel connections
3.	Remote Controlled Traxxas Vehicle
4.	300mAH Lithium ion batteries
5.	USB cable
6.	Jumper cables
7.	Two ultrasonic sensors

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/hardware.png"  width="700"  height="300"  />
</p>

**Hardware Integrated Vehicle**
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/f1_10th_integrated.jpg"  width="600"  height="500" />
</p>

## Software Implementation
**For ACC**

 - Firstly, the Exponential filter and Servo library was imported in the code to use it in the next steps.
 - Variables were defined for exponential filter and PID controller and initial values were set for the steering and throttle.
 - Time data received from the ultrasonic sensor is sampled and converted to distance in real time.
 - Exponential Filter is implemented in Adaptive cruise control.
 - PD controller implementation for throttle control with the implementation of dead zone at 30cm from the wall so that the car does not fluctuate when stopped by an obstruction. PWM is also implemented to make the car run slower on the slope so that the car can steer well. Also, duty cycle was increased for the case when car has to climb the slope in reverse direction.

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/pulse_width_modulation.png"  width="700"  height="300"  />
</p>

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/pid_acc.png"  width="800"  height="300"  />
</p>

 - (Filtered_distance)[n] = w × (sensor_distance)[n] + (1 – w) × (Filtered_distance)[n–1] where, w is the weight factor from 0 to 1
 - Weight factor of 80% was selected to compromise between desired performance and system lag. 


<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/exponential_filter_results.JPG"  width="700"  height="300"  />
</p>

**For Lane keeping**

 - Firstly, the Exponential filter and Servo library was imported in the code to use it in the next steps.
 - Variables were defined for exponential filter and PID controller and initial values were set for the steering and throttle.
 - Time data received from the ultrasonic sensor is sampled and converted to distance in real time.
 - PD controller implemented for steering control.

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/pid_lane_keeping.png"  width="800"  height="300"  />
</p>

## Results
**ACC:**

The vehicle is stopping and maintaining the distance of 30cm from the front obstacle as shown in figure below:
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/acc_working.png"  width="400"  height="600"  />
</p>

**Lane Keeping:**

The vehicle is keeping itself inside the lane defined and can be seen in the following figure:
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/lane_keeping_working.png"  width="400"  height="600"  />
</p>

**ADAS functions Working Video:**
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruize%20Control%20and%20Autonomous%20Lane%20Keeping/images/acc_lane_keeping.gif" />
</p>
