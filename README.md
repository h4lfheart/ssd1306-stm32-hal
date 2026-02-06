ssd1306-stm32-hal - An STM32 HAL driver for the SSD1306 display
------------------------------------------

## Usage
 
```c
#include "ssd1306.h"
#include "fonts/font_8x8.h"
#include "fonts/font_16x16.h"

I2C_HandleTypeDef i2c_handle; // initialize this yourself

// init the screen with your i2c handle
ssd1306_t screen = {};
if (!ssd1306_init(&screen, &i2c_handle))
    return 1;

// fill the screen
ssd1306_fill(&screen, BLACK);

// draw a pixel
ssd1306_set_pixel(&screen, 5, 5, WHITE);

// draw text
ssd1306_draw_text(&screen, &font_8x8, "ssd1306 is", 0, 0);
ssd1306_draw_text_aligned(&screen, &font_16x16, "goated", 32, ALIGN_CENTER); // with alignment :O

// each byte is a column, LSB is the top, MSB is the bottom
const uint8_t smiley[] = {
    0b00000000,
    0b00100000,
    0b01001000,
    0b01000000,
    0b01000000,
    0b01001000,
    0b00100000,
    0b00000000
};

// draw smiley bitmap :)
ssd1306_draw_bitmap(&screen, smiley, 64, 48, 8, 8);

// set the contrast/brightness
ssd1306_set_contrast(&screen, 0xFF);

// draw the framebuffer to the screen
ssd1306_update(&screen);
```

## Planned Features
- Screen Initialization Options