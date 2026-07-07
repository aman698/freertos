/**
 * Topic 06 - Exercise 08: Parse comma-separated values
 * STM32 context: parse config string from BLE module
 * Build: gcc ex08_parse_csv.c -o ex08 && ./ex08
 */
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

static int parse_three_uints(const char *s, uint16_t *a, uint16_t *b, uint16_t *c)
{
    unsigned va = 0U, vb = 0U, vc = 0U;
    int matched = 0;

    while (*s && isspace((unsigned char)*s)) {
        s++;
    }

    matched = sscanf(s, "%u,%u,%u", &va, &vb, &vc);
    if (matched != 3) {
        return -1;
    }

    *a = (uint16_t)va;
    *b = (uint16_t)vb;
    *c = (uint16_t)vc;
    return 0;
}

int main(void)
{
    const char *cfg = " 12,34,56 ";
    uint16_t x, y, z;

    if (parse_three_uints(cfg, &x, &y, &z) == 0) {
        printf("Parsed: x=%u y=%u z=%u\n", x, y, z);
    } else {
        printf("Parse failed\n");
    }
    return 0;
}
