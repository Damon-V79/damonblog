/*
 * DMAStreams.h
 *
 *  Created on: 27.11.2013
 *      Author: damon
 */

#ifndef DMASTREAMS_H_
#define DMASTREAMS_H_

extern "C" {
#include <libopencm3/stm32/f4/rcc.h>
#include <libopencm3/stm32/f4/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
}

class Stream1 {
public:
	typedef enum {
		MemToPeripheral = 0, PeripheralToMem, MemToMem
	} Direction_e;

	Stream1() {
		/* Enable DMA clock. */RCC_AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	}
	void Enable() {
		// DMA2 stream 1 channel 7 is triggered by timer 8.
		// Stop it and configure interrupts.
		Disable();

		// Configure DMA.
		DMA2_S1CR = (DMA_SxCR_CHSEL_7) | // Channel 7
				(DMA_SxCR_PL_VERY_HIGH) | // Priority 3
				(DMA_SxCR_PSIZE_32BIT) | // PSIZE = 16 bit
				(DMA_SxCR_MSIZE_32BIT) | // MSIZE = 32 bit
				DMA_SxCR_MINC | // Increase memory address
				(DMA_SxCR_DIR_MEM_TO_PERIPHERAL) | // Memory to peripheral
				DMA_SxCR_TCIE | // Transfer complete interrupt
				(DMA_SxCR_MBURST_SINGLE) | // burst on the memory-side
				DMA_SxCR_CIRC;

		DMA2_S1NDTR = Stream1::times;
		DMA2_S1PAR = ((&TIM8_ARR ));
		DMA2_S1M0AR = Stream1::time;
		DMA2_S1CR |= DMA_SxCR_EN;
	}
	void Disable() {
		DMA2_S1CR &= ~DMA_SxCR_EN;
	}
	bool isEnable() {
		return DMA2_S1CR & DMA_SxCR_EN;
	}
	void SetDir(Direction_e) {
	}
	void SetCircularMode(bool) {
	}
	void SetMemoryAddr(unsigned int *) {
	}
	void SetMemorySize(unsigned int) {
	}
	void MemoryIncrement(bool) {
	}
	void SetPeripheralAddr(unsigned int *) {
	}
	void SetPeripheralSize(unsigned int) {
	}
	void PeripheralIncrement(bool) {
	}
	void DisableInterrupt() {
		nvic_disable_irq(NVIC_DMA2_STREAM1_IRQ);
	}
	void EnableInterrupt() {
		nvic_enable_irq(NVIC_DMA2_STREAM1_IRQ);
	}
	static unsigned int time[];
	static unsigned int times;

};

// TIM8_ARR = 4250; // Initial Timer8 value
// TIM8_CNT = 8450;
// unsigned int Stream1::time[ ] = { 2150, 1100, 550, 300, 170, 100, 8450, 4250 }; // For 10kHz PWM
// unsigned int Stream1::times = sizeof ( time ) / sizeof(unsigned int);

class Stream2 {
public:
	typedef enum {
		MemToPeripheral = 0, PeripheralToMem, MemToMem
	} Direction_e;

	Stream2() {
		/* Enable DMA clock. */RCC_AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	}
	void Enable() {
		// DMA2 stream 2 channel 7 is triggered by timer 8.
		// Stop it and configure interrupts.
		Disable();

		// Configure DMA.
		DMA2_S2CR = (DMA_SxCR_CHSEL_7) | // Channel 7
				(DMA_SxCR_PL_MEDIUM) | // Priority 3
				(DMA_SxCR_PSIZE_32BIT) | // PSIZE = 32 bit
				(DMA_SxCR_MSIZE_32BIT) | // MSIZE = 32 bit
				DMA_SxCR_MINC | // Increase memory address
				(DMA_SxCR_DIR_MEM_TO_PERIPHERAL) | // Memory to peripheral
				DMA_SxCR_TCIE | // Transfer complete interrupt
				(DMA_SxCR_MBURST_SINGLE) | // burst on the memory-side
				DMA_SxCR_CIRC;

		DMA2_S2FCR = DMA_SxFCR_DMDIS | // Enable FIFO.
				(DMA_SxFCR_FTH_1_4_FULL); // Set threshold to 1/2. (TODO: look at this)
		DMA2_S2CR |= DMA_SxCR_EN;
	}
	void Disable() {
		DMA2_S2CR &= ~DMA_SxCR_EN;

	}
	bool isEnable() {
		return DMA2_S2CR & DMA_SxCR_EN;
	}
	void SetDir(Direction_e) {
	}
	void SetCircularMode(bool) {
	}
	void SetMemoryAddr(unsigned int *addr) {
		DMA2_S2M0AR = addr;
	}
	void SetMemorySize(unsigned int size) {
		DMA2_S2NDTR = size;
	}
	void MemoryIncrement(bool) {
	}
	void SetPeripheralAddr(unsigned int *addr) {
		DMA2_S2PAR = addr;
	}
	void SetPeripheralSize(unsigned int) {
	}
	void PeripheralIncrement(bool) {
	}
	void DisableInterrupt() {
		nvic_disable_irq(NVIC_DMA2_STREAM2_IRQ);
	}
	void EnableInterrupt() {
		nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);
	}
};

#endif /* DMASTREAMS_H_ */
