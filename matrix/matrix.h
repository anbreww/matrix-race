/**
 * @file matrix.h
 * @author Andrew Watson (andy@watsons.ch)
 * @date 2011-10-24
 * @version 0.1
 *
 * @brief  Functions to draw stuff in the matrix buffer.
 *
 * What do we want to be able to do?
 * -# Use function 5 (bitmask) for the low level part.
 * -# Clear the whole matrix
 * -# Clear only one colour
 * -# Set a pixel to a given colour, regardless of what colour it is
 * -# Toggle a pixel (green/off, red/off, red/green)
 *     -# What happens if a pixel is green and we want to toggle red-off?
 *     -# Does it go green-red-off-red, green-off-red-off or green-orange..?
 * -# Bitmasks on a line (and, or, xor)
 *     -# one mask for green, one mask for red
 * -# read pixels of a line (red or green), returns uint8
 * -# read a pixel (returns OFF, RED, GREEN)
 * -# optional : provide the same functionality as lines on the columns
 * -# to think about : do this directly, or double-buffer?
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

#define BUTTON_DDR  DDRD    
#define BUTTON_PORT PORTD   //!< Buttons are active low!
#define BUTTON_PIN  PIND

#define BTN_1   2
#define BTN_2   3
#define BTN_3   6
#define BTN_4   7

/**
 * \def BUTTON_PRESSED(button)
 *
 * Tells you if \a button is currently pressed
 *
 * @returns 1 if true, 0 otherwise
 */
#define BUTTON_PRESSED(button)  ((BUTTON_PIN & _BV(button)) == 0)

/**
 * Sets port directions
 */
void init_matrix(void);


/**
 * @brief  Clears entire buffer
 */
void matrix_clear(void);


/**
 * @brief  Set the pixels of a given line
 *
 * @param line_id   Matrix line (0 = bottom, 7 = top)
 * @param values    One byte containing pixel values
 * @param colour    Can be either M_RED, M_RED or M_ORANGE
 */
void matrix_set_line(uint8_t line_id, uint8_t values, uint8_t colour);

/**
 * @brief  temporary test function
 */
void matrix_test(void);

/**
 * @brief  Switch buffers around.
 *
 * You might want to be careful when calling this function, to do it at the end
 * of a frame, to avoid glitches.
 */
void switch_buffers(void);
