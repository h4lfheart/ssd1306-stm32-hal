ssd1306-stm32-hal - An STM32 HAL driver for the SSD1306 display
------------------------------------------

## Usage
 
```c
#include "ssd1306.h"
#include "fonts.h"

I2C_HandleTypeDef i2c_handle; // initialize this yourself

// init the screen with your i2c handle
ssd1306_t screen = {};
if (!ssd1306_init(&screen, &i2c_handle))
    return 1;

// fill the screen
ssd1306_fill(&screen, BLACK);

// draw a pixel
ssd1306_set_pixel(&screen, 5, 5, WHITE);

// set the contrast/brightness
ssd1306_set_contrast(&screen, 0xFF);

// draw the framebuffer to the screen
ssd1306_draw(&screen);
```

## Planned Features
- Screen Initialization Options
- Font Definitions + Rendering
- Bitmap Rendering