#include "systick.h"

static volatile uint32_t systick_ms = 0;

#define SYSTICK_LOAD_72Mhz  (72000U)        // For 1ms tick at 72MHz
#define SYSTICK_LOAD_36MHz  (36000U)        // For 1ms tick at 36MHz
#define SYSTICK_LOAD_16MHz  (16000U)        // For 1ms tick at 16MHz
#define SYSTICK_LOAD_8MHz   (8000U)         // For 1ms tick at 8MHz

#define SYS_CTRL_EN         (1U << 0)       // Counter enable
#define SYS_CTRL_TICKINT    (1U << 1)       // Enable SysTick exception request
#define SYS_CTRL_CLKSRC     (1U << 2)       // Clock source: 0 = external, 1 = processor clock (AHB)
#define SYS_CTRL_CNTFLAG    (1U << 16)      // Returns 1 if timer counted to 0 since last read
#define SYS_CTRL_ENABLE_MASK (SYS_CTRL_EN | SYS_CTRL_TICKINT | SYS_CTRL_CLKSRC)

void SysTick_Init()
{
    SYSTICK_CTRL = 0;                       // Disable SysTick
    SYSTICK_VAL = 0;                        // Clear current value
    SYSTICK_LOAD = SYSTICK_LOAD_72Mhz - 1;  // Load value for 1ms tick at 72MHz
    SYSTICK_CTRL |= SYS_CTRL_ENABLE_MASK;   // Enable SysTick with interrupts
}

inline uint32_t millis(void)
{
    return systick_ms;
}

void DelayMs(uint32_t msDelay)
{
    uint32_t start = millis();
    while ((millis() - start) < msDelay);
}

void DelayUs(uint32_t usDelay)
{
    volatile uint32_t count;
    while (usDelay--)
    {
        count = 72;
        while (count--);
    }
}

void SysTick_Handler(void)
{
    systick_ms++;
}
