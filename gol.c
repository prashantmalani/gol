/* State checking logic */
#include "gol.h"

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

    // Dead cell case.
    return (live_neighbours == 3);
}
