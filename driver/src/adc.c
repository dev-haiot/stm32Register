#include "adc.h"
#include "systick.h"
#include "dma.h"

void ADC_Init(ADC_TypeDef *pADCx, ADC_HandleTypeDef *pADC_HandleStruct)
{

    // Enable ADC clock
    if (pADCx == ADC1)
    {
        RCC->APB2ENR |= (1 << 9);
    }
    else if (pADCx == ADC2)
    {
        RCC->APB2ENR |= (1 << 10);
    }

    // CR1: Scan mode
    if (pADC_HandleStruct->ScanConvMode)
    {
        pADCx->CR1 |= (1 << 8);
    }
    else
    {
        pADCx->CR1 &= ~(1 << 8);
    }

    // CR2: Data alignment
    if (pADC_HandleStruct->DataAlign)
    {
        pADCx->CR2 |= (1 << 11); // left alignment
    }
    else
    {
        pADCx->CR2 &= ~(1 << 11); // right alignment
    }

    // --- Channel sample time configuration ---
    uint8_t ch = pADC_HandleStruct->Channel;
    uint8_t st = pADC_HandleStruct->SampleTime;

    if (ch <= 9)
    {
        pADCx->SMPR2 &= ~(0x7 << (3 * ch));
        pADCx->SMPR2 |= (st & 0x7) << (3 * ch);
    }
    else
    {
        pADCx->SMPR1 &= ~(0x7 << (3 * (ch - 10)));
        pADCx->SMPR1 |= (st & 0x7) << (3 * (ch - 10));
    }

    // Set channel vao SQR3
    pADCx->SQR3 = ch & 0x1F;

    // Enable ADC
    pADCx->CR2 |= (1 << 0);
    DelayMs(1);
    pADCx->CR2 |= (1 << 0);

    // Calib
    pADCx->CR2 |= (1 << 3);
    while (pADCx->CR2 & (1 << 3))
        ;

    pADCx->CR2 |= (1 << 2);
    while (pADCx->CR2 & (1 << 2))
        ;

    /* Configure continuous conversion mode if requested */
    if (pADC_HandleStruct->ContinuousConv)
    {
        pADCx->CR2 |= (1 << 1); /* CONT = 1 */
    }
    else
    {
        pADCx->CR2 &= ~(1 << 1); /* CONT = 0 */
    }

    /* Start conversion by software (SWSTART) */
    pADCx->CR2 |= (1 << 22);
}
uint16_t ADC_ReadData(ADC_TypeDef *pADCx)
{
    while (!(pADCx->SR & (1 << 1)))
        ;
    return (uint16_t)(pADCx->DR & 0xFFFF);
}

/* Start ADC DMA: peripheral (ADCx->DR) -> memory (pBuffer)
 * - Uses DMA1 Channel1 for ADC1 on STM32F1
 * - Configures circular mode so ADC conversions continuously fill the buffer
 */
void ADC_StartDMA(ADC_TypeDef *pADCx, uint16_t *pBuffer, uint32_t length)
{
    if (pADCx == 0 || pBuffer == 0 || length == 0)
        return;

    /* Only support ADC1 for now */
    if (pADCx != ADC1)
        return;

    /* Enable DMA clock */
    DMA_ClockEnable(DMA1);

    DMA_InitTypeDef dma_cfg;
    dma_cfg.PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
    dma_cfg.MemoryBaseAddr = (uint32_t)pBuffer;
    dma_cfg.DIR = DMA_DIR_P2M; /* peripheral to memory */
    dma_cfg.BufferSize = length;
    dma_cfg.PeripheralInc = DMA_INC_DISABLE;
    dma_cfg.MemoryInc = DMA_INC_ENABLE;
    dma_cfg.PeripheralDataSize = DMA_DATASIZE_16BIT;
    dma_cfg.MemoryDataSize = DMA_DATASIZE_16BIT;
    dma_cfg.Mode = DMA_MODE_CIRCULAR; /* continuous */
    dma_cfg.Priority = DMA_PRIORITY_HIGH;
    dma_cfg.M2M = DMA_M2M_DISABLE;

    const uint8_t channel = DMA_CHANNEL1; /* ADC1 -> DMA1 Channel1 */

    DMA_Init(DMA1, channel, &dma_cfg);


    pADCx->CR2 |= (1 << 8); 

    DMA_Enable(DMA1, channel);
}

void ADC_StopDMA(ADC_TypeDef *pADCx)
{
    if (pADCx == 0)
        return;

    if (pADCx != ADC1)
        return;

    const uint8_t channel = DMA_CHANNEL1;
    /* Disable DMA channel */
    DMA_Disable(DMA1, channel);

    /* Disable ADC DMA request */
    pADCx->CR2 &= ~(1 << 8);
}