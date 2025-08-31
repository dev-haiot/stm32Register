#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_system.h"

/* Control Register 1 (CR1) */
#define USART_CR1_RE (1 << 2)
#define USART_CR1_TE (1 << 3)
#define USART_CR1_RXNEIE (1 << 5)
#define USART_CR1_PCE (1 << 10)
#define USART_CR1_M (1 << 12)
#define USART_CR1_UE (1 << 13)

/* Control Register 3 (CR3) - DMA enable bits */
#define USART_CR3_DMAR (1 << 6) /* DMA enable receiver */
#define USART_CR3_DMAT (1 << 7) /* DMA enable transmitter */

/* Control Register 1 (CR2) */
#define USART_CR2_STOP_1 (0 << 12)
#define USART_CR2_STOP_2 (2 << 12)

/* Status Register (SR) */
#define USART_SR_RXNE (1 << 5)
#define USART_SR_TC (1 << 6)
#define USART_SR_TXE (1 << 7)

/* clearer aliases (recommended) */
#define USART_BAUD_4800 USART_BRR_4800
#define USART_BAUD_9600 USART_BRR_9600
#define USART_BAUD_14400 USART_BRR_14400
#define USART_BAUD_19200 USART_BRR_19200
#define USART_BAUD_38400 USART_BRR_38400
#define USART_BAUD_57600 USART_BRR_57600
#define USART_BAUD_115200 USART_BRR_115200

/* Word length options for USART_HandleTypeDef->WordLength */
#define USART_WORDLENGTH_8B (0U)
#define USART_WORDLENGTH_9B (1U)

/* Stop bits options (these match the CR2 STOP field encoding) */
#define USART_STOPBITS_1 USART_CR2_STOP_1
#define USART_STOPBITS_2 USART_CR2_STOP_2

/* USART bits mask */
#define USART_CR1_ENABLE_MASK (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE)
#define USART_CR1_IRQ_MASK (USART_CR1_RXNEIE)

    typedef struct
    {
        uint32_t BaudRate;
        uint32_t WordLength;
        uint32_t StopBits;
        FunctionalState IRQ_Enable;
    } USART_HandleTypeDef;

    FlagStatus USART_GetFlagStatus(USART_TypeDef *USARTx, uint32_t USART_FLAG);

    extern USART_TypeDef *USART_Global;

    void USART_SetGlobal(USART_TypeDef *USARTx);

    int USART_Printf(const char *fmt, ...);
    void USART_Init(USART_TypeDef *USARTx, USART_HandleTypeDef *USART_InitStruct);
    void USART_SendChar(USART_TypeDef *USARTx, char c);
    void USART_SendString(USART_TypeDef *USARTx, const char *str);

    void USART1_IRQHandler(void);
    void USART2_IRQHandler(void);
    void USART3_IRQHandler(void);

    /* DMA helper: blocking send via DMA (currently supports USART1) */
    void USART_SendDMA(USART_TypeDef *USARTx, const uint8_t *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // USART_H
