#ifndef __RCC_H
#define __RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

// RCC Register map
#define RCC_APB2_AFIO       ((uint32_t)0x00000001)
#define RCC_APB2_GPIOA      ((uint32_t)0x00000004)
#define RCC_APB2_GPIOB      ((uint32_t)0x00000008)
#define RCC_APB2_GPIOC      ((uint32_t)0x00000010)
#define RCC_APB2_ADC1       ((uint32_t)0x00000200)
#define RCC_APB2_ADC2       ((uint32_t)0x00000400)
#define RCC_APB2_TIM1       ((uint32_t)0x00000800)
#define RCC_APB2_SPI1       ((uint32_t)0x00001000)
#define RCC_APB2_USART1     ((uint32_t)0x00004000)

#define RCC_APB1_TIM2       ((uint32_t)0x00000001)
#define RCC_APB1_TIM3       ((uint32_t)0x00000002)
#define RCC_APB1_TIM4       ((uint32_t)0x00000004)
#define RCC_APB1_WWDG       ((uint32_t)0x00000800)
#define RCC_APB1_SPI2       ((uint32_t)0x00004000)
#define RCC_APB1_USART2     ((uint32_t)0x00020000)
#define RCC_APB1_USART3     ((uint32_t)0x00040000)
#define RCC_APB1_I2C1       ((uint32_t)0x00200000)
#define RCC_APB1_I2C2       ((uint32_t)0x00400000)
#define RCC_APB1_USB        ((uint32_t)0x00800000)
#define RCC_APB1_CAN        ((uint32_t)0x02000000)
#define RCC_APB1_BKP        ((uint32_t)0x08000000)
#define RCC_APB1_PWR        ((uint32_t)0x10000000)

typedef enum
{
	RCC_CLOCK_SYS_24MHz = 0,
	RCC_CLOCK_SYS_36MHz,
	RCC_CLOCK_SYS_48MHz,
	RCC_CLOCK_SYS_56MHz,
	RCC_CLOCK_SYS_72MHz
} RCC_CLOCK_SYS_t;

typedef enum
{
    RCC_CLOCK_HSE = 0,
    RCC_CLOCK_HSI = 1
} RCC_ClockSource;

typedef struct
{
    RCC_ClockSource ClockSource; 	// HSE hoặc HSI
    uint8_t pll_mul;        		// Hệ số nhân PLL (2-16)
    uint8_t ahb_div;        		// Chia AHB (0: /1, 8: /2, ...)
    uint8_t apb1_div;       		// Chia APB1 (0: /1, 4: /2, ...)
    uint8_t apb2_div;       		// Chia APB2 (0: /1, 4: /2, ...)
    uint8_t flash_latency;  		// Độ trễ Flash (0-2)
} RCC_ClockConfig_t;


void RCC_CLOCK(RCC_CLOCK_SYS_t rcc_clock_sys);
void RCC_CLOCKConfig(const RCC_ClockConfig_t *config);
void RCC_APB2ClockCmd(uint32_t periph_mask, FunctionalState state);
void RCC_APB1ClockCmd(uint32_t periph_mask, FunctionalState state);

#ifdef __cplusplus
}
#endif

#endif // __RCC_H
