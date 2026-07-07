/*
 * ex10_sensor_packet.c — Wire-format sensor packet struct
 * Key concept: struct layout must match protocol byte order on wire.
 */
#include <stdint.h>
#include <stdio.h>

typedef struct __attribute__((packed)) {
    uint8_t  header;
    int16_t  temperature;
    uint16_t humidity;
    uint8_t  checksum;
} sensor_packet_t;

int main(void)
{
    sensor_packet_t pkt = {
        .header = 0xAA,
        .temperature = 235,   /* 23.5 C x10 */
        .humidity = 650U,     /* 65.0 % x10 */
        .checksum = 0x5A
    };

    printf("Packet: hdr=0x%02X temp=%d hum=%u cksum=0x%02X\n",
           pkt.header, pkt.temperature, pkt.humidity, pkt.checksum);
    printf("sizeof(packet) = %zu bytes (packed)\n", sizeof(pkt));
    return 0;
}
