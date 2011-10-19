/***********************************
 *
 *  LED Matrix Racing Game
 *  Andrew Watson 2011
 *  
 **********************************/

#include <avr/io.h>
#include "matrix/matrix.h"
#include "race/track.h"

uint8_t car_pos = 0;
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
        matrix_clear();

        // display car
        matrix_set_line(0,car_pos,RED); // set bottom line with one red dot

		uint8_t i;
        // load 8 track segments
        for(i=0; i<8; i++)
        {
            uint8_t line = 0;
            // load segment
            line = LOAD(track_pos + i); // TODO : complete stub

            matrix_set_line(i,line,GREEN);
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
    // timers for display refreshing and score counting?
	return;
}
