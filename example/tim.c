#include "main.h"

static void GPIO_Config(void)
{
    RCC_APB2ClockCmd(RCC_APB2_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio;
    gpio.Mode = GPIO_MODE_OP_PP;
    gpio.Pin = GPIO_PIN_13;
    gpio.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOC, &gpio);
}
int main()
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    TIM_DelayInit();
    GPIO_Config();
    while (1)
    {
        GPIO_WritePin(GPIOC, GPIO_PIN_13, BIT_RESET);
        delay_ms(1000);
        GPIO_WritePin(GPIOC, GPIO_PIN_13, BIT_SET);
        delay_ms(1000);
    }
}