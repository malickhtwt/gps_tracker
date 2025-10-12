#ifndef USART_H
#define USART_H

#include <stdint.h>
#include "common.h"

/* APB2 */ 
#define USART1_BASE 					(PERIPH_BASE_APB2 + 0x1000)

/* the below approach can be used to set register contents rather than struct 
that is how libopencm3 does it */
// #define USART_CR1 						(USART1_BASE + 0x0C)
// #define USART_CR2 						(USART1_BASE + 0x10)
// #define USART_BRR						(USART1_BASE + 0x08)

/* USART registers */
typedef struct {
    _VO uint32_t SR;
    _VO uint32_t DR;
    _VO uint32_t BRR;
    _VO uint32_t CR1;
    _VO uint32_t CR2;
    _VO uint32_t CR3;
    _VO uint32_t GTPR;
} USART_REG;

/* STOP: set stop bits */
#define USART_CR2_STOPBITS_1            (0x00 << 12)    
#define USART_CR2_STOPBITS_0_5          (0x01 << 12)    
#define USART_CR2_STOPBITS_2            (0x02 << 12)     
#define USART_CR2_STOPBITS_1_5          (0x03 << 12)     
#define USART_CR2_STOPBITS_MASK         (0x03 << 12)
#define USART_CR2_STOPBITS_SHIFT        12

/* M: Word length */
#define USART_CR1_M                     (1 << 12)

/* UE: usart enable */
#define USART_CR1_UE					(1 << 13)

/* PCE: parity control enable */
#define USART_CR1_PCE					(1 << 10)

/* OVER8: oversampling mode */
#define USART_CR1_OVER8					(1 << 15)

/* TE: transmission enable */
#define USART_CR1_TE					(1 << 3)

/* RE: reception enable */
#define USART_CR1_RE					(1 << 2)

/* RXNEIE: enable RXNE interrupt (RX not empty) */
#define USART_CR1_RXNEIE                (1 << 5)

/* RXNE: if this bit is 1, DR is empty */
#define USART_SR_RXNE					(1 << 5)

/* TXE: if this bit is 1, DR is empty, 
data is transferred to the shift register */
#define USART_SR_TXE					(1 << 7)

/* TC: Transmission complete */
#define USART_SR_TC						(1 << 6)

int main();
void USART_Init(USART_REG *USARTx);
void USART_Read(USART_REG *USARTx, uint8_t *buffer, uint32_t nBytes);
void USART_Write(USART_REG *USARTx, uint8_t *buffer, uint32_t nBytes);

#endif