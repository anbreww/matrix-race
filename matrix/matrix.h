/**
 * @file    matrix.h
 * @author  Andrew Watson (andy@watsons.ch)
 * @brief   Functions to draw stuff in the buffer.
 */

#define M_OFF   0   //!< not used
#define M_RED   1   //!< Act on red buffer
#define M_GREEN 2   //!< Act on green buffer
#define M_ORANGE 3  //!< Act on both buffers

#define ANODE_PORT  PORTA   //!< Anode port is active low
#define ANODE_DDR   DDRA

#define RED_PORT    PORTB   //!< Red cathodes (active high)
#define GREEN_PORT  PORTC   //!< Green cathodes (active high)
#define RED_DDR     DDRB
#define GREEN_DDR   DDRC


//! Initialisation functions
void init_matrix(void);

void matrix_clear(void);

/**
 *  Functions to draw on the matrix.
 *  What do we want to be able to do?
 *  -# Use function 5 (bitmask) for the low level part.
 *  -# Clear the whole matrix
 *  -# Clear only one colour
 *  -# Set a pixel to a given colour, regardless of what colour it is
 *  -# Toggle a pixel (green/off, red/off, red/green)
 *      -# What happens if a pixel is green and we want to toggle red-off?
 *      -# Does it go green-red-off-red, green-off-red-off or green-orange..?
 *  -# Bitmasks on a line (and, or, xor)
 *      -# one mask for green, one mask for red
 *  -# read pixels of a line (red or green), returns uint8
 *  -# read a pixel (returns OFF, RED, GREEN)
 *
 *  -# optional : provide the same functionality as lines on the columns
 *  -# to think about : do this directly, or double-buffer?
 *
 */

void matrix_set_line(uint8_t line_id, uint8_t values, uint8_t colour);

// temporary test function
void matrix_test(void);

void switch_buffers(void);
