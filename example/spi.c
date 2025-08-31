#include "main.h"

static void SPI_SendCommand(SPI_TypeDef *SPIx, uint8_t data)
{
    CS_ON();
    SPI_TransmitReceive(SPIx, data);
    CS_OFF();
}

int main(void)
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    SysTick_Init();
    SPI_Config(SPI1);

    while (1)
    {
        SPI_SendCommand(SPI1, 0xA3);
        DelayMs(1000);
    }
}