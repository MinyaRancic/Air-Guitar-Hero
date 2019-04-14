#include "CurieIMU.h"

int const SI_Pin = 12;
int const Pow_Pin = 13;  

/*bool is_up = false;   // boolean to see if the hand is up or down*/
int strum_index = 0;
const int buffer_len = 20;
float strum_buf[buffer_len];

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  for (int i=0; i < buffer_len; i++)
  {
    strum_buf[i] = 0.0;
  }

  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  pinMode(SI_Pin, OUTPUT);
  pinMode(Pow_Pin, OUTPUT);
  
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
}

void loop() {
  float ax, ay, az;  //scaled accelerometer values

  // read accelerometer measurements from device, scaled to the configured range
  CurieIMU.readAccelerometerScaled(ax, ay, az);

  strum_buf[((strum_index) % buffer_len)] = ax;

  if( abs(ax) + abs(strum_buf[strum_index + (buffer_len/2)]) > 0.3)
  {
    digitalWrite(SI_Pin, HIGH); // Send strum input.
    delay(5);
    digitalWrite(SI_Pin, LOW); // Reset strum input.
    Serial.println("Sending signal!");
  }

  /*
  if(is_up && ax < 0)
  {
    is_up = false;
    digitalWrite(SI_Pin, HIGH); // Send strum input.
    delay(20);
    digitalWrite(SI_Pin, LOW); // Reset strum input.
    Serial.println("Sending signal!");
  } 
  else if(!is_up && ax > 0)
  {
    is_up = true;
    digitalWrite(SI_Pin, HIGH); // Send strum input.
    delay(20);
    digitalWrite(SI_Pin, LOW); // Reset strum input.
    Serial.println("Sending signal!");
  }
  */

  if(((ax > 0.7) && (strum_buf[((strum_index + 1) % buffer_len)] < -0.7)) || 
      ((ax < -0.7) && (strum_buf[((strum_index + 1) % buffer_len)] > 0.7)))
  {
    digitalWrite(Pow_Pin, HIGH); // Send star power input
    delay(5);
    digitalWrite(Pow_Pin, LOW); // Reset star power input.
  }

  // Serial.println(ax);
  
  strum_index = (strum_index + 1) % buffer_len;
}

/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/
