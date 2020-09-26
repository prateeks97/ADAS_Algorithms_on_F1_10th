## Implementation of ADAS algorithms on F1/10th using Arduino IDE.

**Objective:**

The objective was to design and implement the vehicle control algorithms such that vehicle was able to maintain a distance of 30cm from any object placed ahead of it. It was also required to stop the vehicle 30cm away from a stationary obstacle placed ahead of it. The second was to maintain a distance of 40cm from the side wall and remain in the center of the defined lane.

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruise%20Control%20and%20Autonomous%20Lane%20Keeping/images/acc_lane_keeping.gif" />
</p>

For this activity, an initial sub-task of implementing sensor signal processing was accomplished, and then the task of developing ADAS algorithms for the F1/10th car were undertaken.

### 1. Sensor signal processing:

**1a. Sensor fusion with digital filtering**

implementation details can be found [here](https://github.com/shorane/ADAS_Algorithms_on_F1_10th/tree/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration)

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration/images/kalman_filter_sensor_fusion_logic.png" height="250"  />
</p>

**1b. Ultrasonic sensor-based Localization system**
implementation details can be found [here](https://github.com/shorane/ADAS_Algorithms_on_F1_10th/tree/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System)

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Ultrasound%20based%20Localization%20System/images/kalman_filter_logic.png"  height="250"  />
</p>

### 2. ACC and Lane-keeping 
implementation details can be found [here](https://github.com/shorane/ADAS_Algorithms_on_F1_10th/tree/master/Adaptive%20Cruise%20Control%20and%20Autonomous%20Lane%20Keeping)

**For ACC**
 - Sampling the time data received from the sensor
 - Implementing Exponential Filter
 - PID Implementation
 - PWM Implementation

**For Lane Keeping**
 - Sampling the time data received from the sensor
 - Implementing Exponential Filter
 - PID Implementation
 
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruise%20Control%20and%20Autonomous%20Lane%20Keeping/images/lane_keeping_logic.png"  width="700"  height="200"  />
</p>

<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Adaptive%20Cruise%20Control%20and%20Autonomous%20Lane%20Keeping/images/hardware.png"  width="700"  height="300"  />
</p>
