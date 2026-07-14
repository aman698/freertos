/*
 * ex05_someip_offer_service.c - Minimal illustrative SOME/IP OfferService message.
 * Key concept: SOME/IP service discovery advertises services instead of fixed signal frames.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t service_id;
    uint16_t instance_id;
    uint8_t major_version;
    uint32_t minor_version;
    uint32_t ttl_seconds;
} SomeIpOfferService_t;

static void someip_build_offer(SomeIpOfferService_t *msg, uint16_t service_id,
                                uint16_t instance_id, uint8_t major_version,
                                uint32_t minor_version, uint32_t ttl_seconds)
{
    if (msg == NULL) {
        return;
    }
    msg->service_id = service_id;
    msg->instance_id = instance_id;
    msg->major_version = major_version;
    msg->minor_version = minor_version;
    msg->ttl_seconds = ttl_seconds;
}

static void someip_print_offer(const SomeIpOfferService_t *msg)
{
    if (msg == NULL) {
        printf("ERROR: null OfferService message\n");
        return;
    }
    printf("OfferService: ServiceID=0x%04X InstanceID=0x%04X Version=%u.%lu TTL=%lus\n",
           msg->service_id, msg->instance_id, msg->major_version,
           (unsigned long)msg->minor_version, (unsigned long)msg->ttl_seconds);
}

int main(void)
{
    SomeIpOfferService_t offer;

    someip_build_offer(&offer, 0x1234U, 0x0001U, 1U, 0UL, 3U);
    someip_print_offer(&offer);
    someip_print_offer(NULL);

    return 0;
}
