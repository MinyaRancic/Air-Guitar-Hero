#include <Adafruit_Sensor.h>

#include <Adafruit_MMA8451.h>

/* Arduino USB HID Keyboard Demo
 * Random Key/Random Delay
 */

const int index_finger = 0;
const int middle_finger = 1;
const int ring_finger = 2;
const int pinky_finger = 3;
const int strum = 12;
const int star = 13;
const int lower_avg = 13;
const int strum_const = 19;

int resistor_index; 
int resistor_middle;
int resistor_ring;
int resistor_pinky;
int strumVal;
int starVal;
bool upstrum;
bool downstrum;

sensors_event_t event;
Adafruit_MMA8451 mma;

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

void setup() 
{
  upstrum = false;
  downstrum = false;
  Serial.begin(9600);
  pinMode(strum, INPUT);
  delay(100);
  mma = Adafruit_MMA8451();
  delay(1000);

  pinMode(11, OUTPUT);
  
    if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
}

void loop() 
{
  resistor_index = analogRead(index_finger);
  resistor_middle = analogRead(middle_finger);
  resistor_ring = analogRead(ring_finger);
  resistor_pinky = analogRead(pinky_finger);
  mma.getEvent(&event);
  
  delay(20);
  if (resistor_index < lower_avg) {
    buf[3] = 4;    // A, green key
  }
  if(resistor_middle < lower_avg) {
    buf[2] = 0x16; // S, Red key
  }
  if(resistor_ring < lower_avg) {
    buf[4] = 7; // D, Yellow Key
  }
  if(resistor_pinky < lower_avg - 1) {
    buf[5] = 9; // F, Blue Key
  }
  if(!downstrum && (event.acceleration.y > strum_const || event.acceleration.y <= -1*strum_const) ) {
    buf[6] = 0x0f; //l, strum
    downstrum = true;
    Serial.println("strum");
  } 
  
  
  
  Serial.write(buf, 8); // Send keypress

  // Only release key if we go back above the threshold
  if(resistor_index >= lower_avg) {
    releaseKey(3);
  }
  if(resistor_middle >= lower_avg) {
    releaseKey(2);
  }
  if(resistor_ring >= lower_avg) {
    releaseKey(4);
  }
  if(resistor_pinky >= lower_avg) {
    releaseKey(5);
  }
  if(downstrum && (event.acceleration.y <= strum_const && event.acceleration.y >= -1*strum_const) ) {
    releaseKey(6);
    downstrum = false;
  }
}

// writes 0 to the approiate buffer
void releaseKey(int finger) 
{
  buf[finger] = 0;
  buf[0] = 0;
  buf[1] = 0;
  buf[7] = 0;
  Serial.write(buf, 8); // Release key  
}
