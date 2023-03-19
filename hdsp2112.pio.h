// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------------ //
// display_char //
// ------------ //

#define display_char_wrap_target 1
#define display_char_wrap 5

static const uint16_t display_char_program_instructions[] = {
    0xbf42, //  0: nop                    side 1 [15]
            //     .wrap_target
    0xd024, //  1: irq    wait 4          side 1     
    0x7061, //  2: out    null, 1         side 1     
    0x7007, //  3: out    pins, 7         side 1     
    0xaa42, //  4: nop                    side 0 [10]
    0xba42, //  5: nop                    side 1 [10]
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program display_char_program = {
    .instructions = display_char_program_instructions,
    .length = 6,
    .origin = -1,
};

static inline pio_sm_config display_char_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + display_char_wrap_target, offset + display_char_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}
#endif

// ------------ //
// set_char_pos //
// ------------ //

#define set_char_pos_wrap_target 0
#define set_char_pos_wrap 10

static const uint16_t set_char_pos_program_instructions[] = {
            //     .wrap_target
    0xc025, //  0: irq    wait 5                     
    0xe020, //  1: set    x, 0                       
    0x20c4, //  2: wait   1 irq, 4                   
    0xa001, //  3: mov    pins, x                    
    0xc044, //  4: irq    clear 4                    
    0xa049, //  5: mov    y, !x                      
    0x0087, //  6: jmp    y--, 7                     
    0xa02a, //  7: mov    x, !y                      
    0xe048, //  8: set    y, 8                       
    0x00a2, //  9: jmp    x != y, 2                  
    0xaa42, // 10: nop                           [10]
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program set_char_pos_program = {
    .instructions = set_char_pos_program_instructions,
    .length = 11,
    .origin = -1,
};

static inline pio_sm_config set_char_pos_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + set_char_pos_wrap_target, offset + set_char_pos_wrap);
    return c;
}
#endif

// -------------- //
// select_display //
// -------------- //

#define select_display_wrap_target 0
#define select_display_wrap 3

static const uint16_t select_display_program_instructions[] = {
            //     .wrap_target
    0x20c5, //  0: wait   1 irq, 5                   
    0x607d, //  1: out    null, 29                   
    0x6003, //  2: out    pins, 3                    
    0xc045, //  3: irq    clear 5                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program select_display_program = {
    .instructions = select_display_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config select_display_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + select_display_wrap_target, offset + select_display_wrap);
    return c;
}

#include "hardware/clocks.h"
#define HDSP2112_DATA_PINS_NUM  7
#define HDSP2112_ADDR_PINS_NUM  3
#define HDSP2112_CE_PINS_NUM    3
#define HDSP2112_PIO_DISPLAY_CHAR_SM   0
#define HDSP2112_PIO_SET_CHAR_POS_SM   1
#define HDSP2112_PIO_SELECT_DISPLAY_SM 2
static inline void hdsp2112_program_init(PIO pio, uint data_pins_base,
                                         uint addr_pins_base, uint ce_pins_base,
                                         uint write_pin)
{
    uint8_t i;
    for (i = 0; i < HDSP2112_DATA_PINS_NUM; i++)
    {
        pio_gpio_init(pio, data_pins_base + i);
    }
    for (i = 0; i < HDSP2112_ADDR_PINS_NUM; i++)
    {
        pio_gpio_init(pio, addr_pins_base + i);
    }
    for (i = 0; i < HDSP2112_CE_PINS_NUM; i++)
    {
        pio_gpio_init(pio, ce_pins_base + i);
    }
    pio_gpio_init(pio, write_pin);
    pio_sm_set_consecutive_pindirs(pio, HDSP2112_PIO_DISPLAY_CHAR_SM,
                                   data_pins_base, HDSP2112_DATA_PINS_NUM,
                                   true);
    pio_sm_set_consecutive_pindirs(pio, HDSP2112_PIO_DISPLAY_CHAR_SM,
                                   write_pin, 1, true);
    pio_sm_set_consecutive_pindirs(pio, HDSP2112_PIO_SET_CHAR_POS_SM,
                                   addr_pins_base, HDSP2112_ADDR_PINS_NUM,
                                   true);
    pio_sm_set_consecutive_pindirs(pio, HDSP2112_PIO_SELECT_DISPLAY_SM,
                                   ce_pins_base, HDSP2112_CE_PINS_NUM,
                                   true);
    pio_sm_config c;
    uint offs0 = pio_add_program(pio, &display_char_program);
    c = display_char_program_get_default_config(offs0);
    sm_config_set_out_shift(&c, false, true, 8);
    sm_config_set_out_pins(&c, data_pins_base, HDSP2112_DATA_PINS_NUM);
    sm_config_set_sideset_pins(&c, write_pin);
    sm_config_set_clkdiv(&c, 100.0);
    pio_sm_init(pio, HDSP2112_PIO_DISPLAY_CHAR_SM, offs0, &c);
    uint offs1 = pio_add_program(pio, &set_char_pos_program);
    c = set_char_pos_program_get_default_config(offs1);
    sm_config_set_out_shift(&c, false, false, 32);
    sm_config_set_out_pins(&c, addr_pins_base, HDSP2112_ADDR_PINS_NUM);
    sm_config_set_clkdiv(&c, 100.0);
    pio_sm_init(pio, HDSP2112_PIO_SET_CHAR_POS_SM, offs1, &c);
    uint offs2 = pio_add_program(pio, &select_display_program);
    c = select_display_program_get_default_config(offs2);
    sm_config_set_out_shift(&c, false, true, 32);
    sm_config_set_out_pins(&c, ce_pins_base, HDSP2112_CE_PINS_NUM);
    sm_config_set_clkdiv(&c, 100.0);
    pio_sm_init(pio, HDSP2112_PIO_SELECT_DISPLAY_SM, offs2, &c);
    // pio_sm_set_enabled(pio, HDSP2112_PIO_DISPLAY_CHAR_SM, true);
    // pio_sm_set_enabled(pio, HDSP2112_PIO_SET_CHAR_POS_SM, true);
    // pio_sm_set_enabled(pio, HDSP2112_PIO_SELECT_DISPLAY_SM, true);
    pio_set_sm_mask_enabled(pio, 0x07, true);
}

#endif

