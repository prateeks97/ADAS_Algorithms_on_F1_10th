# Ultrasound based Localization System

## Objective

Our objective was to use two ultrasonic sensors to accurately measure the x and y coordinates of the object placed in front of them.
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System/images/problem_statement.png"  width="400"  height="200"  />
</p>

## Technical Approach

 1. Sampling of time data from the ultrasonic sensor.
 2. Calibration to map the time data into real distance using a fitting function.
 3. Localization to calculate the x and y coordinates of the object. (Used Distance formula)
 4. Filtering the noise in position data using a Kalman filter.
 5. Output the distance in real time and flash an LED and sound a buzzer when filtering is done.(after convergence)

## Hardware Implementation
The hardware used for this task are: Arduino Uno board, two HCSR04 sensors, breadboard and wires to connect everything, resistor, LED and buzzer. The given figure explains the connections used in the setup.
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System/images/sensor_setup_explanation.png"  width="500"  height="400"  />
</p>

The following figure shows the actual setup:
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System/images/sensor_setup.png"  width="700"  height="500"  />
</p>

## Software Implementation

 1. Time data from the two ultrasonic sensors were sampled.
 2. Piece wise calibration was performed for both sensors individually and time data was converted to real distance.
 3. Distance formula was implemented for localization i.e. to find x and y coordinates.
 4. Kalman filter implemented to filter out x and y coordinates. The logic of Kalman filter is shown below:

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System/images/kalman_filter_logic.png"  width="700"  height="300"  />
</p>

 5. At last the LED and buzzer were implemented so that they will turn on when the calibration has been completed.

## Results

 - Convergence in 7.8 seconds.
 - Piece-wise calibration gave us an accuracy of +/- 5 mm. 
 - Coefficients of calibration function for sensor 1 and 2  as below:
**Sensor 1**
A= 0.1757
B= -3.8058
**Sensor 2**
A=0.1759
B= -8.8477
