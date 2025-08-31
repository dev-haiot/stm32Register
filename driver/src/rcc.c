#include "rcc.h"

void RCC_CLOCK(RCC_CLOCK_SYS_t rcc_clock_sys)
{
    switch (rcc_clock_sys)
    {
    case RCC_CLOCK_SYS_24MHz:
        RCC_CLOCKConfig(&(RCC_ClockConfig_t){
            .ClockSource = RCC_CLOCK_HSE,
            .pll_mul = 6,  // 4MHz x 6 = 24MHz
            .ahb_div = 0,  // AHB /1
            .apb1_div = 4, // APB1 /2
            .apb2_div = 0, // APB2 /1
            .flash_latency = 0});
        break;

    case RCC_CLOCK_SYS_36MHz:
        RCC_CLOCKConfig(&(RCC_ClockConfig_t){
            .ClockSource = RCC_CLOCK_HSE,
            .pll_mul = 9, // 4MHz x 9 = 36MHz
            .ahb_div = 0,
            .apb1_div = 4,
            .apb2_div = 0,
            .flash_latency = 1});
        break;

    case RCC_CLOCK_SYS_48MHz:
        RCC_CLOCKConfig(&(RCC_ClockConfig_t){
            .ClockSource = RCC_CLOCK_HSE,
            .pll_mul = 12,
            .ahb_div = 0,
            .apb1_div = 4,
            .apb2_div = 0,
            .flash_latency = 1});
        break;

    case RCC_CLOCK_SYS_56MHz:
        RCC_CLOCKConfig(&(RCC_ClockConfig_t){
            .ClockSource = RCC_CLOCK_HSE,
            .pll_mul = 14,
            .ahb_div = 0,
            .apb1_div = 4,
            .apb2_div = 0,
            .flash_latency = 2});
        break;

    case RCC_CLOCK_SYS_72MHz:
        RCC_CLOCKConfig(&(RCC_ClockConfig_t){
            .ClockSource = RCC_CLOCK_HSE,
            .pll_mul = 9, // 8MHz HSE x9 = 72MHz
            .ahb_div = 0,
            .apb1_div = 4, // APB1 max 36MHz
            .apb2_div = 0,
            .flash_latency = 2});
        break;
    }
}

void RCC_CLOCKConfig(const RCC_ClockConfig_t *config)
{
    if (!config)
        return;

    // 1. Chọn nguồn clock (HSE / HSI)
    if (config->ClockSource == RCC_CLOCK_HSE)
    {
        RCC->CR |= (1 << 16); // HSEON
        while (!(RCC->CR & (1 << 17)))
            ; // HSERDY
    }
    else
    {
        RCC->CR |= (1 << 0); // HSION
        while (!(RCC->CR & (1 << 1)))
            ; // HSIRDY
    }

    // 2. Cấu hình Flash latency
    FLASH->ACR = config->flash_latency;

    // 3. Cấu hình prescaler AHB, APB1, APB2
    RCC->CFGR &= ~((0xF << 4) | (0x7 << 8) | (0x7 << 11));
    RCC->CFGR |= (config->ahb_div << 4);
    RCC->CFGR |= (config->apb1_div << 8);
    RCC->CFGR |= (config->apb2_div << 11);

    // 4. Tắt PLL trước khi config
    RCC->CR &= ~(1 << 24); // PLL OFF
    while (RCC->CR & (1 << 25))
        ; // chờ PLLRDY = 0

    // 5. Cấu hình PLL
    RCC->CFGR &= ~(0xF << 18);
    RCC->CFGR |= ((config->pll_mul - 2) << 18);

    if (config->ClockSource == RCC_CLOCK_HSE)
        RCC->CFGR |= (1 << 16); // PLLSRC = HSE
    else
        RCC->CFGR &= ~(1 << 16); // PLLSRC = HSI/2

    // 6. Bật PLL
    RCC->CR |= (1 << 24);
    while (!(RCC->CR & (1 << 25)))
        ; // PLLRDY

    // 7. Chọn PLL làm SYSCLK
    RCC->CFGR &= ~(0x3);
    RCC->CFGR |= 0x2;
    while (((RCC->CFGR >> 2) & 0x3) != 0x2)
        ;
}

void RCC_APB2ClockCmd(uint32_t periph_mask, FunctionalState state)
{
    if (state == ENABLE)
        RCC->APB2ENR |= periph_mask;
    else
        RCC->APB2ENR &= ~periph_mask;
}

void RCC_APB1ClockCmd(uint32_t periph_mask, FunctionalState state)
{
    if (state == ENABLE)
        RCC->APB1ENR |= periph_mask;
    else
        RCC->APB1ENR &= ~periph_mask;
}
