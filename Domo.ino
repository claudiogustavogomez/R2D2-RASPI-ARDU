
// Software Serial Sample for Packet Serial
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include <Wire.h>

// Define the slave address of this device.
#define SLAVE_ADDRESS 0x7b

// string to store what the RPi sends
String str_recieved_from_RPi = "";

SoftwareSerial SWSerial(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
Sabertooth ST(128, SWSerial);           // Address 128, and use SWSerial as the serial port.

void setup()
{
  SWSerial.begin(9600);
  ST.autobaud();

  // begin running as an I2C slave on the specified address
  Wire.begin(SLAVE_ADDRESS);
 
  // create event for receiving data
  Wire.onReceive(receiveData);  
}


void loop()
{
  
/*  
  // Ramp from -127 to 127 (full reverse to full forward), waiting 20 ms (1/50th of a second) per value.
  for (power = -127; power <= 127; power ++)
  {
    ST.motor(1, power);
    delay(20);
  }
  
  // Now go back the way we came.
  for (power = 127; power >= -127; power --)
  {
    ST.motor(1, power);
    delay(20);
  }
*/  
}

void receiveData(int byteCount) {
 int power;
  while ( Wire.available()) {
    str_recieved_from_RPi += (char)Wire.read();
  }
 
  // turn on or off the LED
  if (str_recieved_from_RPi == "left") {
      for (power = -127; power <= 127; power ++)
      {
        ST.motor(1, power);
        delay(20);
      }
  }
  if (str_recieved_from_RPi == "right") {
      for (power = 127; power >= -127; power --)
      {
        ST.motor(1, power);
        delay(20);
      }
  }
 
  str_recieved_from_RPi = "";
 
}
