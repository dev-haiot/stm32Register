#include "dma.h"

void DMA_Init(DMA_TypeDef *pDMAx, uint8_t channel, DMA_InitTypeDef *pDMA_InitStruct)
{
    volatile uint32_t *pCCR;
    volatile uint32_t *pCNDTR;
    volatile uint32_t *pCPAR;
    volatile uint32_t *pCMAR;

    switch (channel)
    {
    case 1:
        pCCR = &pDMAx->CCR1;
        pCNDTR = &pDMAx->CNDTR1;
        pCPAR = &pDMAx->CPAR1;
        pCMAR = &pDMAx->CMAR1;
        break;
    case 2:
        pCCR = &pDMAx->CCR2;
        pCNDTR = &pDMAx->CNDTR2;
        pCPAR = &pDMAx->CPAR2;
        pCMAR = &pDMAx->CMAR2;
        break;
    case 3:
        pCCR = &pDMAx->CCR3;
        pCNDTR = &pDMAx->CNDTR3;
        pCPAR = &pDMAx->CPAR3;
        pCMAR = &pDMAx->CMAR3;
        break;
    case 4:
        pCCR = &pDMAx->CCR4;
        pCNDTR = &pDMAx->CNDTR4;
        pCPAR = &pDMAx->CPAR4;
        pCMAR = &pDMAx->CMAR4;
        break;
    case 5:
        pCCR = &pDMAx->CCR5;
        pCNDTR = &pDMAx->CNDTR5;
        pCPAR = &pDMAx->CPAR5;
        pCMAR = &pDMAx->CMAR5;
        break;
    case 6:
        pCCR = &pDMAx->CCR6;
        pCNDTR = &pDMAx->CNDTR6;
        pCPAR = &pDMAx->CPAR6;
        pCMAR = &pDMAx->CMAR6;
        break;
    case 7:
        pCCR = &pDMAx->CCR7;
        pCNDTR = &pDMAx->CNDTR7;
        pCPAR = &pDMAx->CPAR7;
        pCMAR = &pDMAx->CMAR7;
        break;
    default:
        return; 
    }

    /* Disable DMA channel trước khi config */
    *pCCR &= ~DMA_CCR_EN;

    /* Gán giá trị */
    *pCPAR = pDMA_InitStruct->PeripheralBaseAddr;
    *pCMAR = pDMA_InitStruct->MemoryBaseAddr;
    *pCNDTR = pDMA_InitStruct->BufferSize;

    /* Cấu hình CCR */
    uint32_t tmpCCR = 0;
    tmpCCR |= (pDMA_InitStruct->DIR ? DMA_CCR_DIR : 0);
    tmpCCR |= (pDMA_InitStruct->PeripheralInc ? DMA_CCR_PINC : 0);
    tmpCCR |= (pDMA_InitStruct->MemoryInc ? DMA_CCR_MINC : 0);
    tmpCCR |= (pDMA_InitStruct->PeripheralDataSize << DMA_CCR_PSIZE_Pos);
    tmpCCR |= (pDMA_InitStruct->MemoryDataSize << DMA_CCR_MSIZE_Pos);
    tmpCCR |= (pDMA_InitStruct->Mode ? DMA_CCR_CIRC : 0);
    tmpCCR |= (pDMA_InitStruct->Priority << DMA_CCR_PL_Pos);
    tmpCCR |= (pDMA_InitStruct->M2M ? DMA_CCR_MEM2MEM : 0);

    *pCCR = tmpCCR;
}

/* Hàm enable channel sau khi config xong */
void DMA_Enable(DMA_TypeDef *pDMAx, uint8_t channel)
{
    switch (channel)
    {
    case 1:
        pDMAx->CCR1 |= DMA_CCR_EN;
        break;
    case 2:
        pDMAx->CCR2 |= DMA_CCR_EN;
        break;
    case 3:
        pDMAx->CCR3 |= DMA_CCR_EN;
        break;
    case 4:
        pDMAx->CCR4 |= DMA_CCR_EN;
        break;
    case 5:
        pDMAx->CCR5 |= DMA_CCR_EN;
        break;
    case 6:
        pDMAx->CCR6 |= DMA_CCR_EN;
        break;
    case 7:
        pDMAx->CCR7 |= DMA_CCR_EN;
        break;
    default:
        break;
    }
}

void DMA_Disable(DMA_TypeDef *pDMAx, uint8_t channel)
{
    switch (channel)
    {
    case 1:
        pDMAx->CCR1 &= ~DMA_CCR_EN;
        break;
    case 2:
        pDMAx->CCR2 &= ~DMA_CCR_EN;
        break;
    case 3:
        pDMAx->CCR3 &= ~DMA_CCR_EN;
        break;
    case 4:
        pDMAx->CCR4 &= ~DMA_CCR_EN;
        break;
    case 5:
        pDMAx->CCR5 &= ~DMA_CCR_EN;
        break;
    case 6:
        pDMAx->CCR6 &= ~DMA_CCR_EN;
        break;
    case 7:
        pDMAx->CCR7 &= ~DMA_CCR_EN;
        break;
    default:
        break;
    }
}

void DMA_ClockEnable(DMA_TypeDef *pDMAx)
{
    if (pDMAx == DMA1)
    {
        RCC->AHBENR |= (1 << 0);
    }
    else if (pDMAx == DMA2)
    {
        RCC->AHBENR |= (1 << 1);
    }
}