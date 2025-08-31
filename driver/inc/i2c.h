#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_system.h"

/* Control register 1 */
#define I2C_ACK_ENABLE          ((uint16_t)0x0400)
#define I2C_ACK_DISABLE         ((uint16_t)0x0000)

/* I2C CR1 bits */
#define I2C_CR1_PE              ((uint16_t)0x0001)    /* Peripheral enable */
#define I2C_CR1_START           ((uint16_t)0x0100)    /* Start Generation */
#define I2C_CR1_STOP            ((uint16_t)0x0200)    /* Stop Generation */
#define I2C_CR1_ACK             ((uint16_t)0x0400)    /* Acknowledge enable */
#define I2C_CR1_SWRST           ((uint16_t)0x8000)    /* Software reset */

/* I2C SR1 flags */
#define I2C_SR1_SB              ((uint16_t)0x0001)    /* Start bit (Master mode) */
#define I2C_SR1_ADDR            ((uint16_t)0x0002)    /* Address sent/matched */
#define I2C_SR1_BTF             ((uint16_t)0x0004)    /* Byte transfer finished */
#define I2C_SR1_RXNE            ((uint16_t)0x0040)    /* Data register not empty */
#define I2C_SR1_TXE             ((uint16_t)0x0080)    /* Data register empty */
#define I2C_SR1_BERR            ((uint16_t)0x0100)    /* Bus error */
#define I2C_SR1_ARLO            ((uint16_t)0x0200)    /* Arbitration lost */
#define I2C_SR1_AF              ((uint16_t)0x0400)    /* Acknowledge failure */
#define I2C_SR1_OVR             ((uint16_t)0x0800)    /* Overrun/Underrun */
#define I2C_SR1_TIMEOUT         ((uint16_t)0x4000)    /* Timeout */

/* I2C SR2 flags */
#define I2C_SR2_MSL             ((uint16_t)0x0001)    /* Master/Slave */
#define I2C_SR2_BUSY            ((uint16_t)0x0002)    /* Bus busy */
#define I2C_SR2_TRA             ((uint16_t)0x0004)    /* Transmitter/Receiver */

/* Higher-level flag aliases */
#define I2C_FLAG_SB             I2C_SR1_SB
#define I2C_FLAG_ADDR           I2C_SR1_ADDR
#define I2C_FLAG_BTF            I2C_SR1_BTF
#define I2C_FLAG_RXNE           I2C_SR1_RXNE
#define I2C_FLAG_TXE            I2C_SR1_TXE
#define I2C_FLAG_BERR           I2C_SR1_BERR
#define I2C_FLAG_ARLO           I2C_SR1_ARLO
#define I2C_FLAG_AF             I2C_SR1_AF
#define I2C_FLAG_OVR            I2C_SR1_OVR

extern I2C_TypeDef *I2C_Global;

typedef enum 
{
    I2C_Direction_Transmitter = 0,
    I2C_Direction_Receiver    = 1
} I2C_Direction;

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendAddress(uint8_t address, I2C_Direction direction);
uint8_t I2C_WriteData(uint8_t data);
uint8_t I2C_ReadData(ACK_Status ack);

void I2C_Master_Transmit(uint8_t addr, uint8_t *data, uint16_t len);
void I2C_Master_Receive(uint8_t addr, uint8_t *buffer, uint16_t len);

void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif // __I2C_H
