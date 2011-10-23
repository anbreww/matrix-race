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
void setup_interrupts(void);

volatile struct Flags {
        int game_running:1;
        
} flags;

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
        
        flags.game_running = 1;

    // Start loop
    while(flags.game_running == 1)
    {
        // reset display
        //matrix_clear();
        matrix_test();

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

void move_car_right(void)
{
    if(car_pos > 0x01)
        car_pos >>= 1;
    else
        car_pos = 0x01;
}

void move_car_left(void)
{
    if(car_pos < 0x80)
        car_pos <<= 1;
    else
        car_pos = 0x80;
}

/**
 * @todo Replace button values with more meaningful names 
 */
// interrupt routine for buttons
ISR(PCINT3_vect)
{
    DDRD = 0x00;

    uint8_t input = PIND;

    if((input & _BV(2)) == 0)
    {
        move_car_left();
    }
    else if((input & _BV(7)) == 0)
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
