#include "task2.h"
#include <string.h>



/* ---------------------------------------------------------------------------
 * ----- M A I N -------------------------------------------------------------
 * ---------------------------------------------------------------------------*/

int main(void)
{
    // Get current window dimensions (size)
    // """"""""""""""""""""""""""""""""""""
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &curWinSize);
    lastWinSize = curWinSize;

    // Set shorthand names for window dimension numbers
    // also cut the number of columns by half
    // cause of the additional spaces printed to seprarate chars
    // """""""""""""""""""""""""""""""""""""""""""""""""""""""""
    ushort_t rows = curWinSize.ws_row,
                   cols = curWinSize.ws_col / 2;
    last_allocated_rows_count = rows;
    last_allocated_cols_count = cols;

    // Allocate array in respect to window dimensions
    // """"""""""""""""""""""""""""""""""""""""""""""
    char ** matrix = calloc( rows, sizeof(char*) );
    for (ushort_t i = 0; i < rows; ++i)
        matrix[i] = calloc( cols, sizeof(char) );

    matrix_rand_letters_fill (matrix, rows, cols);

    /* ------- START REVOLUTION -------- */
    start_revolution( matrix, rows, cols );

    return 0;
}

// ===========================================================================

// ---------------------------------------------------------------------------

void
matrix_rand_letters_fill
(
    char ** p_matrix,
    ushort_t rows, ushort_t cols
)
{
    // Iterate 2D array using single loop
    // """"""""""""""""""""""""""""""""""
	for (ushort_t i=0, j=0; i < rows; ++j)
	{
		p_matrix[i][j] = LETTER_LIST[ rand() % LETTERS_COUNT ];;
		(j >= cols-1) && ++i && (j = -1);
	}
}

// ---------------------------------------------------------------------------

void
row_rand_letters_fill (ushort_t cols, char * row)
{
    for (ushort_t j=0; j < cols; ++j)
	{
		row[j] = LETTER_LIST[ rand() % LETTERS_COUNT ];
	}
}

// ---------------------------------------------------------------------------

void allocErrorExit()
{
    fprintf( stderr,
        "Failed to reallocate memory at: line %d in %s\n\n",
        __LINE__, __FILE__
    );
    exit(267);
}

// ---------------------------------------------------------------------------

void
on_winsize_changed( char *** p_matrix )
{
    // Current window dimensions
    // """""""""""""""""""""""""
    ushort_t newsize_rows = curWinSize.ws_row * 2;
    ushort_t newsize_cols = (curWinSize.ws_col /2) * 2;

    ushort_t last_rows = last_allocated_rows_count;
    ushort_t last_cols = last_allocated_cols_count;

    // When size of window rows more than array can hold
    // """""""""""""""""""""""""""""""""""""""""""""""""
    if ( curWinSize.ws_row > last_allocated_rows_count )
    {
        // Create temporary pointer to avoid corruption and loss
        // of the matrix pointer
        // In case of successfull reallocation change the pointer
        // """""""""""""""""""""""""""""""""""""""""""""""""""""
        char ** matrix = (char**) realloc(
            *p_matrix,
            sizeof(char*) * newsize_rows
        );
        
        // If allocation failed print some info and exit
        // """""""""""""""""""""""""""""""""""""""""""""
        if (matrix == NULL)
            allocErrorExit();
        *p_matrix = matrix;

        // Allocate spapce for new rows
        // """"""""""""""""""""""""""""
        ushort_t _i = last_rows - 1;
        for (; _i < newsize_rows; ++_i)
        {
            (*p_matrix)[_i] = (char*) malloc(newsize_cols * sizeof(char));
            if ( (*p_matrix)[_i] == NULL )
                allocErrorExit();
        }

        last_allocated_rows_count = newsize_rows;
    }
    
    // Amount of columsns changed
    if ( (curWinSize.ws_col ) > last_cols )
    {
        for (ushort_t _i = 0; _i < last_rows; ++_i)
        {
            char * tmp = (char*) realloc((*p_matrix)[_i], (newsize_cols) * sizeof(char));
            if (tmp == NULL)
                allocErrorExit();
            (*p_matrix)[_i] = tmp;
        }
        last_allocated_cols_count = newsize_cols;
    }
}

// ---------------------------------------------------------------------------

void
start_revolution(
    char ** p_matrix,
    ushort_t rows, ushort_t cols)
{
    // Fill matrix with pseudo-random letters from predefined list
    // """""""""""""""""""""""""""""""""""""""""""""""""""""""""""
    matrix_rand_letters_fill( p_matrix, rows, cols );

    // This will point out
    // if the window size was cahnged durring the iteration
    // """"""""""""""""""""""""""""""""""""""""""""""""""""
    bool_t b_winsize_changed;

    // This specifies the matrix row shift
    // from which to start printing the whole matrix at each iteration
    // this is for new rows to be generated
    // and stored in the same matrix array without additional arrays
    // """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
    ushort_t row_shift = 0;
    
    // Tracks amount of rows left to print
    // on each drawing (matrix print) step
    // """""""""""""""""""""""""""""""""""
    ushort_t rows_counter = rows;

    // Counters for rows and columns
    // """""""""""""""""""""""""""""
    ushort_t i = 0, j=0;



    // Global loop that generates new rows
    // """""""""""""""""""""""""""""""""""
    while (1)
	{
        // Set green text color
        // """"""""""""""""""""
        printf("\033[32m");
        b_winsize_changed = 0;

        // Print(draw) matrix to the screen
        // """"""""""""""""""""""""""""""""
        for (i = (rows - row_shift - 1), j = 0; rows_counter; ++j)
        {
            // Get current window size
            // """""""""""""""""""""""
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &curWinSize);

            if (
                 curWinSize.ws_row != lastWinSize.ws_row ||
                 curWinSize.ws_col != lastWinSize.ws_col )
            {
                b_winsize_changed = 1;
            }

            // When window size is altered
            // trigger matrix resize action
            // """"""""""""""""""""""""""""
            on_winsize_changed(&p_matrix);
            if (b_winsize_changed) // stop printing matrix columns
                break;

            // Print column
            printf("%c ", p_matrix[i][j]);

            // On each iteration check if all row is passed
			// If row is passed (j > cols) then check some other coditions
            // """""""""""""""""""""""""""""""""""""""""""""""""""""""""""
			(   
				(j >= cols-1)
                    // Move to the next row and reset column counter
                    && ++i && (j = -1)
                    // Print new line at the end of the current row
                    && printf("\n")
			)
			&&
            // If i is out of array boundary (i > rows)
            // """"""""""""""""""""""""""""""""""""""""
			(
                // Rows left to iterate
                ( rows_counter-- )
                // reset current row index position
                // if it crosses the array boundary
                && (i >= rows) && (i = 0)
			); 
        }        
        // Clear the screen
        printf("\033c");

        // Generate new row at the end of the array
        // with current position shift
        // """"""""""""""""""""""""""""""""""""""""
        row_rand_letters_fill (cols, p_matrix[rows-row_shift-1]);

        // In case window has been resized reset the counters and start over
        // """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
        if (b_winsize_changed)
        {
            rows = curWinSize.ws_row;
            cols = curWinSize.ws_col / 2;
            rows_counter = rows - 1;
            row_shift=0;
            lastWinSize.ws_row = curWinSize.ws_row;
            lastWinSize.ws_col = curWinSize.ws_col;

            matrix_rand_letters_fill (p_matrix, rows, cols);
            continue;
        }

        // Reset rows counter so the loop that prints the matrix
        // can exit at the right time
        // """""""""""""""""""""""""""""""""""""""""""""""""""""
        rows_counter = rows;
        
        // Reset shift when it's out of the boundary (current_index > last)
        // """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
        ++row_shift;
        (row_shift >= rows) && (row_shift = 0);
        
        // Introduce some latency before next drawing (matrix printing)
        // """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""
        usleep(LATENCY);
	}

}

// ---------------------------------------------------------------------------