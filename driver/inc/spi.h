#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

/*======================= SPI_CR1 register bits =======================*/
// CPHA: Clock phase
#define SPI_CPHA_1Edge              (0U << 0)
#define SPI_CPHA_2Edge              (1U << 0)
// CPOL: Clock polarity     
#define SPI_CPOL_LOW                (0U << 1)
#define SPI_CPOL_HIGH               (1U << 1)
// MSTR: Master selection
#define SPI_MODE_SLAVE              (0U << 2)
#define SPI_MODE_MASTER             (1U << 2)
// Baud rate control
#define SPI_BAUD_2                  (0U << 3)
#define SPI_BAUD_4                  (1U << 3)
#define SPI_BAUD_8                  (2U << 3)
#define SPI_BAUD_16                 (3U << 3)
#define SPI_BAUD_32                 (4U << 3)
#define SPI_BAUD_64                 (5U << 3)
#define SPI_BAUD_128                (6U << 3)
#define SPI_BAUD_256                (7U << 3)
// SPE: SPI enable
#define SPI_CR1_SPE_DISABLE         (0U << 6)
#define SPI_CR1_SPE_ENABLE          (1U << 6)
// LSBFIRST: Frame format
#define SPI_FIRSTBIT_MSB            (0U << 7)
#define SPI_FIRSTBIT_LSB            (1U << 7)
// SSI: Internal slave select
#define SPI_CR1_SSI_RESET           (0U << 8)
#define SPI_CR1_SSI_SET             (1U << 8)
// SSM: Software slave management
#define SPI_CR1_SSM_DISABLE         (0U << 9)
#define SPI_CR1_SSM_ENABLE          (1U << 9)
#define SPI_SSM_SSI_ENABLE_MASK     (SPI_CR1_SSI_SET | SPI_CR1_SSM_ENABLE)
// RXONLY: Receive only
#define SPI_DIRECTION_FULL_DUPLEX   (0U << 10)
#define SPI_DIRECTION_RXONLY        (1U << 10)
// DFF: Data frame format
#define SPI_DATASIZE_8BIT          (0U << 11)
#define SPI_DATASIZE_16BIT         (1U << 11)

/*======================= SPI_CR2 register bits =======================*/
#define SPI_CR2_RXNEIE            (1U << 6)
#define SPI_CR2_TXEIE             (1U << 7)

/*======================= SPI_SR (Status register) flags =======================*/
#define SPI_FLAG_RXNE             ((uint16_t)0x0001)  // Receive buffer not empty
#define SPI_FLAG_TXE              ((uint16_t)0x0002)  // Transmit buffer empty
#define SPI_FLAG_BSY              ((uint16_t)0x0080)  // Busy flag

/*======================= Chip Select Macros =======================*/
#define CS_PORT                   GPIOA
#define CS_PIN                    GPIO_PIN_4
#define CS_ON()                   (CS_PORT->BRR = CS_PIN)    
#define CS_OFF()                  (CS_PORT->BSRR = CS_PIN) 

typedef struct
{
    uint16_t Mode;
    uint16_t BaudRate;
    uint16_t SS;
    uint16_t CPOL;
    uint16_t CPHA;
    uint16_t FirstBit;
    uint16_t DataSize;
    uint16_t Direction;
} SPI_InitTypeDef;


void SPI_Cmd(SPI_TypeDef *SPIx,  FunctionalState state);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint32_t SPI_FLAG);
void SPI_Config(SPI_TypeDef *SPIx);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_TransmitData(SPI_TypeDef *SPIx, uint8_t u8data);
void SPI_SendCmd(SPI_TypeDef *SPIx, uint8_t command);
uint8_t SPI_ReceiveData(SPI_TypeDef *SPIx);
uint8_t SPI_TransmitReceive(SPI_TypeDef *SPIx, uint8_t u8data);

#ifdef __cplusplus
}
#endif

#endif // __SPI_H
