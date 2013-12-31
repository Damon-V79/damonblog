/*
 * Factory.cpp
 *
 *  Created on: 27.11.2013
 *      Author: damon
 */

#include "Factory.h"

unsigned int Stream1::time[] = { 2150, 1100, 550, 300, 170, 100, 8450, 4250 }; // For 10kHz PWM
unsigned int Stream1::times = sizeof(time) / sizeof(unsigned int);

PortA portA;

// Motors support devise
Stream1 pwmClock;
Stream2 pwmStream;
Factory::PWMDMA_t pwmDMA(pwmStream, portA);

Factory::Factory() :
		_pwm(pwmDMA) {
	// configure IO pins
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_168MHZ]);

	/* Enable GPIOx clock. */
	rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_IOPAEN);
//	/* Enable DMA clock. */RCC_AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	// PWM DMA pins
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1 | GPIO3);

	PWMSetup();
}

Factory::~Factory() {
	// TODO Auto-generated destructor stub
}

void Factory::PWMSetup() {
	timer_reset(TIM8);

	// Setup Timer 8
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_TIM8EN);
	timer_reset(TIM8);
	timer_set_prescaler(TIM8, 0); 	// TIM8_PSC = 0;
	timer_set_period(TIM8, 4250); 	// TIM8_ARR = 4250;
	timer_set_counter(TIM8, 8450);	// TIM8_CNT = 8450;
	timer_enable_preload(TIM8);		// TIM8_CR1 |= TIM_CR1_ARPE;

	timer_set_oc_value(TIM8, TIM_OC1, 0);

	timer_enable_update_event(TIM8);
	timer_enable_irq(TIM8, TIM_DIER_UDE | TIM_DIER_CC1DE); // TIM8_DIER = TIM_DIER_UDE | TIM_DIER_CC1DE;

	pwmDMA.Enable();
	pwmClock.Enable();

	timer_enable_counter(TIM8);
}
