# Sensor Fusion with Digital Filtering

## Objective

The objective was to use two ultrasonic sensors to accurately measure the distance from an orthogonal object. This has to be done in the fastest way possible.
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration/images/problem_statement.png"  width="400"  height="200"  />
</p>

## Technical Approach

 1. Sampling of time data from the ultrasonic sensor.
 2. Calibration to map the time data into real distance using a fitting function.
 3. Fusion of two ultrasonic sensor then filter the distance data using a Kalman filter.
 4. Output the distance in real time and flash an LED and sound a buzzer when filtering is done.(after convergence)

## Hardware Implementation
The hardware used for this task are: Arduino Uno board, two HCSR04 sensors, breadboard and wires to connect everything, resistor, LED and buzzer. The given figure explains the connections used in the setup.
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration/images/sensor_setup_explanation.png"  width="500"  height="400"  />
</p>

The following figure shows the actual setup:
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration/images/sensor_setup.jpg"  width="500"  height="500"  />
</p>

## Sotware Implementation

 1. Time data from the two ultrasonic sensors were sampled.
 2. Piece wise calibration was performed for both sensors individually and time data was converted to real distance.
 3. Measurement co-variance (R) for the Kalman filter was calculated.
 4. After these steps Kalman filter was used to fuse the two sensors shown as below:
<p align = "center">
<img src="https://github.com/prateeks97/ADAS_Algorrithms_on_F1_10th/blob/master/Sensor%20Signal%20Processing/Sensor%20Fusion%20and%20Calibration/images/kalman_filter_sensor_fusion_logic.png"  width="750"  height="200"  />
</p>

The prediction was made by one sensor and correction was made by another sensor in the sensor fusion.

 5. At last the LED and buzzer were implemented so that they will turn on when the calibration has been completed.

## Results

 - Convergence in 6 seconds.
 - Piece-wise calibration gave us an accuracy of +/- 2 mm.
