/* 
 * File:   Debug.cpp
 * Author: Cameron
 * 
 * Created on January 9, 2015, 4:09 PM
 */

#include "Debug.h"
#include "Clock.h"
#include <avr/io.h>

#include <CRC8.h>

using namespace AVR;
using namespace ThreePhaseControllerNamespace;
using libCameron::CRC8;

Debug::Printer Debug::SOUT;

static CRC8 CRC;

void Debug::init() {
 UBRR1 = 0;
 
 // Set default
 UCSR1D = 0b00;
 
 // Set default
 UCSR1C = 0b00000110;
 
 // Set default
 UCSR1A = 0b00000000;
 
 // Enable transmitter
 UCSR1B = 0b00001000;
}

void Debug::sendByte(const u1 c) {
 while (!(UCSR1A & (1 << UDRE1)));
 UDR1 = c;
}

u1 nibToHex(u1 const nib) {
 if (nib < 10)
  return '0' + nib;
 if (nib < 16)
  return 'A' - 10 + nib;
 return '*';
}

void Debug::reportU1(const u1 b) {
 CRC << b;
 sendByte(b);
}

void Debug::reportClock() {
 u4 t;
 Clock::readTime(t);
 reportU2(t);
}

void Debug::sendHeader() {
 sendByte(0xff);
 sendByte(0xff);
 sendByte(0xff);
 sendByte(0xee);
 sendByte(0xff);
 CRC.reset();
}

void Debug::sendEnd() {
 sendByte(CRC.getCRC());
}
