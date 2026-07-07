/*
 * ex06_struct_with_handler.c - Store a handler inside a driver object.
 * Key concept: function pointers can be struct members.
 */
#include <stdio.h>

typedef void (*WriteFn_t)(const char *text);

typedef struct {
    const char *name;
    WriteFn_t write;
} Console_t;

static void uart_write(const char *text)
{
    printf("UART: %s\n", text);
}

int main(void)
{
    Console_t console = {.name = "USART2", .write = uart_write};
    console.write(console.name);
    return 0;
}
