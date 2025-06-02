#define RED 0
#define GREEN 1
#define YELLOW 2
#define PED 3

int state = RED, remainingTime = 5;
bool pedRequest = false;
unsigned long lastChange = 0;

const int lights[] = {2, 3, 4};       // red, yellow, green
const int ped = 5, buzzer = 6, btn = 7;
const int segPins[] = {8, 9, 10, 11, 12, 13, A0};

const byte digits[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

void setup() {
  for (int i = 2; i <= A0; i++) pinMode(i, OUTPUT); // set all lights and buzzer pins as outputs
  pinMode(btn, INPUT_PULLUP); // button pin as input with pull-up resistor
  showDigit(remainingTime);  // display initial time on 7-segment display
}

void loop() {
  unsigned long now = millis();  // get current time in milliseconds
  if (!digitalRead(btn)) pedRequest = true;

  int timeLeft = max(0, remainingTime - (now - lastChange) / 1000); // calculate remaining time in seconds by subtracting the elapsed time from the remaining time
  showDigit(timeLeft);

  if ((now - lastChange) >= remainingTime * 1000UL) { // check if the remaining time has elapsed
    switch (state) { // change the state based on the current state and remaining time
      case RED:
        if (pedRequest) { state = PED; remainingTime = 10; buzz(); digitalWrite(ped, 1); } // if a pedestrian requests to cross, switch to PED state
        else { state = GREEN; remainingTime = 10; }
        break;
      case GREEN:  state = YELLOW; remainingTime = 3; break;
      case YELLOW: state = RED; remainingTime = 5; break;
      case PED: digitalWrite(ped, 0); buzz(); pedRequest = false; state = GREEN; remainingTime = 10; break;
    }
    lastChange = now; // reset the last change time to the current time
    updateLights(); // update the lights based on the new state
  }

  if (state == PED && timeLeft <= 3) digitalWrite(ped, millis() / 300 % 2); // blink the pedestrian light if in PED state and less than 3 seconds remaining
}

void updateLights() {
  digitalWrite(lights[0], state == RED || state == PED);
  digitalWrite(lights[1], state == YELLOW);
  digitalWrite(lights[2], state == GREEN);
}

void buzz() {
  digitalWrite(buzzer, 1); delay(300); digitalWrite(buzzer, 0);
}

void showDigit(int n) {
  for (int i = 0; i < 7; i++) digitalWrite(segPins[i], digits[n][i]); // cycles through the pinouts and turns them on or off respectively according to the digit
}
