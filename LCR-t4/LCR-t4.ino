/*

  HelloWorld.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.

*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
//U8G2_NULL u8g2(U8G2_R0);	// null device, a 8x8 pixel display which does nothing
U8G2_ST7565_LX12864_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 2, /* data=*/3, /* cs=*/ 4, /* dc=*/ 1, /* reset=*/ 0);

// End of constructor list


void setup(void) {
  u8g2.begin();
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  //digitalWrite(PB2,HIGH);
}

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
  //u8g2.drawBox(0,0,200,120);
  //u8g2.sendBuffer();					// transfer internal memory to the display
  if (analogRead(0) > 512)
  {
    for (int w = 0; w < 128; w += 8) {
      for (int h = 0; h < 64; h += 8)
      {
        u8g2.drawPixel(w, h);
      }
    }
  }
  else if (analogRead(2) > 512)
  {
    for (int w = 0; w < 128; w ++) {
      for (int h = 0; h < 64; h ++)
      {
        u8g2.drawPixel(w, h);
      }
    }
  }
  else
  {
    for (int w = 0; w < 128; w +=4) {
      for (int h = 0; h < 64; h +=4)
      {
        u8g2.drawPixel(w, h);
      }
    }
  }
  u8g2.sendBuffer();
  delay(70);
  u8g2.clearDisplay();
  delay(200);
}
