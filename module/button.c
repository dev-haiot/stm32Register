#include "button.h"
#include "systick.h"

static const uint16_t btn_pins[BTN_COUNT] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4};
static GPIO_TypeDef *button_port = GPIOA; // default port

void Button_Init(GPIO_TypeDef *GPIOx)
{
    GPIO_InitTypeDef cfg = {0};

    // enable clock for selected port
    if (GPIOx == GPIOA)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_APB2ClockCmd(RCC_APB2_GPIOC, ENABLE);
    }
    cfg.Mode = GPIO_MODE_IPU;
    cfg.Speed = GPIO_SPEED_50MHZ;

    for (uint8_t i = 0; i < BTN_COUNT; i++)
    {
        cfg.Pin = btn_pins[i];
        GPIO_Init(GPIOx, &cfg);
    }

    button_port = GPIOx;
}

uint8_t Button_ReadRaw(uint8_t idx)
{
    if (idx >= BTN_COUNT)
    {
        return 0;
    }
    return GPIO_ReadPin(button_port, btn_pins[idx]);
}

Bool Button_Read(uint8_t idx)
{
    static uint8_t lastStableState[BTN_COUNT] = {1, 1, 1, 1, 1}; // mặc định thả (1 do pull-up)
    static uint8_t lastReading[BTN_COUNT] = {1, 1, 1, 1, 1};
    static uint32_t lastDebounceTime[BTN_COUNT] = {0};

    if (idx >= BTN_COUNT)
        return FALSE;

    uint8_t reading = Button_ReadRaw(idx);

    if (reading != lastReading[idx])
    {
        lastDebounceTime[idx] = millis();
    }

    if ((millis() - lastDebounceTime[idx]) > 20)
    {
        lastStableState[idx] = reading;
    }

    lastReading[idx] = reading;

    return (lastStableState[idx] == 0) ? TRUE : FALSE;
}

Bool READ_Button0(void) { return Button_Read(0); }
Bool READ_Button1(void) { return Button_Read(1); }
Bool READ_Button2(void) { return Button_Read(2); }
Bool READ_Button3(void) { return Button_Read(3); }
Bool READ_Button4(void) { return Button_Read(4); }
