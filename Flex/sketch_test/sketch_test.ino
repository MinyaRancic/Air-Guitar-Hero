/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

// Selecting the inputs for the flex senors, labelling them according to finger. 1 is index, 2 is middle, etc...
int finger1 = A0;
int finger2 = A1;
int finger3 = A2;
int finger4 = A3;
// Variables to store the read values from the fingers
int f1Value = 0;
int f2Value = 0;
int f3Value = 0;
int f4Value = 0;

void setup() {
  // nothing happens in setup
  Serial.begin(9600);
}

void loop() {
  int fingerTotal = B0;
  f1Value = analogRead(finger1);
  f2Value = analogRead(finger2);
  f3Value = analogRead(finger3);
  f4Value = analogRead(finger4);
  if(f1Value<=16) {
    fingerTotal = fingerTotal | 1;
  }
  if(f2Value<=16) {
    fingerTotal = fingerTotal | 2;
  }
  if(f3Value<=16) {
    fingerTotal = fingerTotal | 4;
  }
  if(f4Value<=16) {
    fingerTotal = fingerTotal | 8;
  }
  Serial.println(fingerTotal);
  delay(1);
}
