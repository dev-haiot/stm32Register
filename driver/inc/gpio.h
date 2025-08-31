#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

// GPIO Mode
typedef enum
{
	GPIO_MODE_INPUT_FLOATING = 0,
	GPIO_MODE_OP_PP,   // Output Push-Pull
	GPIO_MODE_OP_OD,   // Output Open-Drain
	GPIO_MODE_AF_PP,   // Alternate Function Push-Pull
	GPIO_MODE_AF_OD,   // Alternate Function Open-Drain
	GPIO_MODE_ANALOG,
	GPIO_MODE_IPU,     // Input Pull-up
	GPIO_MODE_IPD,     // Input Pull-down
} GPIO_Mode_t;

// GPIO Speed
typedef enum
{
	GPIO_SPEED_NONE = 0,
	GPIO_SPEED_10MHZ = 1,
	GPIO_SPEED_2MHZ,
	GPIO_SPEED_50MHZ
} GPIO_Speed_t;

// GPIO Init structure
typedef struct
{
	uint16_t Pin;
	GPIO_Mode_t Mode;
	GPIO_Speed_t Speed;
} GPIO_InitTypeDef;

// Function prototypes
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState state);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif // __GPIO_H
