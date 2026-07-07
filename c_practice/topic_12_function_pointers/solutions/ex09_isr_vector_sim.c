/*
 * ex09_isr_vector_sim.c - Simulate an interrupt vector table.
 * Key concept: interrupt dispatch is commonly table-based.
 */
#include <stdio.h>

typedef void (*IrqHandler_t)(void);

static void default_handler(void) { puts("default IRQ"); }
static void timer_irq(void)       { puts("timer IRQ"); }
static void uart_irq(void)        { puts("uart IRQ"); }

int main(void)
{
    IrqHandler_t vector[] = {default_handler, timer_irq, uart_irq};
    vector[1]();
    vector[2]();
    return 0;
}
