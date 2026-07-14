/*
 * ex12_full_session_demo.c - Chain SessionControl, SecurityAccess, ReadDataByIdentifier, ECUReset.
 * Key concept: a real tool sequence walks through several UDS services in one session.
 */
#include <stdint.h>
#include <stdio.h>

#define SID_DIAGNOSTIC_SESSION_CONTROL 0x10U
#define SID_SECURITY_ACCESS 0x27U
#define SID_READ_DATA_BY_IDENTIFIER 0x22U
#define SID_ECU_RESET 0x11U

#define SESSION_EXTENDED 0x03U
#define SUB_REQUEST_SEED_L1 0x01U
#define SUB_SEND_KEY_L1 0x02U
#define RESET_HARD 0x01U
#define SEED_LEN 4U

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

/* Illustrative only - NOT a real cryptographic key algorithm. See topic README. */
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

static void step_session_control(void)
{
    printf("[1] DiagnosticSessionControl\n");
    printf("    Request : 0x%02X 0x%02X\n", SID_DIAGNOSTIC_SESSION_CONTROL, SESSION_EXTENDED);
    printf("    Response: 0x%02X 0x%02X 0x00 0x32 0x01 0xF4 (extendedDiagnosticSession)\n",
           SID_DIAGNOSTIC_SESSION_CONTROL + 0x40U, SESSION_EXTENDED);
}

static void step_security_access(void)
{
    uint8_t seed[SEED_LEN];
    uint8_t key[SEED_LEN];

    printf("[2] SecurityAccess\n");
    printf("    Request : 0x%02X 0x%02X (requestSeed)\n", SID_SECURITY_ACCESS, SUB_REQUEST_SEED_L1);

    generate_seed(seed, SEED_LEN);
    printf("    Response: 0x%02X 0x%02X", SID_SECURITY_ACCESS + 0x40U, SUB_REQUEST_SEED_L1);
    for (size_t i = 0U; i < SEED_LEN; i++) {
        printf(" 0x%02X", seed[i]);
    }
    printf(" (seed)\n");

    compute_key(seed, key, SEED_LEN);
    printf("    Request : 0x%02X 0x%02X", SID_SECURITY_ACCESS, SUB_SEND_KEY_L1);
    for (size_t i = 0U; i < SEED_LEN; i++) {
        printf(" 0x%02X", key[i]);
    }
    printf(" (key)\n");
    printf("    Response: 0x%02X 0x%02X (security access granted)\n",
           SID_SECURITY_ACCESS + 0x40U, SUB_SEND_KEY_L1);
}

static void step_read_data_by_id(void)
{
    uint16_t did = 0xF190U;
    printf("[3] ReadDataByIdentifier\n");
    printf("    Request : 0x%02X 0x%02X 0x%02X\n",
           SID_READ_DATA_BY_IDENTIFIER, (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU));
    printf("    Response: 0x%02X 0x%02X 0x%02X data=\"1HGCM82633A004352\" (VIN)\n",
           SID_READ_DATA_BY_IDENTIFIER + 0x40U, (uint8_t)(did >> 8), (uint8_t)(did & 0xFFU));
}

static void step_ecu_reset(void)
{
    printf("[4] ECUReset\n");
    printf("    Request : 0x%02X 0x%02X (hardReset)\n", SID_ECU_RESET, RESET_HARD);
    printf("    Response: 0x%02X 0x%02X (ECU will reset)\n", SID_ECU_RESET + 0x40U, RESET_HARD);
}

int main(void)
{
    step_session_control();
    step_security_access();
    step_read_data_by_id();
    step_ecu_reset();

    return 0;
}
