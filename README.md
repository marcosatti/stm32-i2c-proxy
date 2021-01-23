# STM32 I2C Proxy
Demonstration project for using the I2C protocol between 3 devices.

This program demonstrates both the usage of the STM32 device becoming a I2C master and slave, using the HAL library.

Upon startup, it will drive a ssd1306 display as the I2C bus master, printing a waiting message. It will then pause for 3 seconds, allowing another I2C device to control the bus. If a byte of data is sent to the slave address of this STM32 device during this time, it will then reacquire the bus and drive the ssd1306 display and output the value of the byte. If a byte was not sent while waiting, it will print an error message instead.

There is a slight pause between becoming the I2C bus master / slave in order for voltage levels to stabilize.

You must ensure that there is no I2C device controlling the bus whilst the STM32 device is driving the display, otherwise you may experience problems.

This program was developed alongside the [i2c-proxy](https://github.com/marcosatti/i2c-proxy) Linux Kernel module, and was tested using a BeagleBone Black SBC and a Blue Pill MCU. See that project for more information on the BeagleBone Black side.

## HAL Config
After running `make hal_config`, enable the following modules/drivers in the MCU config header file.

```
#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
```

## Circuit Schematic
See [here](https://github.com/marcosatti/stm32-i2c-example) for the project that this is extended off. Follow the same directions as in that. Place the other I2C master on the same SCL / SDA lines. If using a BeagleBone Black, this is pin 19 (SCL) / pin 20 (SDA) on the P9 header.

By default, this program sets up the STM32 device to receive a byte of data on I2C address 0x20.

## Prerequisites:
- [STM32Cube MCU Package](https://www.st.com/en/embedded-software/stm32cube-mcu-mpu-packages.html)
    - Requires a sign-in to ST in order to download.
- ARM embedded toolchain
    - On x86_64 Fedora, run `sudo dnf install arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-newlib` (installs a cross-compilation toolchain).
- STLink flashing tool
    - On x86_64 Fedora, run `sudo dnf install stlink`.
- GNU Make
    - On x86_64 Fedora, run `sudo dnf install make`.
- tr
    - On x86_64 Fedora, run `sudo dnf install coreutils` (most likely already installed).

## Blue Pill Quick Start
1. Download and extract the STM32Cube firmware package for your MCU, and update the `CUBE_PATH` variable to point to it.
2. Run `make hal_config`, making sure to change the configuration afterwards.
3. Run `make` to build the project.
4. Run `make flash` to flash the binary.

## SSD1306 Library
Uses the driver library found [here](https://github.com/afiskon/stm32-ssd1306), originally distributed under the MIT licence. Many thanks to the author(s)! Parts of it modified and/or removed as they are not needed.
```
MIT License

Copyright (c) 2018 Aleksander Alekseev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Licence
GPLv3+  
See LICENCE.md for a full copy of the licence text.
