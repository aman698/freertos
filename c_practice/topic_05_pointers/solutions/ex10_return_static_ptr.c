/*
 * ex10_return_static_ptr.c — Return pointer to static storage (not stack!)
 * Key concept: only return pointers to static/global or caller-owned memory.
 */
#include <stdint.h>
#include <stdio.h>

static const char *get_device_name(void)
{
    static const char name[] = "NUCLEO-F411RE";
    return name;  /* OK — static string persists */
}

int main(void)
{
    const char *dev = get_device_name();
    printf("Device: %s\n", dev);
    return 0;
}
