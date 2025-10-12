#ifndef GPIO_H
#define GPIO_H

#include "common.h"

#define GPIO_BASE						PERIPH_BASE_AHB1
#define GPIOA_BASE						GPIO_BASE
#define GPIOB_BASE 						(GPIO_BASE + 0x0400)

/* GPIO structure */
typedef struct {
	_VO uint32_t MODER;
	_VO uint32_t OTYPER;
	_VO uint32_t OSPEEDR;
	_VO uint32_t PUPDR;
	_VO uint32_t IDR;
	_VO uint32_t ODR;
	_VO uint32_t BSRR;
	_VO uint32_t LCKR;
	_VO uint32_t AFRL;
	_VO uint32_t AFRH;
} GPIO_REG;


#endif