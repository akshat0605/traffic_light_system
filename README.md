# Traffic_Light_System

## **Report**

##**Name: Akshat Agarwal**
##**Branch: Energy Engineering**


###**Design:**
The design is kept pretty simple and solely based on the problem statement. There are three LEDs for traffic lights Red, Green, Blue and another Green LED for pedestrians. There is also a buzzer installed to indicate when to stop and when to move for the pedestrians. The push button toggles the pedestrian state. The brain of the whole circuit is Arduino UNO.

###**Code Logic:**
First we define the 4 states namely, RED, GREEN, BLUE, PED to toggle them later on. Then we define the pinouts for the components. Next I built a 2D array defining the high(1) and low(0) patterns for various numbers to be displayed on the 7-segment display.
In the setup, I have defined all the LED pins as output via for loop, button as input and also initialized a showDigit() function which basically prints the required digit on input. It works by looping through the 7 output pins and assigning them 1 or 0 based on the 2D of patterns we coded earlier.
For the void loop, first we calculate the current time using millis() function. Also if button is pressed, we change pedestrain request from false to true.Then we display remaining time on the Display.
Next we cycle through the different states we defined earlier and take actions accordingly.
Lastly we update the LEDs according to the current state.

###**Challenges Faced:**
There were quite a few challenges I faced:
1) 7 segment display was something new to work with and it was tough to keep the code short and simple as earlier I was trying to define different functions for each digit instead of the 2D array.
2) A lot of part of the coding section was new to me, like the time management part.
3) At some instances, I couldn’t figure out the logic for certain things like how to display the time left or how to cycle through the different states.
