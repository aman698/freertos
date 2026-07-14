# Automotive Communication Protocols Practice in C

Brief theory + runnable C programs covering the protocol stack a vehicle ECU/BSP developer needs, from wire-level UART/SPI/I2C up through CAN, J1939, and UDS diagnostics/reflashing.

**7 topics** x **~10 problems** = **~72 programs**

---

## Learning Path

| # | Folder | Focus |
|---|--------|-------|
|01| [topic_01_serial_comm_basics](topic_01_serial_comm_basics/) | UART/SPI/I2C recap for ECU/diagnostic-connector links: K-Line, OBD-II connector, SPI-to-CAN-controller chips, I2C to EEPROM/sensors |
|02| [topic_02_can_bus](topic_02_can_bus/) | CAN 2.0A/B frame format, arbitration, bit timing, error states/bus-off, bit stuffing, CRC-15 |
|03| [topic_03_j1939_transport](topic_03_j1939_transport/) | SAE J1939: PGN/SPN, 29-bit ID breakdown, PDU1/PDU2, BAM and RTS/CTS transport protocol, address claiming/NAME field |
|04| [topic_04_iso_tp](topic_04_iso_tp/) | ISO 15765-2: Single/First/Consecutive/Flow-Control frames, PCI byte, STmin/block-size flow control, segmentation/reassembly |
|05| [topic_05_uds](topic_05_uds/) | ISO 14229 UDS: session control, security access seed-key, DTC read/clear, read/write data by identifier, routine control, negative response codes |
|06| [topic_06_uds_bootloader_flashing](topic_06_uds_bootloader_flashing/) | Full ECU reflash sequence: RequestDownload/TransferData/RequestTransferExit, checksum validation, TesterPresent keep-alive |
|07| [topic_07_lin_flexray_ethernet](topic_07_lin_flexray_ethernet/) | Brief survey of LIN, FlexRay, and Automotive Ethernet/SOME-IP |

---

## Master References
- [PROTOCOLS_THEORY_REFERENCE.md](PROTOCOLS_THEORY_REFERENCE.md) — condensed theory for all 7 topics
- [PRACTICE_LOG_PROTOCOLS.md](PRACTICE_LOG_PROTOCOLS.md) — session log template

---

## Build & Run

```bash
cd automotive_protocols/topic_02_can_bus/solutions
gcc ex01_can_frame_layout.c -o ex01 && ./ex01
```

Each file is self-contained and uses only standard C headers.
