/*
 * ex10_payload_limits.c - Check payload sizes against the TP session limit.
 * Key concept: 255 packets * 7 data bytes caps a BAM/RTS session at 1785 bytes.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define TP_DATA_BYTES_PER_PACKET 7U
#define TP_MAX_PACKETS           255U
#define TP_MAX_PAYLOAD_BYTES     (TP_DATA_BYTES_PER_PACKET * TP_MAX_PACKETS)
#define TP_MIN_PAYLOAD_BYTES     9U /* 9+ bytes need transport protocol; <=8 fits one frame */

static bool j1939_payload_size_ok(uint16_t size)
{
    return (size >= TP_MIN_PAYLOAD_BYTES) && (size <= TP_MAX_PAYLOAD_BYTES);
}

static void check_and_print(uint16_t size)
{
    printf("size=%u bytes -> %s\n", size, j1939_payload_size_ok(size) ? "OK" : "REJECTED");
}

int main(void)
{
    printf("TP_MAX_PAYLOAD_BYTES = %u\n", (unsigned int)TP_MAX_PAYLOAD_BYTES);

    check_and_print(8U);    /* below TP minimum, use single frame instead */
    check_and_print(9U);    /* smallest valid TP payload */
    check_and_print(1785U); /* exact maximum */
    check_and_print(1786U); /* one byte over maximum */

    return 0;
}
