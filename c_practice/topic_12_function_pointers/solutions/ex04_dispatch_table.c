/*
 * ex04_dispatch_table.c - Use an array of handlers for command IDs.
 * Key concept: table dispatch replaces long switch statements.
 */
#include <stdio.h>

typedef void (*CommandHandler_t)(void);

static void cmd_start(void) { puts("start"); }
static void cmd_stop(void)  { puts("stop"); }
static void cmd_status(void){ puts("status: ok"); }

int main(void)
{
    CommandHandler_t table[] = {cmd_start, cmd_stop, cmd_status};
    for (size_t id = 0U; id < sizeof(table) / sizeof(table[0]); id++) {
        table[id]();
    }
    return 0;
}
