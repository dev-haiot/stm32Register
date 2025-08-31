#ifndef __BUTTON_H
#define __BUTTON_H

#include "gpio.h"
#include "rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BTN_COUNT 5 /* A0..A4 */

    void Button_Init(GPIO_TypeDef *GPIOx);

    Bool Button_Read(uint8_t idx);

    uint8_t Button_ReadRaw(uint8_t idx);

    Bool READ_Button0(void);
    Bool READ_Button1(void);
    Bool READ_Button2(void);
    Bool READ_Button3(void);
    Bool READ_Button4(void);

#ifdef __cplusplus
}
#endif

#endif // __BUTTON_H