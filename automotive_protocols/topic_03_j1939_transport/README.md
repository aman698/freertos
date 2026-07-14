# Topic 03 — SAE J1939 (Heavy-Duty Vehicle Network over CAN)

J1939 is the application layer that runs on top of CAN 2.0B (29-bit ID) to let engine, transmission, brake, and body ECUs on trucks, buses, off-highway, and agricultural equipment exchange standardized messages.

## Brief Theory

### 29-bit J1939 CAN Identifier

| Bits | Field | Width | Meaning |
|---|---|---|---|
| 28-26 | Priority | 3 bits | 0 = highest, 7 = lowest; lower value wins CAN arbitration |
| 25 | Reserved (R) | 1 bit | Normally 0 |
| 24 | Data Page (DP) | 1 bit | Selects PGN page 0 or page 1 |
| 23-16 | PDU Format (PF) | 8 bits | PF < 240 -> PDU1, PF >= 240 -> PDU2 |
| 15-8 | PDU Specific (PS) | 8 bits | Meaning depends on PF (see below) |
| 7-0 | Source Address (SA) | 8 bits | Address of the transmitting ECU |

### PDU1 vs PDU2

| PF range | Format | PS means | Communication style |
|---|---|---|---|
| 0-239 (0x00-0xEF) | PDU1 | Destination Address (DA) | Peer-to-peer / addressable |
| 240-255 (0xF0-0xFF) | PDU2 | Group Extension (GE) | Broadcast |

### PGN (Parameter Group Number)

| Formula | Applies to | Notes |
|---|---|---|
| PGN = (R\<\<17) \| (DP\<\<16) \| (PF\<\<8) | PDU1 (PF < 240) | PS carries the DA, not part of the PGN value |
| PGN = (R\<\<17) \| (DP\<\<16) \| (PF\<\<8) \| PS | PDU2 (PF >= 240) | PS carries the group extension, part of the PGN value |

### SPN vs PGN

| Concept | Scope | Example |
|---|---|---|
| PGN | Identifies the whole message (data group) | 61444 = EEC1 |
| SPN | Identifies one signal inside that message's data field | SPN 190 = Engine Speed |

### Well-known PGNs (illustrative, not exhaustive)

| PGN (dec) | PGN (hex) | Name | Notes |
|---|---|---|---|
| 61444 | 0xF004 | EEC1 (Electronic Engine Controller 1) | Carries SPN 190 Engine Speed |
| 65262 | 0xFEEE | Engine Temperature 1 | Carries SPN 110 Coolant Temp |
| 65263 | 0xFEEF | Engine Fluid Level/Pressure 1 | Carries oil pressure/level SPNs |
| 65226 | 0xFECA | DM1 (Active Diagnostic Trouble Codes) | Carries SPN + FMI + count per DTC |
| 60416 | 0xEC00 | TP.CM (Transport Protocol Connection Mgmt) | BAM / RTS / CTS / EndOfMsgAck / Abort |
| 60160 | 0xEB00 | TP.DT (Transport Protocol Data Transfer) | Carries up to 7 payload bytes per frame |
| 60928 | 0xEE00 | Address Claimed / Cannot Claim | Carries the 64-bit NAME |

### Transport Protocol (J1939-21)

| Mode | Control byte (TP.CM) | Flow control | Use case |
|---|---|---|---|
| BAM (Broadcast Announce Message) | 0x20 | None — all nodes may listen | Broadcast, no destination ECU |
| RTS (Request To Send) | 0x10 | Peer waits for CTS | Peer-to-peer, destination specific |
| CTS (Clear To Send) | 0x11 | Grants N packets, starting seq | Sent by receiver in response to RTS |
| EndOfMsgAck | 0x13 | Confirms full receipt | Sent by receiver after last packet |
| Abort | 0xFF | Terminates session | Sent by either side on error |

### Address Claiming (J1939-81) — 64-bit NAME

| Field | Width | Purpose |
|---|---|---|
| Arbitrary Address Capable | 1 bit | Can this ECU pick another address on conflict? |
| Industry Group | 3 bits | e.g. on-highway, agricultural |
| Vehicle System Instance | 4 bits | Distinguishes multiple identical systems |
| Vehicle System | 7 bits | e.g. tractor, trailer |
| Function | 8 bits | e.g. engine #1, brakes |
| Function Instance | 5 bits | Distinguishes multiple identical functions |
| ECU Instance | 3 bits | Distinguishes multiple ECUs for one function |
| Manufacturer Code | 11 bits | Assigned by SAE |
| Identity Number | 21 bits | Unique per manufacturer |

| Step | Action |
|---|---|
| Claim | ECU sends Address Claimed (PGN 60928) with its NAME and desired address |
| Contend | On conflict, NAME values are compared as 64-bit numbers — lower NAME wins |
| Defend | Winner re-sends its claim; loser must move to another address or address 254 (cannot claim) if not arbitrary-address-capable |

**Tips:** A PDU1 message's PS is a *destination address* (0xFF = global/broadcast), while a PDU2 message's PS is baked into the PGN itself — mixing these up is the most common J1939 decoding bug. BAM has zero flow control, so a busy receiver can silently drop TP.DT packets; RTS/CTS exists precisely to avoid that. Address-claim NAME comparisons are unsigned 64-bit compares, not priority fields — a single differing low bit changes the winner.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_id_pack_unpack.c](solutions/ex01_id_pack_unpack.c) | Pack/unpack a 29-bit J1939 CAN ID from {priority, PGN, source address} | Packed hex ID, then round-tripped fields match | 29-bit ID layout |
| 02 | [ex02_pdu_classifier.c](solutions/ex02_pdu_classifier.c) | Classify a set of PF byte values as PDU1 or PDU2 | Table of PF values with format + PS meaning | PDU1 vs PDU2 |
| 03 | [ex03_pgn_extraction.c](solutions/ex03_pgn_extraction.c) | Extract the PGN from raw 29-bit CAN IDs | Decoded PGN for a PDU1 and a PDU2 example ID | PGN formula |
| 04 | [ex04_spn_lookup.c](solutions/ex04_spn_lookup.c) | Look up an SPN in a small static table and decode a raw value | Name, unit, and scaled physical value | SPN scaling |
| 05 | [ex05_bam_sender.c](solutions/ex05_bam_sender.c) | Build a BAM TP.CM + TP.DT sequence for a payload > 8 bytes | TP.CM frame then each TP.DT frame printed | BAM sender |
| 06 | [ex06_bam_receiver.c](solutions/ex06_bam_receiver.c) | Reassemble TP.DT packets into the original payload | Reassembled byte buffer matches original | BAM receiver |
| 07 | [ex07_rts_cts.c](solutions/ex07_rts_cts.c) | Simulate RTS/CTS flow-controlled transfer in two grant batches | RTS, CTS(x2), TP.DT frames, EndOfMsgAck | RTS/CTS |
| 08 | [ex08_name_field.c](solutions/ex08_name_field.c) | Pack/unpack the 64-bit NAME field | Sub-fields printed, round trip verified | NAME bitfield |
| 09 | [ex09_address_claim.c](solutions/ex09_address_claim.c) | Resolve an address-claim conflict between two ECUs by NAME | Winner keeps address, loser reassigned/254 | Claim/contend/defend |
| 10 | [ex10_payload_limits.c](solutions/ex10_payload_limits.c) | Check payload sizes against the 1785-byte multi-packet limit | Pass/fail for boundary sizes | TP size limits |
| 11 | [ex11_dm1_dtc.c](solutions/ex11_dm1_dtc.c) | Build/decode a simplified DM1 active-DTC frame | SPN, FMI, occurrence count printed | DM1 DTC encoding |
| 12 | [ex12_priority_arbitration.c](solutions/ex12_priority_arbitration.c) | Same PGN, two priorities — show which ID wins CAN arbitration | Lower numeric ID declared bus winner | Priority vs arbitration |

---

## Build & Run

```bash
cd automotive_protocols/topic_03_j1939_transport/solutions
gcc ex01_id_pack_unpack.c -o ex01 && ./ex01
```
