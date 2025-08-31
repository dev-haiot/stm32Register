#include "exti.h"

int8_t Get_Pin_Number(uint16_t GPIO_Pin)
{
    uint8_t u8cnt;
    for (u8cnt = 0; u8cnt < 16; u8cnt++)
    {
        if (GPIO_Pin & (1 << u8cnt))
        {
            return u8cnt;
        }
    }
    return -1;
}
int8_t Get_EXTI_Line(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA)
    {
        return 0;
    }
    else if (GPIOx == GPIOB)
    {
        return 1;
    }
    else if (GPIOx == GPIOC)
    {
        return 2;
    }
    return -1;
}
void EXTI_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t mode)
{
    int8_t u8line = Get_EXTI_Line(GPIOx);
    uint8_t u8pinNumber = Get_Pin_Number(GPIO_Pin);

    if (u8line < 0 || u8pinNumber < 0)
    {
        return;
    }

    uint32_t tempreg = (u8pinNumber % 4) * 4;

    if (u8pinNumber < 4)
    {
        AFIO->EXTICR1 &= ~(uint32_t)(0x0F << tempreg);
        AFIO->EXTICR1 |= (uint32_t)(u8line << tempreg);
    }
    else if (u8pinNumber < 8)
    {
        AFIO->EXTICR2 &= ~(uint32_t)(0x0F << tempreg);
        AFIO->EXTICR2 |= (uint32_t)(u8line << tempreg);
    }
    else if (u8pinNumber < 12)
    {
        AFIO->EXTICR3 &= ~(uint32_t)(0x0F << tempreg);
        AFIO->EXTICR3 |= (uint32_t)(u8line << tempreg);
    }
    else
    {
        AFIO->EXTICR4 &= ~(uint32_t)(0x0F << tempreg);
        AFIO->EXTICR4 |= (uint32_t)(u8line << tempreg);
    }

    EXTI->IMR |= (1 << u8pinNumber);

    switch (mode)
    {
    case EXTI_MODE_RISING:
        EXTI->RTSR |= (1 << u8pinNumber);
        EXTI->FTSR &= ~(1 << u8pinNumber);
        break;

    case EXTI_MODE_FALLING:
        EXTI->RTSR &= ~(1 << u8pinNumber);
        EXTI->FTSR |= (1 << u8pinNumber);
        break;

    case EXTI_MODE_BOTH:
        EXTI->RTSR |= (1 << u8pinNumber);
        EXTI->FTSR |= (1 << u8pinNumber);
        break;

    default:
        return;
    }

    if (u8pinNumber <= 4)
    {
        NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn + u8pinNumber));
    }
    else if (u8pinNumber <= 9)
    {
        NVIC_EnableIRQ(EXTI9_5_IRQn);
    }
    else if (u8pinNumber <= 15)
    {
        NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
    else
    {
        return;
    }
}
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if (IRQn < 0 || IRQn >= 84)
    {
        return;
    }
    NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0)) // Check pending flag
    {
        EXTI->PR |= (1 << 0); // Write 1 to clear
        // TODO: Xử lý ngắt ở đây
    }
}