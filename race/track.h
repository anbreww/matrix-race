/**
 * @file    track.h
 * @author  Andrew Watson (andy@watsons.ch)
 * @brief   Functions for advancing the track and loading segments into memory.
 * @date    October 2011
 * @version 0.1
 *
 */

// define track in flash

// provide functions to load a track segment into a variable
void track_increment_position(void);

uint8_t track_load_line(uint8_t _line);
