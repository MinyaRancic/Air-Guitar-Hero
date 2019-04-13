/* Arduino USB HID Keyboard Demo
 * Random Key/Random Delay
 */
const int index_finger = 0;
const int middle_finger = 1;
const int ring_finger = 2;
const int lower_avg = 15;

int resistor_reading; 
int resistor_two;
int resistor_three;

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

void setup() 
{
  Serial.begin(9600);
  delay(100);
}

void loop() 
{
  resistor_reading = analogRead(index_finger);
  resistor_two = analogRead(middle_finger);
  resistor_three = analogRead(ring_finger);
  delay(20);
  if (resistor_reading < lower_avg) {
    buf[3] = 4;    // A, green key
  }
  if(resistor_two < lower_avg) {
    buf[2] = 0x16; // S, Red key
  }
  if(resistor_three < lower_avg) {
    buf[4] = 7; // D, Yellow Key
  }
  Serial.write(buf, 8); // Send keypress

  // Only release key if we go back above the threshold
  if(resistor_reading >= lower_avg) {
    releaseKey(3);
  }
  if(resistor_two >= lower_avg) {
    releaseKey(2);
  }
  if(resistor_three >= lower_avg) {
    releaseKey(4);
  }
}

// writes 0 to the approiate buffer
void releaseKey(int finger) 
{
  buf[finger] = 0;
  Serial.write(buf, 8); // Release key  
}
