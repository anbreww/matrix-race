#include <avr/io.h>
#include "matrix.h"

void _display_next_line(void);

/**
 * for double-buffering, let's store two tables of 8x8 pixels in RAM
 */
uint8_t _green_buffer[2][8] = {
    {
        0b00001000,
        0b00011000,
        0b00101000,
        0b00001000,
        0b00001000,
        0b00001000,
        0b00111110,
        0b00000000
    },
    {
        0b00011100,
        0b00100010,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00111110,
        0b00000000
    }
};

uint8_t _red_buffer[2][8] = {
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    },
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000
    }
};

volatile uint8_t _active_buffer = 1;
#define draw_buffer (1-_active_buffer)
#define disp_buffer (_active_buffer)

// temporary test function
void matrix_test()
{
    _display_next_line();
}


//! Initialisation functions
void init_matrix(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0x00;
    return;
}


void matrix_clear(void)
{
    return;
}

void matrix_set_line(uint8_t line_id, uint8_t values, uint8_t colour)
{
    // since orange == 3, this covers all cases
    if(colour & M_RED)
    {
        _red_buffer[draw_buffer][line_id] = values;
    }
    if(colour & M_GREEN)
    {
        _green_buffer[draw_buffer][line_id] = values;
    }
    return;
}

/*
 * Bitmask function
 * used to set, toggle, clear bits in a buffer
 */
#define BITMASK_AND    1
#define BITMASK_OR     2
#define BITMASK_XOR    3
void _matrix_bitmask(uint8_t line_id, uint8_t values,
                     uint8_t colour, uint8_t function)
{
    // since orange == 3, this covers all cases
    if(colour & M_RED)
    {
        if(function == BITMASK_AND)
            _red_buffer[draw_buffer][line_id] &= values;
        else if(function == BITMASK_OR)
            _red_buffer[draw_buffer][line_id] |= values;
        else if(function == BITMASK_XOR)
            _red_buffer[draw_buffer][line_id] ^= values;
    }
    if(colour & M_GREEN)
    {
        if(function == BITMASK_AND)
            _green_buffer[draw_buffer][line_id] &= values;
        else if(function == BITMASK_OR)
            _green_buffer[draw_buffer][line_id] |= values;
        else if(function == BITMASK_XOR)
            _green_buffer[draw_buffer][line_id] ^= values;
    }

    return;
}


void switch_buffers(void)
{
    _active_buffer ^= 1;
}

/**
 * @brief   flips the order of bits in a byte
 *
 * @todo    this function is crap. re-implement in assembler!
 */
uint8_t flip_bits(uint8_t _byte)
{
    uint8_t i, output=0;
    uint8_t mask = 0b00000001;
    uint8_t en_mask = 0b10000000;
    for(i=0; i<8; i++)
    {
        if((_byte & mask))
        {
            output |= en_mask;
        }
        en_mask >>= 1;
        mask <<= 1;
    }
    return output;
}

// **** CALLBACKS ****

/**
 * @brief  Callback to be called after every line refresh
 *
 * @param line_pos  current line (0-7)
 * @todo    replace this function with a pointer to a callback
 */
void line_callback(uint8_t line_pos)
{
    // this function will be called after every line
    return;
}

/**
 * @brief  Callback to be called at the end of a frame
 *
 * @todo    replace this function with a pointer to a callback
 */
void frame_callback(void)
{
    static uint16_t frame_counter = 0;
    // this function will be called at the end of every frame
    
    frame_counter++;
    return;
}


/**
 * @brief   load the next line from the buffer and display it
 *
 * @todo    call this function on a 800 Hz timer 
 */
void _display_next_line(void)
{
    static uint8_t line_pos = 0;

    // set anodes corresponding to current line
    ANODE_PORT = ~_BV(line_pos);

    // load a line from the buffer and display it
    GREEN_PORT = flip_bits(_green_buffer[_active_buffer][line_pos]);
    RED_PORT =   flip_bits(  _red_buffer[_active_buffer][line_pos]);

    line_pos++;
    // call line_callback(line_pos);

    if(line_pos >= 8)
    {
        line_pos = 0;

        // call frame_callback(frame_number);
    }
}
