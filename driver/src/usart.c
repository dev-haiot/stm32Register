#include "stm32f1xx_system.h"
#include "gpio.h"
#include "usart.h"
#include "rcc.h"
#include "exti.h"
#include <stdarg.h>
#include "dma.h"

static uint16_t USART_GetBaudRate(uint32_t u32pclk, uint32_t u32baudrate)
{
    if (u32baudrate == 0 || u32pclk == 0)
        return 0;

    uint32_t denom = 16U * u32baudrate;
    uint32_t mantissa = u32pclk / denom;
    uint32_t rem = u32pclk % denom;

    uint32_t fraction = (rem * 16U + denom / 2U) / denom;

    if (fraction >= 16U)
    {
        mantissa += 1U;
        fraction = 0U;
    }

    uint32_t brr = (mantissa << 4) | (fraction & 0xFU);
    return (uint16_t)(brr & 0xFFFFU);
}

static void USART_GPIO_Config(USART_TypeDef *USARTx)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (USARTx == USART1)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_IPU;
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (USARTx == USART2)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_IPU;
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (USARTx == USART3)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Mode = GPIO_MODE_IPU;
        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

FlagStatus USART_GetFlagStatus(USART_TypeDef *USARTx, uint32_t USART_FLAG)
{
    if (USARTx == 0)
        return RESET;

    if (USARTx->SR & USART_FLAG)
        return SET;

    return RESET;
}

void USART_Init(USART_TypeDef *USARTx, USART_HandleTypeDef *USART_InitStruct)
{
    if (USART_InitStruct == NULL)
    {
        return;
    }

    if (USARTx == USART1)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOA | RCC_APB2_USART1, ENABLE);
    }
    else if (USARTx == USART2)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART2, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOA, ENABLE);
    }
    else if (USARTx == USART3)
    {
        RCC_APB1ClockCmd(RCC_APB1_USART3, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);
    }
    else
    {
        return;
    }
    USART_GPIO_Config(USARTx);

    if (USARTx == USART1)
    {
        if (USART_InitStruct->BaudRate != 0)
            USARTx->BRR = USART_GetBaudRate(SystemCoreClock_72MHz, USART_InitStruct->BaudRate);
    }
    else
    {
        if (USART_InitStruct->BaudRate != 0)
            USARTx->BRR = USART_GetBaudRate(SystemCoreClock_36MHz, USART_InitStruct->BaudRate);
    }

    USARTx->CR1 &= ~USART_CR1_UE;

    /* Clear parity control and word length bits */
    USARTx->CR1 &= ~(USART_CR1_PCE | USART_CR1_M);

    /* Configure stop bits: clear STOP bits then set desired value */
    USARTx->CR2 &= ~(3U << 12);
    if (USART_InitStruct->StopBits == USART_STOPBITS_2)
    {
        USARTx->CR2 |= USART_CR2_STOP_2;
    }

    /* Enable transmitter and receiver */
    USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    /* Configure IRQ if requested */
    if (USART_InitStruct->IRQ_Enable == ENABLE)
    {
        USARTx->CR1 |= USART_CR1_IRQ_MASK;

        if (USARTx == USART1)
        {
            NVIC_EnableIRQ(USART1_IRQn);
        }
        else if (USARTx == USART2)
        {
            NVIC_EnableIRQ(USART2_IRQn);
        }
        else if (USARTx == USART3)
        {
            NVIC_EnableIRQ(USART3_IRQn);
        }
    }

    /* Finally enable USART (UE) */
    USARTx->CR1 |= USART_CR1_UE;
}

void USART_SendChar(USART_TypeDef *USARTx, char c)
{
    while (USART_GetFlagStatus(USARTx, USART_SR_TXE) == RESET)
    {
    }
    USARTx->DR = c;
}
void USART_SendString(USART_TypeDef *USARTx, const char *str)
{
    while (*str)
    {
        USART_SendChar(USARTx, *str++);
    }
}

/* Global USART instance and helper functions */
USART_TypeDef *USART_Global = USART1;

void USART_SetGlobal(USART_TypeDef *USARTx)
{
    if (USARTx != 0)
        USART_Global = USARTx;
}

/* Minimal integer to string converter (unsigned) */
static int uint_to_str(unsigned int val, unsigned int base, char *out, int out_size, int lowercase)
{
    char tmp[32];
    const char *digits = lowercase ? "0123456789abcdef" : "0123456789ABCDEF";
    int pos = 0;

    if (val == 0)
    {
        if (out_size > 1)
            out[0] = '0';
        return 1;
    }

    while (val && pos < (int)sizeof(tmp))
    {
        tmp[pos++] = digits[val % base];
        val /= base;
    }

    int len = 0;
    for (int i = pos - 1; i >= 0; --i)
    {
        if (len < out_size - 1)
            out[len] = tmp[i];
        ++len;
    }

    return len;
}

/* Minimal vsnprintf-like formatter supporting %s %c %d %i %u %x %X %% */
static int tiny_vsnprintf(char *buf, int buf_size, const char *fmt, va_list ap)
{
    int idx = 0;
    const char *p = fmt;

    while (*p)
    {
        if (*p != '%')
        {
            if (idx < buf_size - 1)
                buf[idx] = *p;
            ++idx;
            ++p;
            continue;
        }

        ++p; /* skip '%' */
        if (*p == '%')
        {
            if (idx < buf_size - 1)
                buf[idx] = '%';
            ++idx;
            ++p;
            continue;
        }

        switch (*p)
        {
        case 'c':
        {
            char c = (char)va_arg(ap, int);
            if (idx < buf_size - 1)
                buf[idx] = c;
            ++idx;
            break;
        }
        case 's':
        {
            const char *s = va_arg(ap, const char *);
            if (s == 0)
                s = "(null)";
            while (*s)
            {
                if (idx < buf_size - 1)
                    buf[idx] = *s;
                ++idx;
                ++s;
            }
            break;
        }
        case 'd':
        case 'i':
        {
            int v = va_arg(ap, int);
            unsigned int u = (v < 0) ? (unsigned int)(-v) : (unsigned int)v;
            char tmp[32];
            int write = 0;
            if (v < 0)
            {
                if (idx < buf_size - 1)
                    buf[idx] = '-';
                ++idx;
            }
            write = uint_to_str(u, 10, tmp, sizeof(tmp), 1);
            for (int i = 0; i < write; ++i)
            {
                if (idx < buf_size - 1)
                    buf[idx] = tmp[i];
                ++idx;
            }
            break;
        }
        case 'u':
        {
            unsigned int v = va_arg(ap, unsigned int);
            char tmp[32];
            int write = uint_to_str(v, 10, tmp, sizeof(tmp), 1);
            for (int i = 0; i < write; ++i)
            {
                if (idx < buf_size - 1)
                    buf[idx] = tmp[i];
                ++idx;
            }
            break;
        }
        case 'x':
        case 'X':
        {
            unsigned int v = va_arg(ap, unsigned int);
            char tmp[32];
            int write = uint_to_str(v, 16, tmp, sizeof(tmp), (*p == 'x'));
            for (int i = 0; i < write; ++i)
            {
                if (idx < buf_size - 1)
                    buf[idx] = tmp[i];
                ++idx;
            }
            break;
        }
        default:
            /* unsupported specifier: ignore */
            break;
        }

        ++p;
    }

    if (buf_size > 0)
    {
        if (idx >= buf_size)
            idx = buf_size - 1;
        buf[idx] = '\0';
    }

    return idx;
}

int USART_Printf(const char *fmt, ...)
{
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    int n = tiny_vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    if (n > 0)
    {
        USART_SendString(USART_Global, buf);
    }

    return n;
}

/* Blocking DMA send for USART (uses DMA1 Channel4 for USART1 TX)
 * Assumptions:
 *  - Only USART1 is supported for now.
 *  - Caller provides valid buffer and len > 0.
 */
void USART_SendDMA(USART_TypeDef *USARTx, const uint8_t *buf, uint32_t len)
{
    if (USARTx == 0 || buf == 0 || len == 0)
        return;

    /* Only implement for USART1 for now */
    if (USARTx != USART1)
        return;

    /* Enable DMA1 clock */
    DMA_ClockEnable(DMA1);

    DMA_InitTypeDef dma_cfg;
    dma_cfg.PeripheralBaseAddr = (uint32_t)&(USART1->DR);
    dma_cfg.MemoryBaseAddr = (uint32_t)buf;
    dma_cfg.DIR = DMA_DIR_M2P; /* memory to peripheral */
    dma_cfg.BufferSize = len;
    dma_cfg.PeripheralInc = DMA_INC_DISABLE;
    dma_cfg.MemoryInc = DMA_INC_ENABLE;
    dma_cfg.PeripheralDataSize = DMA_DATASIZE_8BIT;
    dma_cfg.MemoryDataSize = DMA_DATASIZE_8BIT;
    dma_cfg.Mode = DMA_MODE_NORMAL;
    dma_cfg.Priority = DMA_PRIORITY_MEDIUM;
    dma_cfg.M2M = DMA_M2M_DISABLE;

    /* Channel mapping: STM32F1xx - USART1_TX -> DMA1 Channel4 */
    const uint8_t channel = DMA_CHANNEL4;

    /* Init DMA channel */
    DMA_Init(DMA1, channel, &dma_cfg);

    /* Enable USART DMA transmitter */
    USARTx->CR3 |= USART_CR3_DMAT;

    /* Enable DMA channel */
    DMA_Enable(DMA1, channel);

    /* Wait for transfer complete by polling ISR TCIF flag for the channel */
    uint32_t tc_mask = DMA_ISR_TCIF(channel);
    while ((DMA1->ISR & tc_mask) == 0)
    {
        /* busy wait */
    }

    /* Clear interrupt flag by writing to IFCR */
    DMA1->IFCR = tc_mask | DMA_ISR_GIF(channel); /* clear global & tc */

    /* Disable DMA channel */
    DMA_Disable(DMA1, channel);

    /* Disable USART DMA transmitter if not needed continuously */
    USARTx->CR3 &= ~USART_CR3_DMAT;
}