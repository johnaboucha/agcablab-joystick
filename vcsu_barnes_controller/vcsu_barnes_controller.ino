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
const int PADDLE_ONE = A2;
const int PADDLE_TWO = A3;
const int PADDLE_THREE = A4;
const int PADDLE_FOUR = A5;


//Steering
const int MAX_TICKS = 1000;
const int MIN_TICKS = -1000;
//const int MAX_TICKS = 500;
//const int MIN_TICKS = -500;

Encoder steering(STEERING_A_PIN, STEERING_B_PIN);


void setup() {
  //Serial.begin(9600);
  //while (!Serial) {}
  //Serial.println("Hello world 1.");
  pinMode(THROTTLE_PIN, INPUT);
  
  pinMode(PADDLE_ONE, INPUT);
  pinMode(PADDLE_TWO, INPUT);
  pinMode(PADDLE_THREE, INPUT);
  pinMode(PADDLE_FOUR, INPUT);
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
  uint16_t throttle_val = analogRead(THROTTLE_PIN);
  //Serial.println(throttle_val);
  // 100 < throttle < 900
  //Serial.println(analogRead(A2));
  
  //uint16_t throttle_val = analogRead(THROTTLE_PIN);
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
  
  
  // Paddle 1 < 200
  // Paddle 2 < 200
  
  // PADDLE_THREE
  // White = Power
  // Black = Ground
  // Red = Data
  // Paddle 3 < 150
  
  // PADDLE_FOUR
  // Green = power
  // Black (tape) = ground
  // Black = data
  // Paddle 4 < 800
  
  // 120 < Throttle < 520
  
  // Set throttle
  //Serial.println(throttle_val);
  if (throttle_val > 900) { throttle_val = 900; }
  if (throttle_val < 100) { throttle_val = 100; }
  joySt.xRotAxis = (map(throttle_val, 100, 900, 255, 0));
  
  
  
  // Steering Axis 0 is joySt.xAxis
   joySt.xAxis = (map(steering_val, MIN_TICKS, MAX_TICKS, 0, 255));
   
  // Button values follow pattern of
  // 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100
  joySt.buttons = 0x0; 
  
  
  if (analogRead(PADDLE_ONE) > 800) {
      joySt.buttons += 0x2;
  } 
  if (analogRead(PADDLE_TWO) > 800) {
     joySt.buttons += 0x4; 
  }
  if (analogRead(PADDLE_THREE) > 800) {
     joySt.buttons += 0x8; 
  }
  if (analogRead(PADDLE_FOUR) > 800) {
    joySt.buttons += 0x1;
  }
  if (digitalRead(LIGHT_PIN) == LOW) {
     joySt.buttons += 0x10; 
  }
  
  Joystick.setState(&joySt);
 
  
  //delay(5);
}

