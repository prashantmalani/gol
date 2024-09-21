/*
 * Unit tests for various functions used in the main program.
 */

#include <stdbool.h>
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

    // Dead cell case.
    return (live_neighbours == 3);
}

struct calcStateTestCase {
    int arr[3][3];
    bool result;
};

struct calcStateTestCase cases[] = {
    // Case 1
    {
        {{1,1,1},
         {1,0,1},
         {1,0,1}},
        false,
    },
    // Case 2
    {
        {{1,0,1},
         {1,0,1},
         {1,0,1}},
        false,
    },
    // Case 3
    {
        {{0,0,1},
         {0,0,1},
         {0,0,1}},
        true,
    },
    // Case 4
    {
        {{0,1,1},
         {0,0,1},
         {0,0,0}},
        true,
    },
    // Case 5
    {
        {{1,1,1},
         {0,1,1},
         {0,0,0}},
        false,
    },
    // Case 6
    {
        {{0,1,1},
         {0,1,1},
         {1,0,0}},
        false,
    },
    // Case 7
    {
        {{0,1,1},
         {0,1,1},
         {1,0,1}},
        false,
    },
    // Case 8
    {
        {{0,1,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    // Case 9
    {
        {{0,1,0},
         {1,1,0},
         {0,0,0}},
        true,
    },
    // Case 10
    {
        {{0,1,0},
         {1,1,0},
         {0,1,0}},
        true,
    },
    // Case 11
    {
        {{0,0,1},
         {0,1,0},
         {1,0,0}},
        true,
    },
    // Case 12
    {
        {{1,0,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    // Case 12
    {
        {{1,1,1},
         {0,1,0},
         {0,0,0}},
        true,
    },
    // Case 13
    {
        {{0,0,1},
         {0,1,1},
         {0,0,1}},
        true,
    },
    // Case 14
    {
        {{0,0,0},
         {0,1,0},
         {0,0,1}},
        false,
    },
    // Case 15
    {
        {{0,0,0},
         {0,1,0},
         {1,0,0}},
        false,
    },
};

// Series of tests that verifies that calcState works correctly.
void testCalcState() {
    printf("Running calcState test cases.\n");
    for (int i = 0; i < (int)(sizeof(cases) / sizeof(cases[0])); i++) {
        if (calcState(cases[i].arr) != cases[i].result)
            printf("Calc state case %d failed\n", i + 1);
    }
}

int main() {
    testCalcState();
}
