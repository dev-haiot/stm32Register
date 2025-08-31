#include "main.h"

static void USART_Config(void)
{
    USART_HandleTypeDef huart1;
    huart1.BaudRate = 57600;
    huart1.WordLength = USART_WORDLENGTH_8B;
    huart1.StopBits = USART_STOPBITS_1;
    huart1.IRQ_Enable = DISABLE;

    USART_Init(USART1, &huart1);
    USART_SetGlobal(USART1);
}

int main(void)
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    SysTick_Init();
    USART_Config();

    USART_Printf("USART ready\r\n");
    const uint8_t banner[] = "USART DMA ready\r\n";
    USART_SendDMA(USART1, banner, sizeof(banner) - 1);

    uint32_t last = millis();

    while (1)
    {
        if ((millis() - last) >= 1000)
        {
            last = millis();

            const uint8_t rxBuff[] = "____ Chao Mung Ngay Quoc Khanh - 2/9/2025 ____\r\n";
            USART_SendDMA(USART1, rxBuff, sizeof(rxBuff) - 1);
        }
    }

    return 0;
}