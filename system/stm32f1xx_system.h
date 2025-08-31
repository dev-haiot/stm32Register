#ifndef __STM32F1XX_SYSTEM_H
#define __STM32F1XX_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_utils.h"

// FLASH registers
typedef struct
{
	volatile uint32_t ACR;
} FLASH_TypeDef;

// RCC_Registers
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
} RCC_TypeDef;

// GPIO_Registers
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_TypeDef;

// AFIO_Registers
typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR1;
    volatile uint32_t EXTICR2;
    volatile uint32_t EXTICR3;
    volatile uint32_t EXTICR4;
    volatile uint32_t MAPR2;
} AFIO_TypeDef;

// EXTI_Registers
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

// NVIC_Registers
typedef struct
{
	volatile uint32_t ISER[8];  /*!< Interrupt Set Enable Registers,           Address offset: 0x00-0x1C */
	uint32_t      RESERVED0[24];
	volatile uint32_t ICER[8];  /*!< Interrupt Clear Enable Registers,         Address offset: 0x80-0x9C */
	uint32_t      RESERVED1[24];
	volatile uint32_t ISPR[8];  /*!< Interrupt Set Pending Registers,          Address offset: 0x100-0x11C */
	uint32_t      RESERVED2[24];
	volatile uint32_t ICPR[8];  /*!< Interrupt Clear Pending Registers,        Address offset: 0x180-0x19C */
	uint32_t      RESERVED3[24];
	volatile uint32_t IABR[8];  /*!< Interrupt Active bit Registers,           Address offset: 0x200-0x21C */
	uint32_t      RESERVED4[56];                      
    volatile uint8_t  IPR[240]; /*!< Interrupt Priority Registers,             Address offset: 0x300-0x3EF */
	uint32_t      RESERVED5[644];                        
	volatile uint32_t STIR;     /*!< Software Trigger Interrupt Register,      Address offset: 0xE00 */
} NVIC_TypeDef;

// TIM_Register
typedef struct {
   volatile uint32_t CR1;    
   volatile uint32_t CR2;    
   volatile uint32_t SMCR;   
   volatile uint32_t DIER;   
   volatile uint32_t SR;     
   volatile uint32_t EGR;    
   volatile uint32_t CCMR1;  
   volatile uint32_t CCMR2;  
   volatile uint32_t CCER;   
   volatile uint32_t CNT;    
   volatile uint32_t PSC;    
   volatile uint32_t ARR;    
   volatile uint32_t RCR;    
   volatile uint32_t CCR1;   
   volatile uint32_t CCR2;   
   volatile uint32_t CCR3;   
   volatile uint32_t CCR4;   
   volatile uint32_t BDTR;   
   volatile uint32_t DCR;    
   volatile uint32_t DMAR;   
} TIM_TypeDef;

// ADC_Register

typedef struct
{    
	volatile uint32_t SR; 
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
} ADC_TypeDef;

// USART_Register

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;

// SPI_Register
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
} SPI_TypeDef;

// I2C_Register
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
} I2C_TypeDef;	
/* DMA controller registers (DMA1/ DMA2 on some families) */
typedef struct
{
	volatile uint32_t ISR;       /*!< DMA interrupt status register,       Address offset: 0x00 */
	volatile uint32_t IFCR;      /*!< DMA interrupt flag clear register,   Address offset: 0x04 */

	/* Channel 1 registers */
	volatile uint32_t CCR1;      /*!< DMA channel 1 configuration */
	volatile uint32_t CNDTR1;    /*!< DMA channel 1 number of data register */
	volatile uint32_t CPAR1;     /*!< DMA channel 1 peripheral address register */
	volatile uint32_t CMAR1;     /*!< DMA channel 1 memory address register */
	volatile uint32_t RESERVED0; /* reserved 0x18 */

	/* Channel 2 registers */
	volatile uint32_t CCR2;
	volatile uint32_t CNDTR2;
	volatile uint32_t CPAR2;
	volatile uint32_t CMAR2;
	volatile uint32_t RESERVED1;

	/* Channel 3 registers */
	volatile uint32_t CCR3;
	volatile uint32_t CNDTR3;
	volatile uint32_t CPAR3;
	volatile uint32_t CMAR3;
	volatile uint32_t RESERVED2;

	/* Channel 4 registers */
	volatile uint32_t CCR4;
	volatile uint32_t CNDTR4;
	volatile uint32_t CPAR4;
	volatile uint32_t CMAR4;
	volatile uint32_t RESERVED3;

	/* Channel 5 registers */
	volatile uint32_t CCR5;
	volatile uint32_t CNDTR5;
	volatile uint32_t CPAR5;
	volatile uint32_t CMAR5;
	volatile uint32_t RESERVED4;

	/* Channel 6 registers */
	volatile uint32_t CCR6;
	volatile uint32_t CNDTR6;
	volatile uint32_t CPAR6;
	volatile uint32_t CMAR6;
	volatile uint32_t RESERVED5;

	/* Channel 7 registers */
	volatile uint32_t CCR7;
	volatile uint32_t CNDTR7;
	volatile uint32_t CPAR7;
	volatile uint32_t CMAR7;
	volatile uint32_t RESERVED6;
} DMA_TypeDef;


// Base Address
#define NVIC_Base 		(0xE000E100)
#define FLASH_BASE  	(0x40022000)
#define RCC_BASE    	(0x40021000)
#define AFIO_BASE   	(0x40010000)
#define GPIOA_BASE		(0x40010800)
#define GPIOB_BASE		(0x40010C00)
#define GPIOC_BASE		(0x40011000)
#define EXTI_BASE   	(0x40010400)
#define TIM1_BASE   	(0x40012C00)
#define TIM2_BASE   	(0x40000000)
#define TIM3_BASE   	(0x40000400)
#define ADC1_BASE		(0x40012400)
#define ADC2_BASE		(0x40012800)
#define USART1_BASE		(0x40013800)
#define USART2_BASE		(0x40004400)
#define USART3_BASE		(0x40004800)
#define SPI1_BASE		(0x40013000)
#define SPI2_BASE		(0x40003800)
#define I2C1_BASE		(0x40005400)
#define I2C2_BASE		(0x40005800)
#define DMA1_BASE      	(0x40020000)
#define DMA2_BASE      	(0x40020400)

// Peripheral instance
#define NVIC        ((NVIC_TypeDef *)NVIC_Base)
#define RCC         ((RCC_TypeDef *)RCC_BASE)
#define FLASH       ((FLASH_TypeDef *)FLASH_BASE)
#define GPIOA 		((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB 		((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC 		((GPIO_TypeDef *)GPIOC_BASE)
#define AFIO        ((AFIO_TypeDef *)AFIO_BASE)
#define EXTI        ((EXTI_TypeDef *)EXTI_BASE)
#define TIM1        ((TIM_TypeDef *)TIM1_BASE)
#define TIM2        ((TIM_TypeDef *)TIM2_BASE)
#define TIM3        ((TIM_TypeDef *)TIM3_BASE)
#define ADC1    	((ADC_TypeDef *)ADC1_BASE)
#define ADC2		((ADC_TypeDef *)ADC2_BASE)
#define USART1		((USART_TypeDef *)USART1_BASE)
#define USART2		((USART_TypeDef *)USART2_BASE)
#define USART3		((USART_TypeDef *)USART3_BASE)
#define SPI1		((SPI_TypeDef *)SPI1_BASE)
#define SPI2		((SPI_TypeDef *)SPI2_BASE)
#define I2C1        ((I2C_TypeDef *)I2C1_BASE)
#define I2C2 		((I2C_TypeDef *)I2C2_BASE)
#define DMA1       	((DMA_TypeDef *)DMA1_BASE)
#define DMA2       	((DMA_TypeDef *)DMA2_BASE)

#ifdef __cplusplus
}
#endif


#endif // __STM32F1XX_SYSTEM_H