#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define SYSTICK_CTRL    (*((volatile uint32_t *)0xE000E010))
#define SYSTICK_LOAD    (*((volatile uint32_t *)0xE000E014))
#define SYSTICK_VAL     (*((volatile uint32_t *)0xE000E018))

void SysTick_Handler(void);
void SysTick_Init(void);
uint32_t millis(void);
void DelayMs(uint32_t msDelay);
void DelayUs(uint32_t usDelay);

#ifdef __cplusplus
}
#endif

#endif // __SYSTICK_H
