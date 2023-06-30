#include <Encoder.h>
#include <Bounce.h>

//This runs on an Arduino Leonardo with a custom IDE build

JoyState_t joySt;

const int DEBOUNCE_TIME = 15;

const int THROTTLE_PIN = A0;
const int STEERING_A_PIN = 2;
const int STEERING_B_PIN = 3;
const int LIGHT_PIN = 4;

// Paddles
const int PADDLE_ONE = A1;
const int PADDLE_TWO = A2;
const int PADDLE_THREE = A3;
//const int PADDLE_FOUR = A4;

//Steering
const int MAX_TICKS = 1000;
const int MIN_TICKS = -1000;
//const int MAX_TICKS = 500;
//const int MIN_TICKS = -500;

Encoder steering(STEERING_A_PIN, STEERING_B_PIN);


void setup() {
  Serial.begin(9600);
  //while (!Serial) {}
  //Serial.println("Hello world 1.");
  pinMode(THROTTLE_PIN, INPUT);
  
  pinMode(PADDLE_ONE, INPUT);
  pinMode(PADDLE_TWO, INPUT);
  pinMode(PADDLE_THREE, INPUT);
  //pinMode(PADDLE_FOUR, INPUT);
 pinMode(LIGHT_PIN, INPUT_PULLUP);
  
  joySt.xAxis = 0;
	joySt.yAxis = 0;
	joySt.zAxis = 0;
	joySt.xRotAxis = 0;
	joySt.yRotAxis = 0;
	joySt.zRotAxis = 0;
	joySt.throttle = 0;
	joySt.rudder = 0;
	joySt.hatSw1 = 0;
	joySt.hatSw2 = 0;
	joySt.buttons = 0;
}

void loop() {
  //start.update();
  //raise.update();
  //lower.update();
  //in.update();
  //out.update();
  //dump.update();
  
  // 120 < throttle < 520

  uint16_t throttle_val = analogRead(THROTTLE_PIN);
  long steering_val = steering.read();
  
  if (steering_val < MIN_TICKS)
  {
    steering_val = MIN_TICKS;
    steering.write(MIN_TICKS);
  } else if (steering_val > MAX_TICKS)
  {
    steering_val = MAX_TICKS;
    steering.write(MAX_TICKS);
  }
  
  // john boucha
  //Joystick.Y(map(steering_val, MIN_TICKS, MAX_TICKS, 1023, 0));
  //Joystick.X(map(throttle_val, 500, 1040, 0, 1023)); //this is here incase we have to change the thresholds
  if (throttle_val > 820) { throttle_val = 820; }
  if (throttle_val < 120) { throttle_val = 120; }
  joySt.xRotAxis = (map(throttle_val, 120, 820, 255, 0));
  joySt.xAxis = (map(steering_val, MIN_TICKS, MAX_TICKS, 0, 255));
  //Serial.println(throttle_val);
    
  // Button values follow pattern of
  // 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100
  joySt.buttons = 0x0; 
  

  
  //if (digitalRead(RAISE_PIN) == LOW) {
  //   joySt.buttons += 0x1;
  //   //Serial.println("Raise");
  //}
  
  if (analogRead(PADDLE_ONE) < 300) {
      joySt.buttons += 0x2;
  } 
  if (analogRead(PADDLE_TWO) < 300) {
     joySt.buttons += 0x4; 
  }
  if (analogRead(PADDLE_THREE) < 300) {
     joySt.buttons += 0x8; 
  }
  if (digitalRead(LIGHT_PIN) == LOW) {
     joySt.buttons += 0x1; 
  }
  
  //Serial.println(analogRead(PADDLE_TWO));
  Joystick.setState(&joySt);
  
 // delay(5);
}

