#ifndef IRQ_H
#define IRQ_H

/* NVIC Peripheral base address */
#define NVIC_BASE       0xE000E100U

#define NVIC_ISER_BASE  ((volatile uint32_t*)(NVIC_BASE + 0x000))
#define NVIC_ICER_BASE  ((volatile uint32_t*)(NVIC_BASE + 0x080))
#define NVIC_ISPR_BASE  ((volatile uint32_t*)(NVIC_BASE + 0x100))
#define NVIC_ICPR_BASE  ((volatile uint32_t*)(NVIC_BASE + 0x180))
#define NVIC_IABR_BASE  ((volatile uint32_t*)(NVIC_BASE + 0x200))
#define NVIC_IPR_BASE   ((volatile uint8_t*)(NVIC_BASE + 0x300))

void enable_interrupt(uint32_t IRQn);

#endif