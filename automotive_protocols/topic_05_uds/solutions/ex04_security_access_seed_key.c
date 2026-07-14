/*
 * ex04_security_access_seed_key.c - Simulate SecurityAccess (0x27) seed/key handshake.
 * Key concept: odd sub-function requests a seed, even sub-function sends the computed key.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_SECURITY_ACCESS 0x27U
#define SUB_REQUEST_SEED_L1 0x01U
#define SUB_SEND_KEY_L1     0x02U
#define SEED_LEN 4U

static void print_bytes(const char *label, const uint8_t *data, size_t len)
{
    if ((label == NULL) || (data == NULL)) {
        return;
    }
    printf("%-14s:", label);
    for (size_t i = 0U; i < len; i++) {
        printf(" 0x%02X", data[i]);
    }
    printf("\n");
}

/* Illustrative seed source only - NOT a cryptographically secure RNG. */
static void generate_seed(uint8_t *seed, size_t len)
{
    static uint8_t counter = 0x11U;
    if (seed == NULL) {
        return;
    }
    for (size_t i = 0U; i < len; i++) {
        counter = (uint8_t)((counter * 5U) + 1U);
        seed[i] = counter;
    }
}

/*
 * Illustrative key algorithm ONLY: XOR each seed byte with a fixed mask, then
 * rotate the whole array left by one byte. Real ECUs use OEM-proprietary or
 * AES-based algorithms; this exists purely to demonstrate the request/response
 * shape of the SecurityAccess service.
 */
static void compute_key(const uint8_t *seed, uint8_t *key, size_t len)
{
    static const uint8_t MASK = 0xA5U;
    if ((seed == NULL) || (key == NULL) || (len == 0U)) {
        return;
    }
    for (size_t i = 0U; i < len; i++) {
        key[i] = seed[i] ^ MASK;
    }
    uint8_t first = key[0];
    for (size_t i = 0U; i < (len - 1U); i++) {
        key[i] = key[i + 1U];
    }
    key[len - 1U] = first;
}

int main(void)
{
    uint8_t seed[SEED_LEN];
    uint8_t client_key[SEED_LEN];
    uint8_t server_key[SEED_LEN];

    printf("Request : 0x%02X 0x%02X (requestSeed level 1)\n",
           SID_SECURITY_ACCESS, SUB_REQUEST_SEED_L1);

    generate_seed(seed, SEED_LEN);
    print_bytes("Seed", seed, SEED_LEN);

    compute_key(seed, client_key, SEED_LEN);
    print_bytes("Client key", client_key, SEED_LEN);

    printf("Request : 0x%02X 0x%02X + key bytes (sendKey level 1)\n",
           SID_SECURITY_ACCESS, SUB_SEND_KEY_L1);

    /* Server independently derives the expected key from the same seed. */
    compute_key(seed, server_key, SEED_LEN);

    int match = 1;
    for (size_t i = 0U; i < SEED_LEN; i++) {
        if (client_key[i] != server_key[i]) {
            match = 0;
        }
    }

    if (match != 0) {
        printf("Response: 0x%02X 0x%02X (positive - security access granted)\n",
               SID_SECURITY_ACCESS + 0x40U, SUB_SEND_KEY_L1);
    } else {
        printf("Response: 0x7F 0x%02X 0x35 (negative - invalidKey)\n", SID_SECURITY_ACCESS);
    }

    return 0;
}
