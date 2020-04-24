# Documentation: CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program


The points addressed below are towards fulfilment of the project requirements as per the rubric.

[//]: # (Image References)

[image1]: ./writeup_images/bridge.jpg "Bridge"
[image2]: ./writeup_images/left_turn.jpg "Left Turn"
[image3]: ./writeup_images/right_turn_entry.jpg "Right Turn"




## Compilation
### Code Compiles Correctly

The code compiles without any issues using `cmake` and `make`. The generic `CMakeLists.txt` provided was used as is. 
Used the following set of commands to build

`cd CarND-PID-Control-Project`
`mkdir build && cd build`
`cmake ..`
`make`

Ran the build on the simulator using 

`./pid`




## Implementation

### PID Follows Lessons

Besides the tuning of the hyperparameters, the controller uses the logic described in the lessons. Methodology used for updating the individual errors, and calculating the final error follows the theory learnt.




## Reflection

### Effect of Individual Components
The final error calculation is the sum of the individual errors for the P, I and D components. As expected, each of these have an important role toward stable control of the vehicle in this project. They are discussed below

__Proportional Component__: Represented in the code of `PID.cpp` as coefficient `Kp`, this component compensates for the error in direct proportion to it. In the project this component helps to move the car towards the lane center to minimize the error value. The value `Kp` is the weighing factor we want error to have directly in the corrective response. The equations used for it are given below, with `cte` as the current trajectory error.

Ref: `PID.cpp`
`p_error = cte;`
`Kp*p_error`


__Integral Component__ : The integral component is not critical for a perfect control system. But real systems have biases, and the integral component helps to compensate those based on the summation of historical errors. For example, in the project if the steering has a bias it will be compensated by the integral component. In the code, `Ki` is used as the coefficient for the integral error.

Ref: `PID.cpp`
`i_error = i_error+ cte;`  
`Ki*i_error`


__Derivative Components__ : Stability of system is quite dependent on the derivative component. The proportional component on it's own moves towards the target to minimize the error, but it overshoots and if left unchecked leads to oscillations. The derivative term, a weigted response to rate of the change error, helps to control overshoot by weighing in how fast the error is growing. In our particular case, it is the difference between current error and previous error of the trajectory. The derivative term helps prevent oscillation of the vehicle from side to side. It also helps increase steering response around turns when the error grows fast. The coefficient is used as `Kd`.

Ref: `PID.cpp`
`d_error = cte - p_error;`
`Kd*d_error`


The coefficients of these individual components are tuned to represent their weight in the corrective response.




### Hyperparameter Tuning

Tuning was the most challenging and fun part of this project. It also happens to be the most critical one.
In this particular case the tuning was done manually. Initial attempts to employ twiddle resulted in car getting unstable and going off-road.

However, the process used for manual tuning was somwhat like the twiddle logic, albeit more intuition based than iterative. 
Starting with the intial set of `p = [1, 1, 1]` values were scaled up or down using the logic described below. The `dp` values were subjective, determined by the vehicle behavior. Instead of total error, the response was used as a 'metric' of performance.

* Run the vehicle with the current set of `p`, and check the response. Monitor the behavior, specifically car oscillation left to right, steering oscillation, and vehicle's sudden jerks

* Increment one of the `Kp`, `Ki`, or `Kd` values
* If the response deteriorates, decrement the initial value and try again. Continue till there is a observable change in behavior.
* When the response improves, go to next component. And repeat the process.

* When the vehicle behavior is close to the desired one, reduce the quantum of change.

* Iterate starting with some different values to avoid a 'local minima'.


While more time consuming, the manual tuning process helped in better practical understanding of how the individul components affect the response. Some of it is reflected in the previous section.


#### Challenges Faced
Most fine tuning was required to navigate two parts of the track where the vehicle would be on the edge of the track at times. These were the two turns right after the bridge- the first left turn, and the following right turn. 
If the `Kd` or `Kp` values were somewhat higher, the turn was navigated sucessfully but vehicle started oscillating in the next section and  momentarily moved off track.


This was resolved when the final set of correct values was reached. Strong enough proportional and derivative control to maneuver turns, but not dangerously oscillate when exiting the turns.

Left Turn

![alt text][image2]



Right Turn

![alt text][image3]




## Simulation

### Successful Laps Around Track

The car was able to successfully drive multiple laps around the track. Throughout the duration of the drive, all the tires of the vehicle stay within the drivable section of the track. Dangerous oscillation were also avoided.


![alt text][image1]

