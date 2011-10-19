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

void matrix_set_line(uint8_t line_id, uint8_t values, uint8_t colour);