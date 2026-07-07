/*
 * ex10_lookup_table.c - Convert numeric code to text.
 * Key concept: lookup tables are clear and fast for small maps.
 */
#include <stdio.h>

typedef struct {
    int code;
    const char *name;
} CodeName_t;

int main(void)
{
    const CodeName_t table[] = {{0, "OK"}, {1, "BUSY"}, {2, "ERROR"}};
    int code = 2;
    for (size_t i = 0U; i < sizeof(table) / sizeof(table[0]); i++) {
        if (table[i].code == code) {
            puts(table[i].name);
        }
    }
    return 0;
}
