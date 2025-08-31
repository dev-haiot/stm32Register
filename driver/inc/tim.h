#ifndef __TIM_H
#define __TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

/* Control Register 1 (CR1) */
#define TIM_CR1_CEN             0x0001
#define TIM_CR1_UDIS            0x0002
#define TIM_CR1_URS             0x0004
#define TIM_CR1_OPM             0x0008
#define TIM_CR1_DIR             0x0010
#define TIM_CR1_CMS_0           0x0020
#define TIM_CR1_CMS_1           0x0040
#define TIM_CR1_ARPE            0x0080
#define TIM_CR1_CKD_0           0x0100
#define TIM_CR1_CKD_1           0x0200

/* Control Register 2 (CR2) */
#define TIM_CR2_CCDS            0x0008

/* Capture/Compare Mode Register 1 (CCMR1) */
#define TIM_CCMR1_OC1FE         0x0004
#define TIM_CCMR1_OC1PE         0x0008
#define TIM_CCMR1_OC1M_MASK     0x0070
#define TIM_CCMR1_OC1M_0        0x0010
#define TIM_CCMR1_OC1M_1        0x0020
#define TIM_CCMR1_OC1M_2        0x0040
#define TIM_CCMR1_OC1CE         0x0080

#define TIM_CCMR1_OC2FE         0x0400
#define TIM_CCMR1_OC2PE         0x0800
#define TIM_CCMR1_OC2M_MASK     0x7000
#define TIM_CCMR1_OC2M_0        0x1000
#define TIM_CCMR1_OC2M_1        0x2000
#define TIM_CCMR1_OC2M_2        0x4000
#define TIM_CCMR1_OC2CE         0x8000

/* Capture/Compare Mode Register 2 (CCMR2) */
#define TIM_CCMR2_OC3FE         0x0004
#define TIM_CCMR2_OC3PE         0x0008
#define TIM_CCMR2_OC3M_MASK     0x0070
#define TIM_CCMR2_OC3M_0        0x0010
#define TIM_CCMR2_OC3M_1        0x0020
#define TIM_CCMR2_OC3M_2        0x0040
#define TIM_CCMR2_OC3CE         0x0080

#define TIM_CCMR2_OC4FE         0x0400
#define TIM_CCMR2_OC4PE         0x0800
#define TIM_CCMR2_OC4M_MASK     0x7000
#define TIM_CCMR2_OC4M_0        0x1000
#define TIM_CCMR2_OC4M_1        0x2000
#define TIM_CCMR2_OC4M_2        0x4000
#define TIM_CCMR2_OC4CE         0x8000

/* Capture/Compare Enable Register (CCER) */
#define TIM_CCER_CC1E           0x0001
#define TIM_CCER_CC1P           0x0002
#define TIM_CCER_CC1NE          0x0004
#define TIM_CCER_CC1NP          0x0008
#define TIM_CCER_CC2E           0x0010
#define TIM_CCER_CC2P           0x0020
#define TIM_CCER_CC2NE          0x0040
#define TIM_CCER_CC2NP          0x0080
#define TIM_CCER_CC3E           0x0100
#define TIM_CCER_CC3P           0x0200
#define TIM_CCER_CC3NE          0x0400
#define TIM_CCER_CC3NP          0x0800
#define TIM_CCER_CC4E           0x1000
#define TIM_CCER_CC4P           0x2000
#define TIM_CCER_CC4NP          0x8000

/* Event Generation Register (EGR) */
#define TIM_EGR_UG              0x0001
#define TIM_EGR_CC1G            0x0002
#define TIM_EGR_CC2G            0x0004
#define TIM_EGR_CC3G            0x0008
#define TIM_EGR_CC4G            0x0010
#define TIM_EGR_COMG            0x0020
#define TIM_EGR_TG              0x0040
#define TIM_EGR_BG              0x0080

/* DMA/Interrupt Enable Register (DIER) */
#define TIM_DIER_UIE            0x0001
#define TIM_DIER_CC1IE          0x0002
#define TIM_DIER_CC2IE          0x0004
#define TIM_DIER_CC3IE          0x0008
#define TIM_DIER_CC4IE          0x0010
#define TIM_DIER_TIE            0x0040
#define TIM_DIER_UDE            0x0100

/* Status Register (SR) */
#define TIM_SR_UIF              0x0001
#define TIM_SR_CC1IF            0x0002
#define TIM_SR_CC2IF            0x0004
#define TIM_SR_CC3IF            0x0008
#define TIM_SR_CC4IF            0x0010
#define TIM_SR_TIF              0x0040
#define TIM_SR_CC1OF            0x0200
#define TIM_SR_CC2OF            0x0400

/* Break and Dead-Time Register (BDTR) */
#define TIM_BDTR_DTG_MASK       0x00FF
#define TIM_BDTR_LOCK_MASK      0x0300
#define TIM_BDTR_OSSR           0x0400
#define TIM_BDTR_OSSI           0x0800
#define TIM_BDTR_BKE            0x1000
#define TIM_BDTR_BKP            0x2000
#define TIM_BDTR_AOE            0x4000
#define TIM_BDTR_MOE            0x8000

/* Output Compare Modes */
#define TIM_OCMODE_PWM1         0x6
#define TIM_OCMODE_PWM2         0x7

#define TIM_OCMODE_PWM1_OC1     (TIM_OCMODE_PWM1 << 4)
#define TIM_OCMODE_PWM1_OC2     (TIM_OCMODE_PWM1 << 12)
#define TIM_OCMODE_PWM2_OC1     (TIM_OCMODE_PWM2 << 4)
#define TIM_OCMODE_PWM2_OC2     (TIM_OCMODE_PWM2 << 12)

/* Types */
typedef enum
{
    TIM_CHANNEL_1 = 0x01,
    TIM_CHANNEL_2 = 0x02,
    TIM_CHANNEL_3 = 0x04,
    TIM_CHANNEL_4 = 0x08
} TIM_Channel_t;

typedef struct
{
    uint16_t prescaler;
    uint16_t autoreload;
} TIM_BaseConfig_t;

typedef struct
{
    TIM_Channel_t channel;
    uint8_t ocmode;
    uint16_t pulse;
} TIM_OCConfig_t;


void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState cmd);
void TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseConfig_t cfg);
void TIM_PWMInit(TIM_TypeDef *TIMx, TIM_OCConfig_t oc_cfg);
void TIM_SetCompare(TIM_TypeDef *TIMx, TIM_Channel_t channel, uint16_t ccr_val);
void TIM_DelayInit(void);

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#ifdef __cplusplus
extern "C" {
#endif

#endif // __TIM_H
