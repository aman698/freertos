/**
 * Topic 06 - Exercise 03: Two-dimensional array (row-major)
 * STM32 context: 8x8 LED matrix framebuffer
 * Build: gcc ex03_2d_array.c -o ex03 && ./ex03
 */
#include <stdio.h>
#include <stdint.h>

#define ROWS 8U
#define COLS 8U

static void matrix_set(uint8_t matrix[ROWS][COLS], uint8_t row, uint8_t col, uint8_t on)
{
    if (row < ROWS && col < COLS) {
        matrix[row][col] = on;
    }
}

static void matrix_print(const uint8_t matrix[ROWS][COLS])
{
    for (uint8_t r = 0U; r < ROWS; r++) {
        for (uint8_t c = 0U; c < COLS; c++) {
            printf("%c", matrix[r][c] ? '#' : '.');
        }
        printf("\n");
    }
}

int main(void)
{
    uint8_t led_matrix[ROWS][COLS] = { 0 };

    matrix_set(led_matrix, 3U, 4U, 1U);
    matrix_set(led_matrix, 3U, 3U, 1U);
    matrix_set(led_matrix, 4U, 4U, 1U);

    /* Row-major linear index for (3,4): 3*COLS + 4 */
    size_t linear = 3U * COLS + 4U;
    printf("Linear index of pixel (3,4) = %zu\n\n", linear);
    matrix_print(led_matrix);
    return 0;
}
