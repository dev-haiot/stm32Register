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

    static uint16_t adc_buffer[16];

    ADC_HandleTypeDef hadc_cfg = {0};
    hadc_cfg.Channel = ADC_CHANNEL_0;
    hadc_cfg.SampleTime = ADC_SAMPLETIME_239CYCLES5;
    hadc_cfg.ScanConvMode = ADC_SCANMODE_DISABLE;
    hadc_cfg.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc_cfg.ContinuousConv = ADC_CONVMODE_CONTINUOUS;

    ADC_Init(ADC1, &hadc_cfg);
    ADC_StartDMA(ADC1, adc_buffer, sizeof(adc_buffer) / sizeof(adc_buffer[0]));

    uint32_t last = millis();

    while (1)
    {
        if ((millis() - last) >= 1000)
        {
            last = millis();

            /* Print the first sample from adc_buffer as an example */
            uint16_t sample = adc_buffer[0];
            USART_Printf("ADC[0]=%u\r\n", sample);
        }
    }

    return 0;
}