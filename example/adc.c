#include "main.h"
#include "adc.h"

static uint16_t adc_value = 0;

static void USART_Config(void)
{
    USART_HandleTypeDef huart1 = {0};
    huart1.BaudRate = 115200;
    huart1.WordLength = USART_WORDLENGTH_8B;
    huart1.StopBits = USART_STOPBITS_1;
    huart1.IRQ_Enable = DISABLE;

    USART_Init(USART1, &huart1);
    USART_SetGlobal(USART1);
}

static void GPIO_ADC_Config(void)
{
    RCC_APB2ClockCmd(RCC_APB2_ADC1 | RCC_APB2_GPIOA | RCC_APB2_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio_cfg = {0};
    gpio_cfg.Mode = GPIO_MODE_ANALOG;
    gpio_cfg.Pin = GPIO_PIN_0;
    gpio_cfg.Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(GPIOA, &gpio_cfg);

    gpio_cfg.Mode = GPIO_MODE_OP_PP;
    gpio_cfg.Pin = GPIO_PIN_13;
    GPIO_Init(GPIOC, &gpio_cfg);

    ADC_HandleTypeDef hadc_cfg = {0};
    hadc_cfg.Channel = ADC_CHANNEL_0;        
    hadc_cfg.SampleTime = ADC_SAMPLETIME_239CYCLES5;    
    hadc_cfg.ScanConvMode = ADC_SCANMODE_DISABLE;  
    hadc_cfg.DataAlign = ADC_DATAALIGN_RIGHT;      
    hadc_cfg.ContinuousConv = ADC_CONVMODE_CONTINUOUS;

    ADC_Init(ADC1, &hadc_cfg);
}
int main(void)
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    SysTick_Init();
    GPIO_ADC_Config();
    USART_Config();
    USART_Printf("USART ready\r\n");

    uint32_t currentTime = millis();
    while (1)
    {
        if (millis() - currentTime > 1000)
        {
            currentTime = millis();

            adc_value = ADC_ReadData(ADC1);

            USART_Printf("The ADC value read is: %d\n", adc_value);

            if (adc_value > 3096)
            {
                GPIOC->ODR ^= GPIO_PIN_13;
            }
        }
    }
}
