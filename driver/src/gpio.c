#include "stm32f1xx_utils.h"
#include "gpio.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t pinpos;
    uint32_t pos;
    uint32_t currentmode = 0;
    uint32_t tmpreg = 0;

    for (pinpos = 0; pinpos < 16; pinpos++)
    {
        pos = ((uint32_t)1 << pinpos);
        if (GPIO_InitStruct->Pin & pos)
        {
            // chọn CRL (pin 0..7) hoặc CRH (pin 8..15)
            if (pinpos < 8)
            {
                tmpreg = GPIOx->CRL;
                tmpreg &= ~((uint32_t)0xF << (pinpos * 4)); // clear trước
            }
            else
            {
                tmpreg = GPIOx->CRH;
                tmpreg &= ~((uint32_t)0xF << ((pinpos - 8) * 4));
            }

            // cấu hình MODE[1:0] và CNF[1:0]
            if (GPIO_InitStruct->Mode == GPIO_MODE_INPUT_FLOATING)
            {
                currentmode = (0x4); // CNF=01, MODE=00
            }
            else if (GPIO_InitStruct->Mode == GPIO_MODE_ANALOG)
            {
                currentmode = (0x0); // CNF=00, MODE=00
            }
            else if (GPIO_InitStruct->Mode == GPIO_MODE_IPU)
            {
                currentmode = (0x8); // CNF=10, MODE=00
                GPIOx->ODR |= pos;   // kéo lên
            }
            else if (GPIO_InitStruct->Mode == GPIO_MODE_IPD)
            {
                currentmode = (0x8); // CNF=10, MODE=00
                GPIOx->ODR &= ~pos;  // kéo xuống
            }
            else
            {
                // output / alternate function
                uint32_t mode = GPIO_InitStruct->Speed & 0x3;
                if (GPIO_InitStruct->Mode == GPIO_MODE_OP_PP)
                {
                    currentmode = (mode | 0x0 << 2); // CNF=00
                }
                else if (GPIO_InitStruct->Mode == GPIO_MODE_OP_OD)
                {
                    currentmode = (mode | 0x1 << 2); // CNF=01
                    GPIOx->ODR |= pos;
                }
                else if (GPIO_InitStruct->Mode == GPIO_MODE_AF_PP)
                {
                    currentmode = (mode | 0x2 << 2); // CNF=10
                }
                else if (GPIO_InitStruct->Mode == GPIO_MODE_AF_OD)
                {
                    currentmode = (mode | 0x3 << 2); // CNF=11
                    GPIOx->ODR |= pos;
                }
            }

            // ghi vào CRL hoặc CRH
            if (pinpos < 8)
            {
                tmpreg |= (currentmode << (pinpos * 4));
                GPIOx->CRL = tmpreg;
            }
            else
            {
                tmpreg |= (currentmode << ((pinpos - 8) * 4));
                GPIOx->CRH = tmpreg;
            }
        }
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState state)
{
    if (state == BIT_SET)
    {
        GPIOx->BSRR = GPIO_Pin; // set bit
    }
    else
    {
        GPIOx->BRR = GPIO_Pin; // reset bit
    }
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if ((GPIOx->ODR & GPIO_Pin) != 0)
    {
        GPIOx->BRR = GPIO_Pin; // clear
    }
    else
    {
        GPIOx->BSRR = GPIO_Pin; // set
    }
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if ((GPIOx->IDR & GPIO_Pin) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
