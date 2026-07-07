/*
 * ex06_protocol_parser.c - Parse a simple framed packet: 0xAA len payload.
 * Key concept: byte parsers naturally fit FSMs.
 */
#include <stdint.h>
#include <stdio.h>

typedef enum { WAIT_SYNC, WAIT_LEN, READ_PAYLOAD } ParseState_t;

int main(void)
{
    uint8_t bytes[] = {0x00U, 0xAAU, 3U, 'O', 'K', '!'};
    ParseState_t state = WAIT_SYNC;
    uint8_t len = 0U;
    uint8_t count = 0U;
    char payload[8];

    for (size_t i = 0U; i < sizeof(bytes); i++) {
        uint8_t b = bytes[i];
        switch (state) {
        case WAIT_SYNC:
            if (b == 0xAAU) {
                state = WAIT_LEN;
            }
            break;
        case WAIT_LEN:
            len = b;
            count = 0U;
            state = READ_PAYLOAD;
            break;
        case READ_PAYLOAD:
            payload[count++] = (char)b;
            if (count == len) {
                payload[count] = '\0';
                printf("payload: %s\n", payload);
                state = WAIT_SYNC;
            }
            break;
        }
    }
    return 0;
}
