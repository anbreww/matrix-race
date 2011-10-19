// Track.c : functions for browsing the track

#include <avr/io.h>

uint8_t LOAD(uint16_t _position)
{
	return 0b00100000;
}
