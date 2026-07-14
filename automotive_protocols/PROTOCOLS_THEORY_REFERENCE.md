# Automotive Protocols Theory Reference — Complete Concept Guide

Quick theory for all 7 practice topics. Pair with topic README + solve exercises.

---

## 1. Serial Communication Basics

| Link | Wires | Typical ECU use |
|------|-------|------------------|
| UART (K-Line/ISO 9141) | 1 wire, half-duplex | Legacy OBD-II diagnostics |
| SPI | SCLK/MOSI/MISO/CS | MCU to standalone CAN controller (e.g. MCP2515) |
| I2C | SDA/SCL, 7-bit addr | EEPROM, temp/pressure sensors on the ECU board |

K-Line uses a 5-baud or fast init handshake before UDS-over-K-Line sessions begin.

**Rule:** always check UART framing (baud, parity, stop bits) and SPI clock polarity/phase match the target chip's datasheet before trusting garbled data to "just be noise."

---

## 2. CAN Bus

| Field | 2.0A (Standard) | 2.0B (Extended) |
|-------|------------------|------------------|
| Identifier | 11 bit | 29 bit |
| Arbitration | Dominant (0) beats recessive (1), bitwise | same |
| DLC | 0–8 bytes | 0–8 bytes |
| CRC | 15 bits + delimiter | 15 bits + delimiter |
| Error states | Error Active → Error Passive → Bus-Off (TEC/REC thresholds 128/256) | same |

Bit stuffing: after 5 identical consecutive bits, a complementary stuff bit is inserted to guarantee edges for clock sync.

**Never** assume a lower CAN ID node can be starved — arbitration is non-destructive, but a continuously-transmitting low-ID node can still monopolize the bus in practice.

---

## 3. SAE J1939

| Concept | Detail |
|---------|--------|
| 29-bit ID | Priority(3) + PGN(18, incl. PDU format/specific + EDP/DP) + Source Address(8) |
| PDU1 | PDU-Format < 240 → destination-specific, PS = destination address |
| PDU2 | PDU-Format >= 240 → broadcast, PS = group extension |
| PGN/SPN | PGN identifies a parameter group; SPN identifies one signal inside it |
| Transport | BAM = broadcast, no flow control; RTS/CTS = point-to-point, flow-controlled |
| Address claim | NAME (64-bit) arbitrates which node keeps a contested source address |

**Rule:** lower priority value = higher bus priority, and PDU1 vs PDU2 changes how the PS byte must be interpreted — never treat J1939 IDs like plain CAN IDs.

---

## 4. ISO-TP (ISO 15765-2)

```c
/* N_PCI byte high nibble = frame type */
0x0N  /* Single Frame:      N = data length (0-7)      */
0x1N  /* First Frame:       N (12-bit) = total length  */
0x2N  /* Consecutive Frame: N = sequence number 0-15   */
0x3F  /* Flow Control:      FS, BS (block size), STmin */
```

Segmentation: First Frame announces total length, Consecutive Frames follow after a Flow Control grant; STmin gates the sender's inter-frame gap, Block Size caps frames-per-FC.

**Rule:** the receiver's Flow Control (STmin/BS) governs sender pacing — ignoring it causes buffer overrun or a dropped multi-frame message.

---

## 5. UDS (ISO 14229)

| Service | SID | Purpose |
|---------|-----|---------|
| DiagnosticSessionControl | 0x10 | Default/Programming/Extended session |
| SecurityAccess | 0x27 | Seed request -> key response unlock |
| ReadDataByIdentifier | 0x22 | Read a DID (VIN, sensor value, etc.) |
| WriteDataByIdentifier | 0x2E | Write a DID |
| ReadDTCInformation / ClearDiagnosticInformation | 0x19 / 0x14 | DTC read / clear |
| RoutineControl | 0x31 | Start/stop/results of an ECU routine |
| Negative Response | 0x7F + SID + NRC | e.g. 0x33 securityAccessDenied, 0x22 conditionsNotCorrect |

**Never** assume a security-access key algorithm is symmetric across ECUs — each seed-key pair is vendor/ECU-specific and must be validated before unlocking higher sessions.

---

## 6. UDS Bootloader / ECU Reflashing

Sequence: `DiagnosticSessionControl(Programming)` -> `SecurityAccess` unlock -> `RequestDownload(0x34)` -> repeated `TransferData(0x36)` blocks -> `RequestTransferExit(0x37)` -> checksum/CRC validation -> reset/re-enumerate.

`TesterPresent(0x3E)` must be sent periodically (sub-function suppressing positive response is common) so the ECU does not time out of the programming session.

**Rule:** always send TesterPresent within the S3 timeout during a bootloader session or the ECU drops back to the default session and aborts the flash.

---

## 7. LIN, FlexRay & Automotive Ethernet

| Bus | Topology/Speed | Notes |
|-----|-----------------|-------|
| LIN | Single-wire, master-slave, up to 20 kbit/s | Low-cost body electronics (windows, mirrors) |
| FlexRay | Dual-channel, up to 10 Mbit/s, TDMA | Deterministic timing for safety-critical/x-by-wire |
| Automotive Ethernet | 100BASE-T1/1000BASE-T1 | Backbone for ADAS/infotainment; SOME-IP is the service-discovery/RPC layer on top |

**Never** expect LIN's single-master schedule table or FlexRay's static TDMA slots to behave like CAN's event-driven arbitration — each bus has a fundamentally different access method.

---
**Practice:** [`README.md`](README.md)
