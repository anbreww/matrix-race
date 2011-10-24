/**
 * @file    main.c
 * @author  Andrew Watson (andy@watsons.ch)
 * @brief   A simple car race for Robopoly's LED matrix module.
 * @date    October 2011
 * @version 0.1
 *
 * This fairly simple example should provide you with a base if you wish to
 * begin developing applications for the LED matrix module that I made for the
 * PRisme2 platform. The main file contains the game logic. This project also
 * contains separate files to house the matrix write and refresh functions, as
 * well as handle advancing and generating pieces of track.
 */

#define F_CPU 14745600

#include <avr/io.h>
#include "matrix/matrix.h"
#include "race/track.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t car_pos = 0;
//volatile uint16_t frame_delay = 100;

uint8_t track_pos = 0; // tracks up to 256 lines

void game_init(void);
void game_start_sequence(void);
void setup_interrupts(void);
void check_for_collisions(void);

volatile struct Flags {
        int game_running:1;
        int collision:1;
        
} game_flags;

int main(void)
{
    // LED matrix race game
    
    init_matrix();

    uint16_t frame_counter = 0;

    /*
     * BEGINNING OF GAME - inits
     */
    game_init();
    setup_interrupts();

    game_start_sequence();
        
        game_flags.game_running = 1;

    // Start loop
    while(game_flags.game_running == 1)
    {
        // reset display
        matrix_clear();

        // display car
        matrix_set_line(0,car_pos,M_RED); // set bottom line with one red dot

        uint8_t i;
        // load 8 track segments
        for(i=0; i<8; i++)
        {
            uint8_t line = 0;
            // load segment
            line = track_load_line(i);

            matrix_set_line(i,line,M_GREEN);
        }

        _delay_ms(1);

        check_for_collisions();
        if (game_flags.collision == 1) {
            // draw a **sadface**
            matrix_set_line(6, 0b00100100, M_RED);
            matrix_set_line(5, 0b00100100, M_RED);
            matrix_set_line(3, 0b00011000, M_RED);
            matrix_set_line(2, 0b00100100, M_RED);
            matrix_set_line(1, 0b00000000, M_RED);
        }

        // redraw screen
        //switch_buffers();
        frame_counter++;
        if(frame_counter == 100)
        {
            switch_buffers();
            frame_counter = 0;
            track_increment_position();
        }
    }

    return 0; // never reached

}

void game_init(void)
{
    // init car position
    car_pos = 0b00010000;

    // reset pointer to race track
    track_pos = 0;
}

/**
 * @brief  Start sequence : flashing lights!
 */
void game_start_sequence(void)
{
    // First step : a red square
    matrix_clear();
    matrix_set_line(3,0b11000000,M_RED);
    matrix_set_line(4,0b11000000,M_RED);
    switch_buffers();

    _delay_ms(500);

    // second step : two red squares
    matrix_clear();
    matrix_set_line(3,0b11011000,M_RED);
    matrix_set_line(4,0b11011000,M_RED);
    switch_buffers();

    _delay_ms(500);

    // third step : three red squares
    matrix_clear();
    matrix_set_line(3,0b11011011,M_RED);
    matrix_set_line(4,0b11011011,M_RED);
    switch_buffers();

    _delay_ms(500);

    // finally : all green
    matrix_clear();
    matrix_set_line(3,0b11011011,M_GREEN);
    matrix_set_line(4,0b11011011,M_GREEN);
    switch_buffers();

    _delay_ms(500);

    // and go!
    return;
}



/**
 * @brief   Set up pin change interrupts for the buttons
 *
 * @todo    Move button interrupt logic into matrix file and register callbacks
 */
void setup_interrupts(void)
{
    // interrupts for left and right buttons
    PCICR |= (1<<PCIE3);

    PCMSK3 |= (1<<PCINT26);
    PCMSK3 |= (1<<PCINT27);
    PCMSK3 |= (1<<PCINT30);
    PCMSK3 |= (1<<PCINT31);
    sei();
    // timers for display refreshing and score counting?
        return;
}

void check_for_collisions(void)
{
    uint8_t track = track_load_line(0);
    if( (car_pos & track) != 0)
    {
        // we have a collision!
        game_flags.collision = 1;
    } else {
        game_flags.collision = 0;
    }

}

/**
 * @brief  Move the car to the right, stop if we hit the wall.
 */
void move_car_right(void)
{
    if(car_pos > 0x01)
        car_pos >>= 1;
    else
        car_pos = 0x01;

    check_for_collisions();
}


/**
 * @brief  Move the car to the left, stop if we hit the wall.
 */
void move_car_left(void)
{
    if(car_pos < 0x80)
        car_pos <<= 1;
    else
        car_pos = 0x80;

    check_for_collisions();
}

/**
 * @brief Interrupt routine from buttons
 *
 * This routine is called on a pin change interrupt. It's incapable of
 * differentiating between different buttons when it's called, so we decode the
 * button presses inside the function. We'll also try to do some debouncing.
 */
ISR(PCINT3_vect)
{
    DDRD = 0x00;

    if( BUTTON_PRESSED(BTN_1) )
    {
        move_car_left();
    }
    else if( BUTTON_PRESSED(BTN_4) )
    {
        move_car_right();
    }
    /*
    if((input & _BV(3)) == 0)
    {
        frame_delay -= 10;
    }
    if((input & _BV(6)) == 0)
    {
        frame_delay += 10;
    }
    */
}
