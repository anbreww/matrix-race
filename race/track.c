// Track.c : functions for browsing the track

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "../utils/track-0.h"

#include "track.h"

// the position in the track is handled by this file.
// it will return a position on the track and auto-wrap around the edges.
volatile uint16_t _start_position = 0;

void track_increment_position(void)
{
    _start_position++;
    if(_start_position > TRACK_LENGTH)
        _start_position = 0;
}

#define LOAD(_position)  pgm_read_byte_near(&race_track[_position]);

uint8_t track_load_line(uint8_t _line)
{
    uint8_t result = 0;

    if(_start_position + _line > TRACK_LENGTH)
    {
        result = LOAD(_start_position + _line - TRACK_LENGTH);
    }
    else
    {
        result = LOAD(_start_position + _line);
    }

    return result;
}

