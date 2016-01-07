/* 
 * File:   ThreePhaseController.h
 * Author: Cameron
 *
 * Created on October 22, 2015, 2:21 AM
 */

#ifndef THREEPHASECONTROLLER_H
#define	THREEPHASECONTROLLER_H

#include <AVR++/basicTypes.h>

#include "ThreePhaseDriver.h"
#include <avr/interrupt.h>

using namespace AVR;

ISR(TIMER4_OVF_vect);

class ThreePhaseController {
 static inline void isr();
 friend void TIMER4_OVF_vect();
 
 static u4 drivePhase;
 static s2 driveVelocity;
 static constexpr u1 drivePhaseValueShift = 2;
 
 static bool isForward;
 
 /**
  * 90 degree phase shift
  */
 static constexpr u2 output90DegPhaseShift = ThreePhaseDriver::StepsPerCycle / 4;
 
public:
 static void init();
 
 class Torque {
  bool forward;
  u1 amplitude;
  friend class ThreePhaseController;

 public:
  inline Torque(s2 const t) : forward(t >= 0), amplitude(forward ? t : -t) {};
  inline Torque(const bool fwd, u1 const ampl) : forward(fwd), amplitude(ampl) {};
 };
 
 static void setTorque(const Torque t);
 
 static void updateDriver();
 
 inline static s2 getPosition() {return drivePhase;}
 inline static s1 getVelocity() {return driveVelocity;}

};

#endif	/* THREEPHASECONTROLLER_H */
