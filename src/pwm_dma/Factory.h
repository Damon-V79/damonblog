/*
 * Factory.h
 *
 *  Created on: 27.11.2013
 *      Author: damon
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "DMAStreams.h"
#include "Ports.h"
#include <STM32F4/PWMDMAOut.h>

class Factory {
public:
  // PWM types
  typedef PWMDMAPortOut< Stream2, PortA, 8 > PWMDMA_t;

  Factory( );
  ~Factory( );

  // PWM methods
  PWMDMA_t& PWMPortA() {
	  return _pwm;
  }

private:

  // PWM over DMA data
  PWMDMA_t &_pwm;

  void PWMSetup();

};

#endif /* FACTORY_H_ */
