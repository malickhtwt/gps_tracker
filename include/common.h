#ifndef COMMON_H
#define COMMON_H

/* bus memory map */
#define PERIPH_BASE  					0x40000000U
#define PERIPH_BASE_APB2                (PERIPH_BASE + 0x10000)
#define PERIPH_BASE_AHB1				(PERIPH_BASE + 0x20000)
#define _VO								volatile

#endif