JoyState_t joySt;

const int STEER_PIN = A0;
const int THROTTLE_PIN = A2;
//const int BRAKE_PIN = A2;
const int REPAIR_PIN = 4;
const int GEAR_PIN = 6;

void setup() {
   pinMode(STEER_PIN, INPUT);
   pinMode(THROTTLE_PIN, INPUT);
   //pinMode(BRAKE_PIN, INPUT);
   pinMode(REPAIR_PIN, INPUT_PULLUP);
   pinMode(GEAR_PIN, INPUT_PULLUP);
   //Serial.begin(9600);
   //while (!Serial) {}
   
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
  delay(25);
  uint16_t steering_val = analogRead(STEER_PIN);
  uint16_t throttle_val = analogRead(THROTTLE_PIN);
  //uint16_t brake_val = analogRead(BRAKE_PIN);
  
  if (steering_val > 510) { steering_val = 510; }
  if (steering_val < 160) { steering_val = 160; }
  
  if (throttle_val > 465) { throttle_val = 465; }
  if (throttle_val < 350) { throttle_val = 310; }
  
  //if (brake_val > 480) { brake_val = 480; }
  //if (brake_val < 260) { brake_val = 260; }
  
  joySt.xAxis = (map(steering_val, 160, 510, 255, 0));
  //Serial.println(steering_val);
  joySt.xRotAxis = (map(throttle_val, 310, 465, 128, 0));
  //joySt.zAxis = (map(brake_val, 260, 480, 128, 0));
  
  // Button values follow pattern of
  // 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100
  joySt.buttons = 0x0; 
  
  if (digitalRead(REPAIR_PIN) == HIGH) {
    joySt.buttons += 0x1;
  }
  if (digitalRead(GEAR_PIN) == HIGH) {
    joySt.buttons += 0x10; 
     //Serial.println("LOW Gear");
  } else {
     //Serial.println("HIGH Gear"); 
  }
  
  Joystick.setState(&joySt);
}
