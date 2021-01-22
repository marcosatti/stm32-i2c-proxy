#include <stdio.h>
#include MCU_HEADER
#include "config.h"
#include "system.h"
#include "gpio.h"
#include "i2c.h"
#include "ssd1306.h"

void main(void)
{
    hal_init();
    clock_init();
    led_init();
    i2c_init();

    while (HAL_I2C_IsDeviceReady(&I2C_INSTANCE, SSD1306_I2C_ADDR, 1, 100) != HAL_OK) {
        set_led(1);
        HAL_Delay(100);
        set_led(0);
        HAL_Delay(100);
    }

    ssd1306_Init();
    set_led(1);

    while (1) {
        ssd1306_Fill(Black);

        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString("Waiting for", Font_6x8, White);
        ssd1306_SetCursor(0, 8);
        ssd1306_WriteString("I2C master", Font_6x8, White);
        ssd1306_UpdateScreen();

        uint8_t value;
        char buffer[16];

        if (HAL_I2C_Slave_Receive(&I2C_INSTANCE, &value, 1, 10000) != HAL_OK) {
            uint32_t error = HAL_I2C_GetError(&I2C_INSTANCE);
            sprintf(buffer, "Error: %d", error);
        } else {
            sprintf(buffer, "Ok: 0x%X", value);
        }
        
        ssd1306_SetCursor(0, 32);
        ssd1306_WriteString(buffer, Font_6x8, White);
        ssd1306_UpdateScreen();
        HAL_Delay(3000);
    }
}
