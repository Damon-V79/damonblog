/*
 * Ports.h
 *
 *  Created on: 27.11.2013
 *      Author: damon
 */

#ifndef PORTS_H_
#define PORTS_H_

extern "C" {
#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/gpio.h>
#include <libopencm3/stm32/f4/dma.h>
#include <libopencm3/stm32/f4/memorymap.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/f4/nvic.h>
#include <libopencm3/stm32/timer.h>
}

struct PortA {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOA_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOA_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOA_BSRR;
  }
};

struct PortB {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOB_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOB_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOB_BSRR;
  }
};

struct PortC {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOC_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOC_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOC_BSRR;
  }
};

struct PortD {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOD_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOD_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOD_BSRR;
  }
};

struct PortE {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOE_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOE_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOE_BSRR;
  }
};

struct PortF {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOF_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOF_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOF_BSRR;
  }
};

struct PortG {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOG_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOG_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOG_BSRR;
  }
};

struct PortH {
  unsigned int * GetInputDataReg() {
    return (unsigned int *) &GPIOH_IDR;
  }
  unsigned int * GetOutputDataReg() {
    return (unsigned int *) &GPIOH_ODR;
  }
  unsigned int * GetBitSetResetReg() {
    return (unsigned int *) &GPIOH_BSRR;
  }
};

#endif /* PORTS_H_ */
