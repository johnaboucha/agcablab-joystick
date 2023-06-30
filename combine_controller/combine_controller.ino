#include <Encoder.h>
#include <Bounce.h>

//This runs on an Arduino Leonardo with a custom IDE build

JoyState_t joySt;

const int DEBOUNCE_TIME = 15;

const int THROTTLE_PIN = A0;
const int STEERING_A_PIN = 9;
const int STEERING_B_PIN = 8;
const int START_PIN = 7;
const int DUMP_PIN = 6;
const int RAISE_PIN = 5;
const int LOWER_PIN = 4;
const int OUT_PIN = 3;
const int IN_PIN = 2;

// Test Gear
const int GEAR_PIN = 10;

//Steering
const int MAX_TICKS = 1000;
const int MIN_TICKS = -1000;
//const int MAX_TICKS = 500;
//const int MIN_TICKS = -500;

//Bounce start = Bounce(START_PIN, DEBOUNCE_TIME);
//Bounce raise = Bounce(RAISE_PIN, DEBOUNCE_TIME);
//Bounce lower = Bounce(LOWER_PIN, DEBOUNCE_TIME);
//Bounce in = Bounce(IN_PIN, DEBOUNCE_TIME);
//Bounce out = Bounce(OUT_PIN, DEBOUNCE_TIME);
//Bounce dump = Bounce(DUMP_PIN, DEBOUNCE_TIME);

Encoder steering(STEERING_A_PIN, STEERING_B_PIN);


void setup() {
  Serial.begin(9600);
  //while (!Serial) {}
  Serial.println("Hello world 1.");
  pinMode(THROTTLE_PIN, INPUT);
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(DUMP_PIN, INPUT_PULLUP);
  pinMode(RAISE_PIN, INPUT_PULLUP);
  pinMode(LOWER_PIN, INPUT_PULLUP);
  pinMode(OUT_PIN, INPUT_PULLUP);
  pinMode(IN_PIN, INPUT_PULLUP);
  pinMode(GEAR_PIN, INPUT_PULLUP);

  //delay(25);  
  //start.update();
  //raise.update();
  //lower.update();
  //in.update();
  //out.update();
  //dump.update();
  //delay(25);
  
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
  if (throttle_val > 910) { throttle_val = 910; }
  if (throttle_val < 470) { throttle_val = 470; }
  joySt.xAxis = (map(throttle_val, 470, 910, 0, 255));
  joySt.yAxis = (map(steering_val, MIN_TICKS, MAX_TICKS, 0, 255));
  //Serial.println(throttle_val);
    
  // Button values follow pattern of
  // 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100
  joySt.buttons = 0x0; 
  

  
  if (digitalRead(RAISE_PIN) == LOW) {
     joySt.buttons += 0x1;
     //Serial.println("Raise");
  }
  if (digitalRead(LOWER_PIN) == LOW) {
     joySt.buttons += 0x2; 
     //Serial.println("Lower");
  }
  if (digitalRead(OUT_PIN) == LOW) {
     joySt.buttons += 0x4; 
     //Serial.println("boom out");
  }
  if (digitalRead(IN_PIN) == LOW) {
     joySt.buttons += 0x8; 
     //Serial.println("boom in");
  }
  if (digitalRead(DUMP_PIN) == LOW) {
     joySt.buttons += 0x10; 
     //Serial.println("dump");
  }
  if (digitalRead(START_PIN) == LOW) {
     joySt.buttons += 0x20; 
     //Serial.println("start");
  }
  if (digitalRead(GEAR_PIN) == LOW) {
     joySt.buttons += 0x40; 
  }

  Joystick.setState(&joySt);
  
 // delay(5);
}

