#include "spi.h"
#include "rcc.h"
#include "gpio.h"

void SPI_Config(SPI_TypeDef *SPIx)
{
    GPIO_InitTypeDef gpio = {0};
    SPI_InitTypeDef spi = {0};

    if (SPIx == SPI1)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOA | RCC_APB2_SPI1, ENABLE);

        gpio.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOA, &gpio);

        gpio.Pin = GPIO_PIN_6;
        gpio.Mode = GPIO_MODE_INPUT_FLOATING;
        GPIO_Init(GPIOA, &gpio);

        gpio.Pin = CS_PIN;
        gpio.Mode = GPIO_MODE_OP_PP;
        gpio.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(CS_PORT, &gpio);
    }
    else if (SPIx == SPI2)
    {
        RCC_APB1ClockCmd(RCC_APB1_SPI2, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

        gpio.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        gpio.Mode = GPIO_MODE_AF_PP;
        gpio.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &gpio);

        gpio.Pin = GPIO_PIN_14;
        gpio.Mode = GPIO_MODE_INPUT_FLOATING;
        GPIO_Init(GPIOB, &gpio);

        gpio.Pin = GPIO_PIN_12;
        gpio.Mode = GPIO_MODE_OP_PP;
        gpio.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &gpio);
    }
    else
    {
        return;
    }

    spi.Mode = SPI_MODE_MASTER;
    spi.BaudRate = SPI_BAUD_128;
    spi.CPHA = SPI_CPHA_1Edge;
    spi.CPOL = SPI_CPOL_LOW;
    spi.SS = SPI_SSM_SSI_ENABLE_MASK;
    spi.DataSize = SPI_DATASIZE_8BIT;
    spi.Direction = SPI_DIRECTION_FULL_DUPLEX;
    spi.FirstBit = SPI_FIRSTBIT_MSB;
    SPI_Init(SPIx, &spi);
}

void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState state)
{
    if (SPIx == NULL)
        return;

    if (state == ENABLE)
    {
        SPIx->CR1 |= SPI_CR1_SPE_ENABLE;
    }
    else
    {
        SPIx->CR1 &= ~SPI_CR1_SPE_ENABLE;
    }
}
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint32_t SPI_FLAG)
{
    if (SPIx == NULL)
        return RESET;
    if (SPIx->SR & SPI_FLAG)
        return SET;
    return RESET;
}
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
    if (SPIx == NULL || SPI_InitStruct == NULL)
    {
        return;
    }

    SPIx->CR1 = 0;

    SPIx->CR1 |= SPI_InitStruct->Mode |
                 SPI_InitStruct->BaudRate |
                 SPI_InitStruct->SS |
                 SPI_InitStruct->CPOL |
                 SPI_InitStruct->CPHA |
                 SPI_InitStruct->FirstBit |
                 SPI_InitStruct->DataSize |
                 SPI_InitStruct->Direction;

    SPI_Cmd(SPIx, ENABLE);
}
inline void SPI_TransmitData(SPI_TypeDef *SPIx, uint8_t u8data)
{
    if (SPIx == NULL)
        return;

    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_TXE) == RESET)
        ;
    *((volatile uint8_t *)&SPIx->DR) = u8data;
    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_BSY) == SET)
        ;
}
inline uint8_t SPI_ReceiveData(SPI_TypeDef *SPIx)
{
    if (SPIx == NULL)
        return 0;

    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_RXNE) == RESET)
        ;
    return *((volatile uint8_t *)&SPIx->DR);
}
inline uint8_t SPI_TransmitReceive(SPI_TypeDef *SPIx, uint8_t u8data)
{
    if (SPIx == NULL)
        return 0;

    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_TXE) == RESET)
        ;
    *((volatile uint8_t *)&SPIx->DR) = u8data;
    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_RXNE) == RESET)
        ;
    while (SPI_GetFlagStatus(SPIx, SPI_FLAG_BSY) == SET)
        ;
    return *((volatile uint8_t *)&SPIx->DR);
}

inline void SPI_SendCmd(SPI_TypeDef *SPIx, uint8_t command)
{
    CS_ON();
    SPI_TransmitReceive(SPIx, command);
    CS_OFF();
}