/*
 * ex07_rts_cts.c - Simulate an RTS/CTS flow-controlled transport session.
 * Key concept: CTS grants a batch of packets at a time, unlike unsolicited BAM.
 */
#include <stdint.h>
#include <stdio.h>

#define RTS_CONTROL_BYTE 0x10U
#define CTS_CONTROL_BYTE 0x11U
#define EOM_ACK_BYTE     0x13U
#define ABORT_BYTE       0xFFU
#define TOTAL_PACKETS    5U

static void send_rts(uint8_t total_packets)
{
    printf("TX -> RTS: total_packets=%u, control=0x%02X\n", total_packets, RTS_CONTROL_BYTE);
}

static uint8_t send_cts(uint8_t packets_to_grant, uint8_t next_seq)
{
    printf("RX -> CTS: grant=%u packet(s) starting at seq=%u, control=0x%02X\n",
           packets_to_grant, next_seq, CTS_CONTROL_BYTE);
    return packets_to_grant;
}

static void send_data_packets(uint8_t start_seq, uint8_t count)
{
    uint8_t i;

    for (i = 0U; i < count; i++) {
        printf("TX -> TP.DT: seq=%u\n", (uint8_t)(start_seq + i));
    }
}

static void send_end_of_msg_ack(uint8_t total_packets)
{
    printf("RX -> EndOfMsgAck: total_packets=%u, control=0x%02X\n", total_packets, EOM_ACK_BYTE);
}

int main(void)
{
    uint8_t delivered = 0U;
    uint8_t next_seq = 1U;
    uint8_t grant;

    send_rts(TOTAL_PACKETS);

    /* First batch: receiver only grants 3 of the 5 packets. */
    grant = send_cts(3U, next_seq);
    send_data_packets(next_seq, grant);
    delivered = (uint8_t)(delivered + grant);
    next_seq = (uint8_t)(next_seq + grant);

    /* Second batch: remaining 2 packets. */
    grant = send_cts((uint8_t)(TOTAL_PACKETS - delivered), next_seq);
    send_data_packets(next_seq, grant);
    delivered = (uint8_t)(delivered + grant);

    if (delivered == TOTAL_PACKETS) {
        send_end_of_msg_ack(TOTAL_PACKETS);
    } else {
        printf("RX -> Abort: control=0x%02X\n", ABORT_BYTE);
    }

    return 0;
}
