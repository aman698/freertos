# Topic 04 — ISO-TP / ISO 15765-2 (Transport Layer for Diagnostics over CAN)

ISO-TP segments payloads larger than a single CAN frame's 8-byte limit into a Single/First/Consecutive-Frame sequence, governed by Flow Control, so UDS and other diagnostic services can exchange multi-byte messages over CAN.

## Brief Theory

| N_PCI Type | High Nibble | Remaining Bits/Bytes | Purpose |
|---|---|---|---|
| Single Frame (SF) | 0x0 | low nibble = SF_DL (0-7) | Whole message fits in one frame |
| First Frame (FF) | 0x1 | low nibble + byte1 = 12-bit FF_DL, then 6 data bytes | Opens a multi-frame message |
| Consecutive Frame (CF) | 0x2 | low nibble = SN (0-15, rolls over) | Carries 7 bytes per frame after FF |
| Flow Control (FC) | 0x3 | low nibble = FS, byte1 = BS, byte2 = STmin | Receiver paces the sender |

| FS Value | Meaning |
|---|---|
| 0 | Continue To Send (CTS) |
| 1 | Wait |
| 2 | Overflow / abort |

| Addressing Mode | Address Location | Effect on Payload |
|---|---|---|
| Normal | Whole CAN ID is the address | Full data bytes available (7/6/7 for SF/FF-first/CF) |
| Extended | Byte 0 of data = target address extension | One byte consumed, capacity drops by 1 |
| Mixed | Address extension + normal ID | Same capacity hit as extended |

| Timing Parameter | Side | Meaning |
|---|---|---|
| N_As / N_Ar | Sender / Receiver | Time to transmit one CAN frame onto the network |
| N_Bs / N_Br | Sender / Receiver | Time waiting for a Flow Control frame |
| N_Cs / N_Cr | Sender / Receiver | Time between Consecutive Frames |

| STmin Byte Range | Meaning |
|---|---|
| 0x00-0x7F | 0-127 ms, direct value |
| 0x80-0xF0 | Reserved |
| 0xF1-0xF9 | 100-900 us in 100 us steps |
| 0xFA-0xFF | Reserved |

**Tips:** BS (block size) of 0 means "send the rest of the message without waiting for another Flow Control frame."

---

## Exercises
| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_single_frame.c](solutions/ex01_single_frame.c) | Build and parse a Single Frame | Frame bytes printed, round-trip payload matches | SF N_PCI encoding |
| 02 | [ex02_first_frame.c](solutions/ex02_first_frame.c) | Build and parse a First Frame | 12-bit FF_DL split across 2 bytes, 6 data bytes | FF N_PCI encoding |
| 03 | [ex03_consecutive_frame.c](solutions/ex03_consecutive_frame.c) | Build and parse Consecutive Frames with rolling SN | SN wraps 0-15, 7 data bytes each | CF sequence numbering |
| 04 | [ex04_flow_control.c](solutions/ex04_flow_control.c) | Build and parse a Flow Control frame | FS/BS/STmin fields printed | FC frame fields |
| 05 | [ex05_stmin_encoding.c](solutions/ex05_stmin_encoding.c) | Encode/decode STmin values | ms and 100us-step bytes shown, reserved detected | STmin table |
| 06 | [ex06_segmenter.c](solutions/ex06_segmenter.c) | Segment a payload > 7 bytes into FF + CFs | Full frame sequence printed in hex | Message segmentation |
| 07 | [ex07_reassembler.c](solutions/ex07_reassembler.c) | Reassemble FF + CF stream back into payload | Payload rebuilt, bad SN reported as error | Message reassembly |
| 08 | [ex08_block_size_sim.c](solutions/ex08_block_size_sim.c) | Simulate BS-driven pause/resume | Sender pauses every BS frames for new FC | Flow control pacing |
| 09 | [ex09_addressing_modes.c](solutions/ex09_addressing_modes.c) | Compare normal vs extended addressing capacity | Payload-per-frame counts differ by 1 byte | Addressing overhead |
| 10 | [ex10_end_to_end.c](solutions/ex10_end_to_end.c) | Full segment/FC/reassemble simulation of a ~30-byte UDS payload | PASS/FAIL after round trip | End-to-end ISO-TP flow |

---

## Build & Run
```bash
cd automotive_protocols/topic_04_iso_tp/solutions
gcc ex01_single_frame.c -o ex01 && ./ex01
```
