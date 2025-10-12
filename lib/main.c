#include <stdio.h>
#include "../include/usart.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/irq.h"

#define RX_BUFFER_SIZE    128

RCC_REG *RCC = (RCC_REG *)(RCC_BASE);
// GPIO_REG *GPIOA = (GPIO_REG *)(GPIOA_BASE);
GPIO_REG *GPIOB = (GPIO_REG *)(GPIOB_BASE);
USART_REG *USART1 = (USART_REG *)(USART1_BASE);

uint8_t tx_buffer[] = "AT\r\n";


uint8_t rx_buffer[RX_BUFFER_SIZE];
uint32_t rx_head = 0;

extern void initialise_monitor_handles(void);

/* USART */
void USART_Init(USART_REG *USARTx)
{
    // Disable USART
    USARTx->CR1 &= ~USART_CR1_UE;

    // set data bits to 8 bits 
    // 00 = 8 bits, 01 = 9 bits, 10 = 7 bits
    USARTx->CR1 &= ~USART_CR1_M;

    // select 1 stop bit 
    // 00 = 1 stop bit          01 = 0.5 stop bit
    // 10 = 2 stop bits         11 = 1.5 stop bit
    USARTx->CR2 &= ~USART_CR2_STOPBITS_1;

    // set parity control to no parity
    // 0 = no parity
    // 1 = parity enabled (then program PS bit to select even or odd parity)
    USARTx->CR1 &= ~USART_CR1_PCE;

    // oversampling by 16
    // 0 = oversampling by 16, 1 = oversampling by 8
    USARTx->CR1 &= ~USART_CR1_OVER8;

    // set baud rate to 115200 using APB frequency of 16 MHZ
    USARTx->BRR = 0x08B;

    // enable transmissin and reception
    USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    // enable usart
    USARTx->CR1 |= USART_CR1_UE;

    // enable usart rx interrupt
    USARTx->CR1 |= USART_CR1_RXNEIE;
}

/* this was used for polling */
// void USART_Read(USART_REG *USARTx, uint8_t *buffer, uint32_t nBytes)
// {   
//     int i;

//     for(i = 0; i < nBytes; i++)
//     {
//         while (!(USARTx->SR & USART_SR_RXNE));
//         buffer[i] = USARTx->DR;
//     }
// }

void USART_Write(USART_REG *USARTx, uint8_t *buffer, uint32_t nBytes)
{
    int i;

    for(i = 0; i < nBytes; i++)
    {
        while(!(USARTx->SR & USART_SR_TXE));
        USARTx->DR = buffer[i] & 0xFF;
    }

    while(!(USARTx->SR & USART_SR_TC));
}

/* Interrupts */
void enable_interrupt(uint32_t IRQn)
{
    uint32_t word_offset = IRQn >> 5; /* this equal to dividing by 32 to get the register number */
    uint32_t bit_offset = IRQn & 0x1F; /* this is equal to IRQn % 32 */
    NVIC_ISER_BASE[word_offset] = 1 << bit_offset;
} 

/* USART1_IRQHandler overrides the weak definition in the startup_code file. The linker takes care of
   putting it in the vector table. */
void USART1_IRQHandler(void)
{   
    /* USART1 IRQ can be triggered by other flags, hence we check the appropriate flag. in this 
       case RXNE since we want to interrupt the CPU each time data arrives. */
    // printf("Reached here!\n");
    if(USART1->SR & USART_SR_RXNE)
    {
        rx_buffer[rx_head++] = USART1->DR;
        if(rx_head >= RX_BUFFER_SIZE) rx_head = 0;
    }
    
}

int main(void)
{
    /* Enable GPIO port A clock */
    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Enable GPIO port B clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* 10 = alernate function for PA9 & PA10 */
    // GPIOA->MODER &= ~((3 << 18) | (3 << 20));
    // GPIOA->MODER |= ((2 << 18) | (2 << 20));

    /* 10 = alternate function for PB6 & PB7
    PB6=TX, PB7=RX */
    GPIOB->MODER &= ~((3 << 12) | (3 << 14));
    GPIOB->MODER |= ((2 << 12) | (2 << 14));

    /* set PA9 & PA10 to AF7 for USART1 */
    // GPIOA->AFRH &= ~((0xF << 4) | (0xF << 8));
    // GPIOA->AFRH |= ((7 << 4) | (7 << 8));

    /* set PB6 & PB7 to AF7 for USART1 */
    GPIOB->AFRL &= ~((0xF << 24) | (0xF << 28));
    GPIOB->AFRL |= ((7 << 24) | (7 << 28));

    /* PB9 & PB10 set to speed 11, very high speed */
    // GPIOA->OSPEEDR |= 0xF << (2 * 9); /* this is same as GPIO->OSPEEDR |= (3 << 18) | (3 <<20) */

    /* PB6 & PB7 set to speed 11, very high speed */
    GPIOB->OSPEEDR |= 0xF << (2 * 6);

    /* PA9 & PA10 pull-up/pull-down, pull-up selected */
    // GPIOA->PUPDR &= ~(0xF << (2 * 9));
    // GPIOA->PUPDR |= (0x5 | (2 * 9));

    /* PB6 & PB7 pull-up/pull-down, pull-up selected */
    GPIOB->PUPDR &= ~(0xF << 2 * 6);
    GPIOB->PUPDR |= (0x5 << 2 * 6);

    /* PA9 & PA10 push-pull, open-drain. push-pull selected */
    // GPIOA->OTYPER &= ~(0x3 << 9);

    /* PB6 & PB7 push-pull, open-drain. push-pull selected */
    GPIOB->OTYPER &= ~(0x3 << 6);

    /* enable USART1 clock */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    /* disable printf buffering. \n fixes prints buffer issues */
    // setbuf(stdout, NULL);

    USART_Init(USART1);

    // enable usart1 NVIC interrupt
    enable_interrupt(37);

    // enable semi-hosting
    initialise_monitor_handles();

    printf("You sent: %s\n", tx_buffer);

    USART_Write(USART1, tx_buffer, sizeof(tx_buffer) - 1);

    // USART_Read(USART1, rx_buffer, sizeof(rx_buffer) - 1);

    // while((rx_head == 0) || (rx_head < 10))
    // {
    //     printf("No data yet!\n");
    // }    

    // printf("rx_head: %ld\n", rx_head);


    while (1)
    {
        // check if any bytes have been received
        if (rx_head > 0)
        {
            // scan received bytes for 'K'
            for (int i = 0; i < rx_head; i++)
            {
                if (rx_buffer[i] == 'K')
                {
                    printf("Found 'K' at position %d!\n", i);
                    printf("AT command response from SIMCOM7600NA: %s\n", rx_buffer);
                    
                    // optionally reset rx_head or mark processed
                    rx_head = 0;  // clear buffer
                    break;
                }
            }
        }
    }


    return 0;
}