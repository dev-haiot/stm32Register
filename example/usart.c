#include "main.h"

static USART_HandleTypeDef huart1;
static GPIO_InitTypeDef gpio_cfg;

static void USART_Config(void)
{
    huart1.BaudRate = 115200;
    huart1.WordLength = USART_WORDLENGTH_8B;
    huart1.StopBits = USART_STOPBITS_1;
    huart1.IRQ_Enable = DISABLE;

    USART_Init(USART1, &huart1);
    USART_SetGlobal(USART1);
}

static void GPIO_Config(void)
{
    RCC_APB2ClockCmd(RCC_APB2_GPIOC, ENABLE);

    gpio_cfg.Mode = GPIO_MODE_OP_PP;
    gpio_cfg.Pin = GPIO_PIN_13;
    gpio_cfg.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOC, &gpio_cfg);
}
int main(void)
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    SysTick_Init();
    USART_Config();
    GPIO_Config();

    USART_SendString(USART1, "Hello from USART1\r\n");

    uint32_t last = millis();
    uint16_t counter = 0;

    while (1)
    {
        uint32_t now = millis();
        if ((now - last) >= 500)
        {
            last = now;
            ++counter;
            USART_Printf("counter=%u\r\n", (unsigned int)counter);

            if (counter % 17 == 0)
            {
                GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                USART_SendString(USART1, "Dao trang thai Led thanh cong!\r\n");
            }
            else if (counter == 105)
            {
                USART_Printf("-------- Tinh Yeu Ngot Ngao Cung Tan Thoi --------");
            }
        }
    }
}