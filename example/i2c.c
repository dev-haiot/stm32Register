#include "i2c.h"
#include "rcc.h"
#include "gpio.h"

I2C_TypeDef *I2C_Global = I2C1; // Default to I2C1

/* Internal helper */
static void I2C_WaitFlagSet(uint16_t flag)
{
    while (!(I2C_Global->SR1 & flag))
        ;
}

static void I2C_GPIO_Init(void)
{
    if (I2C_Global == I2C1)
    {
        RCC_APB1ClockCmd(RCC_APB1_I2C1, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7; // PB6=SCL, PB7=SDA
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
    else if (I2C_Global == I2C2)
    {
        RCC_APB1ClockCmd(RCC_APB1_I2C2, ENABLE);
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11; // PB10=SCL, PB11=SDA
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_50MHZ;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

/* Tính toán clock cho I2C */
static void I2C_ConfigClock(uint32_t pclk1, uint32_t speed)
{
    uint16_t ccr, trise;

    // Set CR2 (PCLK1 frequency in MHz)
    I2C_Global->CR2 = (pclk1 / 1000000);

    if (speed <= 100000) // Standard mode (≤100kHz)
    {
        ccr = (pclk1 / (speed << 1));
        if (ccr < 4)
            ccr = 4; // RM0008: CCR ≥ 4 in SM
        trise = (pclk1 / 1000000) + 1;
    }
    else // Fast mode (≤400kHz)
    {
        I2C_Global->CCR |= (1 << 15);  // FS = 1 (Fast mode)
        I2C_Global->CCR &= ~(1 << 14); // Duty = 0 => Tlow/Thigh = 2
        ccr = (pclk1 / (speed * 3));
        trise = ((pclk1 / 1000000) * 300 / 1000) + 1; // = Freq(MHz)*300ns + 1
    }

    I2C_Global->CCR = ccr & 0x0FFF;
    I2C_Global->TRISE = trise & 0x3F;
}

void I2C_Init(void)
{
    I2C_GPIO_Init();

    I2C_Global->CR1 = 0; // Reset CR1

    // PCLK1 = 36 MHz (STM32F103 default), speed = 100kHz
    I2C_ConfigClock(36000000, 100000);

    I2C_Global->CR1 |= I2C_CR1_PE; // Enable I2C
}

void I2C_Start(void)
{
    I2C_Global->CR1 |= I2C_CR1_START;
    while (!(I2C_Global->SR1 & I2C_SR1_SB))
        ;
}

void I2C_Stop(void)
{
    I2C_Global->CR1 |= I2C_CR1_STOP;
}

void I2C_SendAddress(uint8_t address, I2C_Direction direction)
{
    I2C_Global->DR = (address << 1) | (direction & 0x01);

    while (!(I2C_Global->SR1 & I2C_SR1_ADDR))
        ;
    (void)I2C_Global->SR2; // Clear ADDR
}

uint8_t I2C_WriteData(uint8_t data)
{
    I2C_Global->DR = data;

    while (!(I2C_Global->SR1 & I2C_SR1_TXE))
        ;

    if (I2C_Global->SR1 & I2C_SR1_AF)
    {
        I2C_Global->SR1 &= ~I2C_SR1_AF;
        I2C_Global->CR1 |= I2C_CR1_STOP;
        return 1; // Fail
    }
    return 0; // Success
}

uint8_t I2C_ReadData(ACK_Status ack)
{
    if (ack == I2C_ACK)
        I2C_Global->CR1 |= I2C_CR1_ACK;
    else
        I2C_Global->CR1 &= ~I2C_CR1_ACK;

    while (!(I2C_Global->SR1 & I2C_SR1_RXNE))
        ;
    return I2C_Global->DR;
}

/* High-level functions */
void I2C_Master_Transmit(uint8_t addr, uint8_t *data, uint16_t len)
{
    I2C_Start();
    I2C_SendAddress(addr, I2C_Direction_Transmitter);

    for (uint16_t i = 0; i < len; i++)
    {
        I2C_WriteData(data[i]);
    }
    I2C_Stop();
}

void I2C_Master_Receive(uint8_t addr, uint8_t *buffer, uint16_t len)
{
    I2C_Start();
    I2C_SendAddress(addr, I2C_Direction_Receiver);

    for (uint16_t i = 0; i < len; i++)
    {
        if (i == (len - 1))
        {
            buffer[i] = I2C_ReadData(I2C_NACK);
            I2C_Stop();
        }
        else
        {
            buffer[i] = I2C_ReadData(I2C_ACK);
        }
    }
}
