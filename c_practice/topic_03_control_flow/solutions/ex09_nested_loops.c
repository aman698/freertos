/*
 * ex09_nested_loops.c — Scan 4x4 key matrix
 * Key concept: nested for loops walk rows and columns.
 */
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* 1 = key pressed at row,col */
    const uint8_t matrix[4][4] = {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };

    int found_row = -1;
    int found_col = -1;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (matrix[row][col] != 0U) {
                found_row = row;
                found_col = col;
                break;
            }
        }
        if (found_row >= 0) {
            break;
        }
    }

    if (found_row >= 0) {
        printf("Key pressed at row=%d col=%d\n", found_row, found_col);
    } else {
        printf("No key pressed\n");
    }

    return 0;
}
