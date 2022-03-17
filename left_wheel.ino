/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */
// Include the servo library:
#include <Servo.h>

// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 4

// Servo
int angle = 0;
boolean latched = false;
int latch_angle = 270;
int unlatch_angle = 0;

// Communication
char incomingData = 0;
bool started= false;//True: Message is strated
bool ended   = false;//True: Message is finished 
char incomingByte ; //Variable to store the incoming byte
char msg[3];    //Message - array from 0 to 2 (3 values - PWM - e.g. 240)
byte index;     //Index of array

void setup() {
  Serial.begin(9600);
  
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);

  myservo.write(latch_angle);
  latched = true;
}

void loop() {

  if (Serial.available() > 0) {
    incomingData = Serial.read();
    
    if (incomingData == '1') {
      if (latched) {
        myservo.write(unlatch_angle);
        latched = false;
        Serial.println("Unlatched!");
      } 
      else {
        myservo.write(latch_angle);
        latched = true;
       Serial.println("Latched!");
      }
    }
  }
}
