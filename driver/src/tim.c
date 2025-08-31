#include "tim.h"
#include "rcc.h"

static TIM_TypeDef *TIMx_Delay = TIM2;

void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState cmd)
{
    if (cmd != DISABLE)
    {
        TIMx->CR1 |= TIM_CR1_CEN;
    }
    else
    {
        TIMx->CR1 &= ~(TIM_CR1_CEN);
    }
}
void TIM_BaseInit(TIM_TypeDef *TIMx, TIM_BaseConfig_t cfg)
{
    TIMx->PSC = cfg.prescaler;
    TIMx->ARR = cfg.autoreload;

    TIMx->CNT = 0;
    TIMx->CR1 |= TIM_CR1_ARPE;  // cho phep preload ARR
    TIMx->EGR |= TIM_EGR_UG;    // dam bao cac new_val dc ap dung ngay
}
void TIM_PWMInit(TIM_TypeDef *TIMx, TIM_OCConfig_t oc_cfg)
{
    switch (oc_cfg.channel)
    {
    case TIM_CHANNEL_1:
        TIMx->CCMR1 &= ~((uint32_t)TIM_CCMR1_OC1M_MASK);
        TIMx->CCMR1 |= ((uint32_t)oc_cfg.ocmode << 4U);
        TIMx->CCMR1 |= (uint32_t)TIM_CCMR1_OC1PE;
        TIMx->CCR1 = oc_cfg.pulse;
        TIMx->CCER |= TIM_CCER_CC1E;
        break;

    case TIM_CHANNEL_2:
        TIMx->CCMR1 &= ~((uint32_t)TIM_CCMR1_OC2M_MASK);
        TIMx->CCMR1 |= ((uint32_t)oc_cfg.ocmode << 12U);
        TIMx->CCMR1 |= (uint32_t)TIM_CCMR1_OC2PE;
        TIMx->CCR2 = oc_cfg.pulse;
        TIMx->CCER |= TIM_CCER_CC2E;
        break;

    case TIM_CHANNEL_3:
        TIMx->CCMR2 &= ~((uint32_t)TIM_CCMR2_OC3M_MASK);
        TIMx->CCMR2 |= ((uint32_t)oc_cfg.ocmode << 4U);
        TIMx->CCMR2 |= (uint32_t)TIM_CCMR2_OC3PE;
        TIMx->CCR3 = oc_cfg.pulse;
        TIMx->CCER |= TIM_CCER_CC3E;
        break;

    case TIM_CHANNEL_4:
        TIMx->CCMR2 &= ~((uint32_t)TIM_CCMR2_OC4M_MASK);
        TIMx->CCMR2 |= ((uint32_t)oc_cfg.ocmode << 12U);
        TIMx->CCMR2 |= (uint32_t)TIM_CCMR2_OC4PE;
        TIMx->CCR4 = oc_cfg.pulse;
        TIMx->CCER |= TIM_CCER_CC4E;
        break;
    }

    TIMx->CR1 |= TIM_CR1_ARPE;

    /* EGR is write-only for update generation; write the UG bit directly */
    TIMx->EGR = TIM_EGR_UG;

    /* Only TIM1 has BDTR/MOE; set MOE for TIM1 if present and continue */
    if (TIMx == TIM1)
    {
        TIMx->BDTR |= TIM_BDTR_MOE;
    }
}
void TIM_SetCompare(TIM_TypeDef *TIMx, TIM_Channel_t channel, uint16_t ccr_val)
{
    switch (channel)
    {
    case TIM_CHANNEL_1:
        TIMx->CCR1 = ccr_val;
        break;
    case TIM_CHANNEL_2:
        TIMx->CCR2 = ccr_val;
        break;
    case TIM_CHANNEL_3:
        TIMx->CCR3 = ccr_val;
        break;
    case TIM_CHANNEL_4:
        TIMx->CCR4 = ccr_val;
        break;
    default:
        break;
    }
}

void TIM_DelayInit(void)
{
    if (TIMx_Delay == TIM1)
    {
        RCC_APB2ClockCmd(RCC_APB2_TIM1, ENABLE);
    }
    else if (TIMx_Delay == TIM2)
    {
        RCC_APB1ClockCmd(RCC_APB1_TIM2, ENABLE);
    }
    else if (TIMx_Delay == TIM3)
    {
        RCC_APB1ClockCmd(RCC_APB1_TIM3, ENABLE);
    }
    else
    {
        return;
    }

    TIMx_Delay->ARR = 9999;
    TIMx_Delay->PSC = 72 - 1;

    TIM_Cmd(TIMx_Delay, ENABLE);
}

void delay_us(uint32_t us)
{
    uint16_t start = (uint16_t)TIMx_Delay->CNT;
    while ((uint16_t)(TIMx_Delay->CNT - start) < us)
    {
    }
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}
