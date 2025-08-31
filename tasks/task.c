#include "task.h"
#include "button.h"

static void GPIO_Config(void)
{
    RCC_APB2ClockCmd(RCC_APB2_GPIOB | RCC_APB2_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio =
    {
        .Mode = GPIO_MODE_OP_PP,
        .Pin = GPIO_PIN_0,
        .Speed = GPIO_SPEED_50MHZ
    };
    GPIO_Init(GPIOB, &gpio);

    gpio.Pin = GPIO_PIN_13;
    GPIO_Init(GPIOC, &gpio);
}

static void LedBlinkTasks(const uint32_t u32time)
{
    static uint32_t prevMillis = 0;
    const uint32_t interval = u32time;

    if ((millis() - prevMillis) >= u32time)
    {
        prevMillis = millis();
        GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}

static void LedButtonTasks(void)
{
    static Bool prev = FALSE;
    Bool curr = READ_Button1();
    if (curr == TRUE && prev == FALSE)
    {
        uint32_t t0 = millis();
        while ((millis() - t0) < 20)
        {
        }
        if (READ_Button1() == TRUE)
        {
            GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        }
    }
    prev = curr;
}

void setup()
{
    RCC_CLOCK(RCC_CLOCK_SYS_72MHz);
    SysTick_Init();
    Button_Init(GPIOA);
    GPIO_Config();
}

void loop()
{
    LedBlinkTasks(1000);
    LedButtonTasks();
}
