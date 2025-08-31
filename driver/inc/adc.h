#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

typedef struct
{
    uint8_t Channel;
    uint8_t SampleTime;
    uint8_t ScanConvMode;
    uint8_t DataAlign;
    uint8_t ContinuousConv;
} ADC_HandleTypeDef;

void ADC_Init(ADC_TypeDef *pADCx, ADC_HandleTypeDef *pADC_HandleStruct);
uint16_t ADC_ReadData(ADC_TypeDef *pADCx);
void ADC_StartDMA(ADC_TypeDef *pADCx, uint16_t *pBuffer, uint32_t length);
void ADC_StopDMA(ADC_TypeDef *pADCx);

#define ADC_CHANNEL_0      0
#define ADC_CHANNEL_1      1
#define ADC_CHANNEL_2      2
#define ADC_CHANNEL_3      3
#define ADC_CHANNEL_4      4
#define ADC_CHANNEL_5      5
#define ADC_CHANNEL_6      6
#define ADC_CHANNEL_7      7
#define ADC_CHANNEL_8      8
#define ADC_CHANNEL_9      9
#define ADC_CHANNEL_10     10
#define ADC_CHANNEL_11     11
#define ADC_CHANNEL_12     12
#define ADC_CHANNEL_13     13
#define ADC_CHANNEL_14     14
#define ADC_CHANNEL_15     15

#define ADC_SAMPLETIME_1CYCLE5       0x0
#define ADC_SAMPLETIME_7CYCLES5      0x1
#define ADC_SAMPLETIME_13CYCLES5     0x2
#define ADC_SAMPLETIME_28CYCLES5     0x3
#define ADC_SAMPLETIME_41CYCLES5     0x4
#define ADC_SAMPLETIME_55CYCLES5     0x5
#define ADC_SAMPLETIME_71CYCLES5     0x6
#define ADC_SAMPLETIME_239CYCLES5    0x7

// Data Alignment
#define ADC_DATAALIGN_RIGHT          0
#define ADC_DATAALIGN_LEFT           1

// Conversion Mode
#define ADC_CONVMODE_SINGLE          0
#define ADC_CONVMODE_CONTINUOUS      1

// Scan Mode
#define ADC_SCANMODE_DISABLE         0
#define ADC_SCANMODE_ENABLE          1


#ifdef __cplusplus
}
#endif

#endif // __ADC_H
