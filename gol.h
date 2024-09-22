#include <stdbool.h>

#define ROWS 8
#define COLS 8

bool calcState(const int arr[3][3]);
void extendArray(const int in[ROWS][COLS], int out[ROWS+2][COLS+2]);
void getNeighbours(const int arr[ROWS+2][COLS+2], int out[3][3], int row, int col);
