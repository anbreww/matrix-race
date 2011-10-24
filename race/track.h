/**
 * @file    track.h
 * @author  Andrew Watson (andy@watsons.ch)
 * @brief   Functions for advancing the track and loading segments into memory.
 * @date    October 2011
 * @version 0.1
 *
 */

/**
 * @brief  Move forward in the track
 *
 * This function automatically keeps track of the length of the race track, and
 * will wrap around the end when needed. You only need to make sure that the
 * first and last piece of track are compatible or the gameplay will be a
 * little... surprising!
 */
void track_increment_position(void);

/**
 * @brief  Load a line from the track stored in program memory
 *
 * @param _line position of the line, from the current starting position
 *
 * @returns one byte containing the pixels for the line requested.
 *
 * This function also keeps track of line length, and will wrap around the end
 * of the track. If for example the track is 300 lines long and you ask for line
 * 302, it will return line number 2. \a _line should be between 0 and 7
 * normally, for the 8x8 led matrix.
 */
uint8_t track_load_line(uint8_t _line);
