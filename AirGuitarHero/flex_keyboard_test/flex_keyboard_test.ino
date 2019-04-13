/* Arduino USB HID Keyboard Demo
 * Random Key/Random Delay
 */
const int index_finger = 0;
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
  resistor_two = analogRead(1);
  resistor_three = analogRead(2);
  delay(20);
dddd  if (resistor_reading < lower_avg) {
    buf[3] = 4;    // Random character
  }
  if(resistor_two < lower_avg) {
    buf[2] = 0x16; // S
  }
  if(resistor_three < lower_avg) {
    buf[4] = 7; // S
  }
  Serial.write(buf, 8); // Send keypress

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

void releaseKey(int finger) 
{
  buf[finger] = 0;
  Serial.write(buf, 8); // Release key  
}
