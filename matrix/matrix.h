/*
// Matrix Module
// 
// Provides basic functions to use the LED matrix module
*/

#define M_OFF 0
#define RED 1
#define GREEN 2
#define BLUE 3

//! Initialisation functions
void init_matrix(void);

void matrix_clear(void);

//! Functions to draw on the matrix.
// What do we want to be able to do?
// 0. Use function 5 (bitmask) for the low level part.
// 1. Clear the whole matrix
// 2. Clear only one colour
// 3. Set a pixel to a given colour, regardless of what colour it is
// 4. Toggle a pixel (green/off, red/off, red/green)
//  - What happens if a pixel is green and we want to toggle red-off?
//  - Does it go green-red-off-red, green-off-red-off or green-orange..?
// 5. Bitmasks on a line (and, or, xor)
//  - one mask for green, one mask for red
// 6. read pixels of a line (red or green), returns uint8
// 7. read a pixel (returns OFF, RED, GREEN)

// 8. optional : provide the same functionality as lines on the columns
// 9. to think about : do this directly, or double-buffer?

// memory requirements : 8Bytes for red, 8 bytes for green = 16 bytes.
// req for double-buffering : 32 bytes.
// total memory : 512 bytes.
// 16 bytes : 3.125%
// 32 bytes : 6.25 % - seems acceptable

void matrix_set_line(uint8_t line_id, uint8_t values, uint8_t colour);
