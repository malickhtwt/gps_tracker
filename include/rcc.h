#ifndef RCC_H
#define RCC_H

#include "common.h"

/* RCC base address */
#define RCC_BASE			(PERIPH_BASE_AHB1 + 0x3800)

/* RCC registers structure */
typedef struct {
	_VO uint32_t CR;
	_VO uint32_t PLLCFGR;
	_VO uint32_t CFGR;
	_VO uint32_t CIR;
	_VO uint32_t AHB1RSTR;
	_VO uint32_t AHB2RSTR;
	_VO uint32_t AHB3RSTR;
	_VO uint32_t Reserved_0x1C;
	_VO uint32_t APB1RSTR;
	_VO uint32_t APB2RSTR;
	_VO uint32_t Reserved_0x28;
	_VO uint32_t Reserved_0x2C;
	_VO uint32_t AHB1ENR;
	_VO uint32_t AHB2ENR;
	_VO uint32_t AHB3ENR;
	_VO uint32_t Reserved_0x3C;
	_VO uint32_t APB1ENR;
	_VO uint32_t APB2ENR;
	_VO uint32_t Reserved_0x48;
	_VO uint32_t Reserved_0x4C;
	_VO uint32_t AHB1LPENR;
	_VO uint32_t AHB2LPENR;
	_VO uint32_t AHB3LPENR;
	_VO uint32_t Reserved_0x5C;
	_VO uint32_t APB1LPENR;
	_VO uint32_t APB2LPENR;
	_VO uint32_t Reserved_0x68;
	_VO uint32_t Reserved_0x6C;
	_VO uint32_t BDCR;
	_VO uint32_t CSR;
	_VO uint32_t Reserved_0x78;
	_VO uint32_t Reserved_0x7C;
	_VO uint32_t SSCGR;
	_VO uint32_t PLLI2SCFGR;
} RCC_REG;

/* GPIO A enable clock */
#define RCC_AHB1ENR_GPIOAEN				(1 << 0)
#define RCC_AHB1ENR_GPIOBEN				(1 << 1)
#define RCC_APB2ENR_USART1EN			(1 << 4)

#endif