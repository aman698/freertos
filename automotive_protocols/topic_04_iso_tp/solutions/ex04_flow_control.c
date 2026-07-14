/* ex04_flow_control.c - Build and parse an ISO-TP Flow Control frame (N_PCI type 0x3). */
/* Key concept: FC carries flow status (FS), block size (BS), and STmin fields. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CAN_DLC       8U
#define FC_PCI_TYPE   0x30U
#define FS_MASK       0x0FU

#define FS_CTS        0U
#define FS_WAIT       1U
#define FS_OVERFLOW   2U

static const char *fs_name(uint8_t fs)
{
    static const char *names[3] = {"Continue To Send", "Wait", "Overflow"};

    if (fs > FS_OVERFLOW) {
        return "Reserved";
    }
    return names[fs];
}

static int32_t build_flow_control(uint8_t *frame, uint8_t fs, uint8_t bs, uint8_t stmin)
{
    if (frame == NULL) {
        return -1;
    }

    memset(frame, 0, CAN_DLC);
    frame[0] = (uint8_t)(FC_PCI_TYPE | (fs & FS_MASK));
    frame[1] = bs;
    frame[2] = stmin;
    return 0;
}

static int32_t parse_flow_control(const uint8_t *frame, uint8_t *fs_out, uint8_t *bs_out, uint8_t *stmin_out)
{
    uint8_t pci_type;

    if ((frame == NULL) || (fs_out == NULL) || (bs_out == NULL) || (stmin_out == NULL)) {
        return -1;
    }

    pci_type = (uint8_t)(frame[0] >> 4);
    if (pci_type != 0x3U) {
        return -1;
    }

    *fs_out = (uint8_t)(frame[0] & FS_MASK);
    *bs_out = frame[1];
    *stmin_out = frame[2];
    return 0;
}

int main(void)
{
    uint8_t frame[CAN_DLC];
    uint8_t fs = 0U;
    uint8_t bs = 0U;
    uint8_t stmin = 0U;

    if (build_flow_control(frame, FS_CTS, 8U, 0x0AU) != 0) {
        printf("build failed\n");
        return 0;
    }

    printf("FC frame:");
    for (uint8_t i = 0U; i < CAN_DLC; i++) {
        printf(" 0x%02X", frame[i]);
    }
    printf("\n");

    if (parse_flow_control(frame, &fs, &bs, &stmin) != 0) {
        printf("parse failed\n");
        return 0;
    }

    printf("FS=%u (%s), BS=%u, STmin=0x%02X\n", fs, fs_name(fs), bs, stmin);

    return 0;
}
