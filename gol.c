/* State checking logic */
#include "gol.h"

#include <stdio.h>

/*
 * Given an 3*3 grid, determines what's the outcome for the
 * center cell.
 * We can assume the grid dimensions to be fixed at 3, since
 * the Game Of Life Rules only look a neighbouring cells.
 *
 * Args:
 *  arr: 3x3 array with current cells' state.
 *
 * Returns:
 *  false if center cell is dead for the next tick.
 *  true if center cell is alive for the next tick.
 */
bool calcState(const int arr[3][3]) {
    int live_neighbours = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1)
                continue;
            if (arr[i][j] == 1)
                live_neighbours++;
        }
    }

    bool is_live = !!arr[1][1];

    if (is_live) {
        if (live_neighbours < 2)
            return false;
        else if (live_neighbours == 2 || live_neighbours == 3)
            return true;
        else
            return false;
    }

    /* Dead cell case. */
    return (live_neighbours == 3);
}

/*
 * extendArray
 *
 *
 * In order to avoid dealing with complicated index wrapping cases, we "extend"
 * the array by duplication the last row before the first row (and vice versa),
 * and the last column, before the first colum (and vice version).
 * We also copy diagonal elements to the opposite diagonal location.
 * That way, creating a 3x3 matrix of neighbours becomes vastly simplified.
 *
 * Args:
 *  in: input array of original size.
 *  out: output array which has had it's size extended.
 *
 * NOTE: Caller is assumed to allocate |in| and |out| arrays appropriately.
 */
void extendArray(const int in[][COLS], int out[][COLS+2]) {
    /* Copy the actual array. */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            out[i+1][j+1] = in[i][j];
        }
    }

    /* Copy the last row to the beginning of the array, and vice versa. */
    for (int j = 0; j < COLS; j++) {
        out[0][j+1] = in[ROWS-1][j];
        out[ROWS+1][j+1] = in[0][j];
    }

    /* Copy the last column to the first and vice versa. */
    for (int i = 0; i < ROWS; i++) {
        out[i+1][0] = in[i][COLS - 1];
        out[i+1][COLS+1] = in[i][0];
    }

    /* Copy the diagonal elements over. */
    out[0][0] = in[ROWS-1][COLS-1];
    out[ROWS+1][COLS+1] = in[0][0];
    out[ROWS+1][0] = in[0][COLS-1];
    out[0][COLS+1] = in[ROWS-1][0];
}

/* Given the 8x8 array and a particular location, fill out a 3x3 array
 * centered at the location and its neighbours. This makes it easier to
 * assess each cell, by taking care of any wrapping issues in this code.
 *
 * Args:
 *  arr = Input (ROW+2) * (COLS+2)  array
 *  out = Output 3x3 array
 *  row, col = Row, Column location of the cell **in the original array**.
 *
 *  Returns:
 *   void
 *
 * NOTE: |out| expected to be allocated appropriately by the caller.
 *
 */
void getNeighbours(const int arr[][COLS+2], int **out, int row, int col) {
    row++;
    col++;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            out[i][j] = arr[row-1+i][col-1+j];
        }
    }
}
