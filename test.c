/*
 * Unit tests for various functions used in the main program.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gol.h"

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

const int extendArrayTest[][COLS] = {
    {1,1,1,0,1,0,1,0},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,1,1},
    {0,1,1,0,1,1,0,0},
    {1,1,1,0,1,0,1,1},
    {0,1,1,0,1,1,1,0},
    {0,0,1,0,1,0,1,0},
    {0,1,1,0,1,1,1,1},
};

const int extendArrayResult[][COLS+2] = {
    {1,0,1,1,0,1,1,1,1,0},
    {0,1,1,1,0,1,0,1,0,1},
    {0,0,1,1,0,1,1,0,0,0},
    {1,0,1,1,0,1,1,1,1,0},
    {0,0,1,1,0,1,1,0,0,0},
    {1,1,1,1,0,1,0,1,1,1},
    {0,0,1,1,0,1,1,1,0,0},
    {0,0,0,1,0,1,0,1,0,0},
    {1,0,1,1,0,1,1,1,1,0},
    {0,1,1,1,0,1,0,1,0,1},
};

// Series of tests that verifies that calcState works correctly.
void testCalcState() {
    printf("Running calcState test cases.\n");
    for (int i = 0; i < (int)(sizeof(cases) / sizeof(cases[0])); i++) {
        if (calcState(cases[i].arr) != cases[i].result)
            printf("Calc state case %d failed\n", i + 1);
    }
}

// Tests that the code used to expand the array works correctly.
void testExtendArray() {
    printf("Running extendArray test case.\n");
    int **arr = malloc(sizeof(int *) * (ROWS+2));
    if (!arr) {
        perror("Failed to allocate memory.\n");
        return;
    }

    for (int i = 0; i < ROWS+2; i++) {
        arr[i] = malloc(sizeof(int) * (COLS+2));
        if (!arr[i]) {
            perror("Failed to allocate memory for a row.\n");
            return;
        }
    }

    extendArray(extendArrayTest, arr);

    for (int i = 0; i < ROWS+2; i++) {
        for (int j = 0; j < COLS+2; j++) {
            if (arr[i][j] != extendArrayResult[i][j]) {
                return;
            }
        }
    }
}

int main() {
    testCalcState();
    testExtendArray();
}
