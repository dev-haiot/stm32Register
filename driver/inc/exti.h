#ifndef __EXTI_H
#define __EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

#define EXTI_MODE_RISING 0x01                                 /*!< Rising edge trigger selection */
#define EXTI_MODE_FALLING 0x02                                /*!< Falling edge trigger selection */
#define EXTI_MODE_BOTH (EXTI_MODE_RISING | EXTI_MODE_FALLING) /*!< Rising and Falling edge trigger selection */

typedef enum IRQn
{
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn = -14,   /*!< 2 Non Maskable Interrupt                             */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M3 Memory Management Interrupt             */
    BusFault_IRQn = -11,         /*!< 5 Cortex-M3 Bus Fault Interrupt                     */
    UsageFault_IRQn = -10,       /*!< 6 Cortex-M3 Usage Fault Interrupt                   */
    SVCall_IRQn = -5,            /*!< 11 Cortex-M3 SV Call Interrupt                      */
    DebugMonitor_IRQn = -4,      /*!< 12 Cortex-M3 Debug Monitor Interrupt                */
    PendSV_IRQn = -2,            /*!< 14 Cortex-M3 Pend SV Interrupt                      */
    SysTick_IRQn = -1,           /*!< 15 Cortex-M3 System Tick Interrupt                  */

    /******  STM32 specific Interrupt Numbers *********************************************************/
    WWDG_IRQn = 0,          /*!< Window WatchDog Interrupt                              */
    PVD_IRQn = 1,           /*!< PVD through EXTI Line detection Interrupt              */
    TAMPER_IRQn = 2,        /*!< Tamper Interrupt                                       */
    RTC_IRQn = 3,           /*!< RTC global Interrupt                                   */
    FLASH_IRQn = 4,         /*!< FLASH global Interrupt                                 */
    RCC_IRQn = 5,           /*!< RCC global Interrupt                                   */
    EXTI0_IRQn = 6,         /*!< EXTI Line0 Interrupt                                   */
    EXTI1_IRQn = 7,         /*!< EXTI Line1 Interrupt                                   */
    EXTI2_IRQn = 8,         /*!< EXTI Line2 Interrupt                                   */
    EXTI3_IRQn = 9,         /*!< EXTI Line3 Interrupt                                   */
    EXTI4_IRQn = 10,        /*!< EXTI Line4 Interrupt                                   */
    DMA_Channel1_IRQn = 11, /*!< DMA Channel 0 global Interrupt                         */
    DMA_Channel2_IRQn = 12, /*!< DMA Channel 1 global Interrupt                         */
    DMA_Channel3_IRQn = 13, /*!< DMA Channel 2 global Interrupt                         */
    DMA_Channel4_IRQn = 14, /*!< DMA Channel 3 global Interrupt                         */
    DMA_Channel5_IRQn = 15, /*!< DMA Channel 4 global Interrupt                         */
    DMA_Channel6_IRQn = 16, /*!< DMA Channel 5 global Interrupt                         */
    DMA_Channel7_IRQn = 17, /*!< DMA Channel 6 global Interrupt                         */
    ADC1_2_IRQn = 18,       /*!< ADC1 and ADC2 global Interrupt                         */
    EXTI9_5_IRQn = 23,      /*!< External Line[9:5] Interrupts                          */
    USART1_IRQn = 37,       /*!< USART1 global Interrupt                                */
    USART2_IRQn = 38,       /*!< USART2 global Interrupt                                */
    USART3_IRQn = 39,       /*!< USART3 global Interrupt                                */
    EXTI15_10_IRQn = 40,    /*!< External Line[15:10] Interrupts                        */
} IRQn_Type;

void EXTI0_IRQHandler(void);
int8_t Get_Pin_Number(uint16_t GPIO_Pin);
int8_t Get_EXTI_Line(GPIO_TypeDef *GPIOx);
void EXTI_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t mode);
void NVIC_EnableIRQ(IRQn_Type IRQn);

#ifdef __cplusplus
}
#endif

#endif // __EXTI_H