#include "ssd1306.h"

void ssd1306_init_commands(ssd1306_t* screen) {

    ssd1306_command(screen, SSD1306_OP_TURN_OFF);

    ssd1306_command(screen, SSD1306_OP_SET_MEM_MODE);
        ssd1306_command(screen, SSD1306_MEM_MODE_PAGE);

    ssd1306_command(screen, SSD1306_OP_PAGE_START_BASE | 0x0);

    ssd1306_command(screen, SSD1306_OP_COM_REMAP_MODE);

    ssd1306_command(screen, SSD1306_OP_LOW_COLUMN_START_BASE | 0x0);
    ssd1306_command(screen, SSD1306_OP_HIGH_COLUMN_START_BASE | 0x0);
    ssd1306_command(screen, SSD1306_OP_START_LINE_ADDR_BASE);

    ssd1306_set_contrast(screen, 0xFF);

    ssd1306_command(screen, SSD1306_OP_SEGMENT_REMAP_MODE);

    ssd1306_set_inverted(screen, false);

    ssd1306_command(screen, SSD1306_OP_SET_MULTIPLEX);
        ssd1306_command(screen, SSD1306_HEIGHT - 1); // set multiplex ratio to max screen height

    ssd1306_command(screen, SSD1306_OP_DISPLAY_RAM_MODE);

    ssd1306_command(screen, SSD1306_OP_SET_DISPLAY_OFFSET);
        ssd1306_command(screen, 0x00); // TODO investigate different values

    ssd1306_command(screen, SSD1306_OP_SET_CLOCK_AND_OSCILLATOR);
        ssd1306_command(screen, (0xF) << 4 | (0x0)); // set freq to 0xF (reset) and divide ratio to 0x0 (none)

    ssd1306_command(screen, SSD1306_OP_SET_PRE_CHARGE_PERIOD);
        ssd1306_command(screen, (0x2) << 4 | (0x2)); // set phase 1 and 2 to 2

    ssd1306_command(screen, SSD1306_OP_SET_VCOMH);
        ssd1306_command(screen, SSD1306_VCOMH_0_77_VCC);

    // what does this do ??
    ssd1306_command(screen, SSD1306_OP_SET_CHARGE_PUMP);
        ssd1306_command(screen, SSD1306_CHARGE_PUMP_ON);

    ssd1306_command(screen, SSD1306_OP_TURN_ON);
}

bool ssd1306_init(ssd1306_t* screen, I2C_HandleTypeDef* handle) {
    if (screen == NULL || handle == NULL)
        return false;

    *screen = (ssd1306_t) {
            .i2c_handle = handle,
            .buffer = calloc(1, SSD1306_BUFFER_SIZE),
    };

    if (HAL_I2C_IsDeviceReady(handle, SSD1306_I2C_ADDR, 1, SSD1306_TIMEOUT) != HAL_OK)
        return false;

    ssd1306_init_commands(screen);

    ssd1306_fill(screen, BLACK);

    ssd1306_draw(screen);

    return true;
}

void ssd1306_command(ssd1306_t* screen, uint8_t command) {
    HAL_I2C_Mem_Write(
            screen->i2c_handle,
            SSD1306_I2C_ADDR,
            0x00,
            1,
            &command,
            1,
            SSD1306_TIMEOUT
    );
}

void ssd1306_set_contrast(ssd1306_t* screen, uint8_t contrast) {
    ssd1306_command(screen, SSD1306_OP_SET_CONTRAST);
    ssd1306_command(screen, contrast);
}

void ssd1306_set_inverted(ssd1306_t* screen, bool inverted) {
    screen->inverted = inverted;

    ssd1306_command(screen, inverted ? SSD1306_OP_DISPLAY_INVERTED_MODE : SSD1306_OP_DISPLAY_NORMAL_MODE);
}

void ssd1306_draw(ssd1306_t* screen) {
    ssd1306_command(screen, SSD1306_OP_SET_COLUMN);
    ssd1306_command(screen, 0); // start column
    ssd1306_command(screen, 127); // end column

    ssd1306_command(screen, SSD1306_OP_SET_PAGE);
    ssd1306_command(screen, 0); // start page
    ssd1306_command(screen, 7); // end page

    HAL_I2C_Mem_Write(
            screen->i2c_handle,
            SSD1306_I2C_ADDR,
            0x40,
            1,
            screen->buffer,
            SSD1306_BUFFER_SIZE,
            SSD1306_TIMEOUT
    );
}

void ssd1306_fill(ssd1306_t* screen, ssd1306_color_t color) {
    memset(screen->buffer, color == WHITE ? 0xFF : 0x00, SSD1306_BUFFER_SIZE);
}

void ssd1306_set_pixel(ssd1306_t* screen, uint8_t x, uint8_t y, ssd1306_color_t color) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
        return;

    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    uint16_t byte_index = x + (page * SSD1306_WIDTH);

    if (color == WHITE) {
        screen->buffer[byte_index] |= (1 << bit);
    } else {
        screen->buffer[byte_index] &= ~(1 << bit);
    }
}