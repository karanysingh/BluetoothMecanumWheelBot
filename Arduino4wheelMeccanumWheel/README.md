# CODE - ARDUINO
### Functions

  * `void setup()` - state is setup in the function.
  * `void loop()`- state is updated depending on what is received from bluetooth and passed to execution function.
  * `void execution()`- pins are set HIGH or LOW depending on the requirement corresponding to the state variable passed in the function.
  * > In `void loop()` function, code passes the current `state` variable value to function `void execution()` If bluetooth module is receiving a value. else it passes 'P' to the same function.


### Cases  
  * `W`:  forward(); 
  * `A`:  left();
  * `D`:  right();
  * `S`:  backward();
  * `R`:  clockwise();
  * `L`:  anti_clockwise();
  * `P` : s_stop();
  * ![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c4/Mecanum_wheel_control_principle.svg/600px-Mecanum_wheel_control_principle.svg.png "Mecannum Wheels Directions")
  
