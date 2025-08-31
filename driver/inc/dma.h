#ifndef __DMA_H
#define __DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

/* ============================================================
 * Channel numbers 
 * ============================================================ */
#define DMA_CHANNEL1   (1U)
#define DMA_CHANNEL2   (2U)
#define DMA_CHANNEL3   (3U)
#define DMA_CHANNEL4   (4U)
#define DMA_CHANNEL5   (5U)
#define DMA_CHANNEL6   (6U)
#define DMA_CHANNEL7   (7U)

/* ============================================================
 * Direction
 * ============================================================ */
#define DMA_DIR_P2M            (0U)   /* Peripheral -> Memory */
#define DMA_DIR_M2P            (1U)   /* Memory -> Peripheral */

/* Increment mode */
#define DMA_INC_DISABLE        (0U)
#define DMA_INC_ENABLE         (1U)

/* Data size (PSIZE/MSIZE) */
#define DMA_DATASIZE_8BIT      (0U)
#define DMA_DATASIZE_16BIT     (1U)
#define DMA_DATASIZE_32BIT     (2U)

/* Mode */
#define DMA_MODE_NORMAL        (0U)
#define DMA_MODE_CIRCULAR      (1U)

/* Priority */
#define DMA_PRIORITY_LOW       (0U)
#define DMA_PRIORITY_MEDIUM    (1U)
#define DMA_PRIORITY_HIGH      (2U)
#define DMA_PRIORITY_VERYHIGH  (3U)

/* Memory-to-Memory mode */
#define DMA_M2M_DISABLE        (0U)
#define DMA_M2M_ENABLE         (1U)

/* ============================================================
 * DMA Interrupt Status / Clear Flags (ISR / IFCR)
 * ============================================================ */
#define DMA_ISR_GIF(ch)      (1U << (((ch) - 1U) * 4U + 0U))  /* Global flag */
#define DMA_ISR_TCIF(ch)     (1U << (((ch) - 1U) * 4U + 1U))  /* Transfer complete */
#define DMA_ISR_HTIF(ch)     (1U << (((ch) - 1U) * 4U + 2U))  /* Half transfer */
#define DMA_ISR_TEIF(ch)     (1U << (((ch) - 1U) * 4U + 3U))  /* Transfer error */

/* ============================================================
 * DMA_CCR Bit Definitions
 * ============================================================ */
#define DMA_CCR_EN_Pos          (0U)
#define DMA_CCR_TCIE_Pos        (1U)
#define DMA_CCR_HTIE_Pos        (2U)
#define DMA_CCR_TEIE_Pos        (3U)
#define DMA_CCR_DIR_Pos         (4U)
#define DMA_CCR_CIRC_Pos        (5U)
#define DMA_CCR_PINC_Pos        (6U)
#define DMA_CCR_MINC_Pos        (7U)
#define DMA_CCR_PSIZE_Pos       (8U)
#define DMA_CCR_MSIZE_Pos       (10U)
#define DMA_CCR_PL_Pos          (12U)
#define DMA_CCR_MEM2MEM_Pos     (14U)

#define DMA_CCR_EN              (1U << DMA_CCR_EN_Pos)
#define DMA_CCR_TCIE            (1U << DMA_CCR_TCIE_Pos)
#define DMA_CCR_HTIE            (1U << DMA_CCR_HTIE_Pos)
#define DMA_CCR_TEIE            (1U << DMA_CCR_TEIE_Pos)
#define DMA_CCR_DIR             (1U << DMA_CCR_DIR_Pos)
#define DMA_CCR_CIRC            (1U << DMA_CCR_CIRC_Pos)
#define DMA_CCR_PINC            (1U << DMA_CCR_PINC_Pos)
#define DMA_CCR_MINC            (1U << DMA_CCR_MINC_Pos)
#define DMA_CCR_MEM2MEM         (1U << DMA_CCR_MEM2MEM_Pos)

/* ============================================================
 * DMA Data Size Configurations
 * ============================================================ */
#define DMA_CCR_PSIZE_8BIT      (0U << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_PSIZE_16BIT     (1U << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_PSIZE_32BIT     (2U << DMA_CCR_PSIZE_Pos)

#define DMA_CCR_MSIZE_8BIT      (0U << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_MSIZE_16BIT     (1U << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_MSIZE_32BIT     (2U << DMA_CCR_MSIZE_Pos)

/* ============================================================
 * DMA Priority Level
 * ============================================================ */
#define DMA_CCR_PL_LOW          (0U << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_MEDIUM       (1U << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_HIGH         (2U << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_VERYHIGH     (3U << DMA_CCR_PL_Pos)

/* ============================================================
 * DMA Init Struct
 * ============================================================ */
typedef struct
{
    volatile uint32_t PeripheralBaseAddr;   /*!< Peripheral address */
    volatile uint32_t MemoryBaseAddr;       /*!< Memory address */
    volatile uint32_t DIR;                  /*!< Direction */
    volatile uint32_t BufferSize;           /*!< Number of data items */
    volatile uint32_t PeripheralInc;        /*!< Peripheral increment mode */
    volatile uint32_t MemoryInc;            /*!< Memory increment mode */
    volatile uint32_t PeripheralDataSize;   /*!< Peripheral data size */
    volatile uint32_t MemoryDataSize;       /*!< Memory data size */
    volatile uint32_t Mode;                 /*!< Circular or Normal mode */
    volatile uint32_t Priority;             /*!< Priority level */
    volatile uint32_t M2M;                  /*!< Memory to Memory mode */
} DMA_InitTypeDef;

/* ============================================================
 * Function Prototype
 * ============================================================ */
void DMA_ClockEnable(DMA_TypeDef *pDMAx);
void DMA_Init(DMA_TypeDef *pDMAx, uint8_t channel, DMA_InitTypeDef *pDMA_InitStruct);
void DMA_Enable(DMA_TypeDef *pDMAx, uint8_t channel);
void DMA_Disable(DMA_TypeDef *pDMAx, uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H */
