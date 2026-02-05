#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"

#define SSD1306_I2C_ADDR 0x78
#define SSD1306_TIMEOUT 200

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_PIXELS_PER_BYTE 8

#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / SSD1306_PIXELS_PER_BYTE)

#define SSD1306_OP_LOW_COLUMN_START_BASE 0x00
#define SSD1306_OP_HIGH_COLUMN_START_BASE 0x10

#define SSD1306_OP_SET_MEM_MODE 0x21
#define SSD1306_OP_SET_COLUMN 0x21
#define SSD1306_OP_SET_PAGE 0x22

#define SSD1306_OP_START_LINE_ADDR_BASE 0x40

#define SSD1306_OP_SET_CONTRAST 0x81

#define SSD1306_OP_SET_CHARGE_PUMP 0x8D

#define SSD1306_OP_SEGMENT_NORMAL_MODE 0xA0
#define SSD1306_OP_SEGMENT_REMAP_MODE 0xA1

#define SSD1306_OP_DISPLAY_RAM_MODE 0xA4
#define SSD1306_OP_DISPLAY_NON_RAM_MODE 0xA5

#define SSD1306_OP_DISPLAY_NORMAL_MODE 0xA6
#define SSD1306_OP_DISPLAY_INVERTED_MODE 0xA7

#define SSD1306_OP_SET_MULTIPLEX 0xA8

#define SSD1306_OP_TURN_OFF 0xAE
#define SSD1306_OP_TURN_ON 0xAF

#define SSD1306_OP_PAGE_START_BASE 0xB0

#define SSD1306_OP_COM_NORMAL_MODE 0xC0
#define SSD1306_OP_COM_REMAP_MODE 0xC8

#define SSD1306_OP_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_OP_SET_CLOCK_AND_OSCILLATOR 0xD5
#define SSD1306_OP_SET_PRE_CHARGE_PERIOD 0xD9
#define SSD1306_OP_SET_COM_PIN_CONFIG 0xDA
#define SSD1306_OP_SET_VCOMH 0xDB

#define SSD1306_MEM_MODE_PAGE 0
#define SSD1306_MEM_MODE_HORIZONTAL 1
#define SSD1306_MEM_MODE_VERTICAL 2

#define SSD1306_CHARGE_PUMP_OFF 0b010000
#define SSD1306_CHARGE_PUMP_ON 0b010100

#define SSD1306_VCOMH_0_64_VCC (0b000 << 4)
#define SSD1306_VCOMH_0_77_VCC (0b010 << 4)
#define SSD1306_VCOMH_0_83_VCC (0b011 << 4)

typedef enum ssd1306_color {
    BLACK = 0,
    WHITE = 1,
} ssd1306_color_t;

typedef struct ssd1306 {
    I2C_HandleTypeDef* i2c_handle;
    uint8_t* buffer;

    bool inverted;
} ssd1306_t;

bool ssd1306_init(ssd1306_t* screen, I2C_HandleTypeDef* handle);
void ssd1306_command(ssd1306_t* screen, uint8_t command);

void ssd1306_set_contrast(ssd1306_t* screen, uint8_t contrast);
void ssd1306_set_inverted(ssd1306_t* screen, bool inverted);

void ssd1306_draw(ssd1306_t* screen);
void ssd1306_fill(ssd1306_t* screen, ssd1306_color_t color);
void ssd1306_set_pixel(ssd1306_t* screen, uint8_t x, uint8_t y, ssd1306_color_t color);


