#ifndef ___TASK2_H___
#define ___TASK2_H___
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>



/* TYPEDEF SECTION
 ---------------------------------------------------------------------------*/

 // Create alias for <winsize> structure that defines terminal window size
 // """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
typedef struct winsize WinSize;
typedef unsigned short ushort_t;
typedef char bool_t;



/* PREPROCESSOR SECTION
 ---------------------------------------------------------------------------*/

// Delay before new row generation and printing
// """"""""""""""""""""""""""""""""""""""""""""
#define LATENCY ((useconds_t) 1000*100)

// Letter set for futher random selection from this set
// """"""""""""""""""""""""""""""""""""""""""""""""""""
#define LETTERS_COUNT 18
const char LETTER_LIST[LETTERS_COUNT] = 
{
    'A', 'B', 'C', 'D', 'E', 'F',
    '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9','*','&'
};

// Stores the amount of matrix rows after reallocation
// this is done to avoid constant reallocation
// on every single window size change
// """""""""""""""""""""""""""""""""""""""""""""""""""
ushort_t last_allocated_rows_count;
ushort_t last_allocated_cols_count;

// Create structure that will hold tereminal window dimensions
// """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
WinSize curWinSize;
WinSize lastWinSize;



/* PROTOTYPES SECTION
 ---------------------------------------------------------------------------*/

/* FUNCTION: get_random_letter
 * ---------------------------
 * > Returns a pseudo-random letter chosen from the predefined set:
 * >    LETTER_LIST
 * ---------------------------
 * @RETURNS { char }
 * ---------------------------
 */
char get_random_letter ();


/* FUNCTION: matrix_rand_letters_fill
 * ---------------------------
 * > Fills up the given matrix with pseudo-random set of letters
 * > which are chosen by <get_random_letter> from LETTER_LIST
 * ---------------------------
 * @param { void * } - p_matrix
 * |    pointer to a 2D array that needs to be filled
 * @param { int } - rows
 * |    amount of rows the array has
 * @param { int } - cols
 * |    amount of columns the array has
 * ---------------------------
 * @RETURNS: { void }
 * ---------------------------   
 */
void matrix_rand_letters_fill (char ** p_matrix, ushort_t rows, ushort_t cols);


/* FUNCTION: matrix_rand_letters_fill
 * ---------------------------
 * > Fills up the given row/array with pseudo-random set of letters
 * > which are chosen by <get_random_letter> from LETTER_LIST
 * ---------------------------
 * @param { int } - cols
 * |    amount of items the array has
 * @param { char [] } - row
 * |    pointer to a row (can be 1D array) that needs to be filled
 * ---------------------------
 * @RETURNS: { void }
 * ---------------------------   
 */
void row_rand_letters_fill (ushort_t cols, char * row);


/* FUNCTION: matrix_rand_letters_fill
 * ---------------------------
 * > Prints given matrix to the screen one time.
 * > Infinite loop then continues to generate row from random letters
 * > and print whole matrix again (after each new row is generated).
 * >
 * > In this way we achieve letters to fall down not up 
 * ---------------------------
 * @param { void * } - p_matrix
 * |    pointer to a 2D array that needs to be filled
 * @param { int } - rows
 * |    amount of rows the array has
 * @param { int } - cols
 * |    amount of columns the array has
 * ---------------------------
 * @RETURNS: { void }
 * ---------------------------   
 */
void start_revolution (char ** p_matrix, ushort_t rows, ushort_t cols);


/* FUNCTION: matrix_rand_letters_fill
 * ---------------------------
 * > Prints info and exits from program
 * > in case the of matrix reallocation failure
 * ---------------------------
 */
void allocErrorExit();


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // ___TASK2_H___