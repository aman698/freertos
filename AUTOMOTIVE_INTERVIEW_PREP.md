# Automotive Embedded BSP Developer — Interview Preparation Map

Use this project as a 6-layer interview prep system:

1. **Embedded C base** - `c_practice/`
2. **DSA/problem solving** - `dsa_practice/`
3. **FreeRTOS concepts** - `examples/` + `THEORY_REFERENCE.md`
4. **Communication protocols** - `automotive_protocols/` (CAN, J1939, ISO-TP, UDS)
5. **Hardware integration (STM32F411RE)** - `examples/14_stm32_can_bxcan`, `docs/DEBUGGING_GUIDE.md`
6. **Integrated firmware design** - `projects/Advanced_FreeRTOS_Lab/`

---

## What To Master First

| Priority | Topic | Must explain in interview |
|----------|-------|---------------------------|
| 1 | CAN frame & arbitration | 11-bit vs 29-bit ID, dominant/recessive bits, bitwise arbitration, why lower ID wins |
| 2 | CAN error handling | Error Active/Passive/Bus-Off, TEC/REC counters, bus-off recovery |
| 3 | J1939 identifier field | 29-bit ID breakdown: priority, PGN (PDU1/PDU2), source address |
| 4 | J1939 transport protocol | BAM vs RTS/CTS multi-packet transfer, CTS/EOM control frames |
| 5 | ISO-TP segmentation | Single/First/Consecutive/Flow-Control frames, STmin, block size |
| 6 | UDS session & security | Default/extended/programming sessions, seed-key SecurityAccess |
| 7 | UDS diagnostics | DTC encoding, status byte, negative response (0x7F) and NRC codes |
| 8 | UDS bootloader reflash | Full sequence from tester-present through ECU reset |
| 9 | Mutex | Ownership and priority inheritance (carried forward — still asked constantly) |
| 10 | ISR deferral | ISR captures CAN frame, task decodes/parses (ties FreeRTOS to protocol stack) |

---

## Interview Build Order

| Stage | Practice | Goal |
|-------|----------|------|
| 1 | `automotive_protocols/topic_01_serial_comm_basics` | Explain UART/SPI/I2C framing used for ECU comms |
| 2 | `automotive_protocols/topic_02_can_bus` | Explain arbitration, bit timing, error states from memory |
| 3 | `automotive_protocols/topic_03_j1939_transport` | Pack/unpack a J1939 29-bit ID and run a BAM transfer by hand |
| 4 | `automotive_protocols/topic_04_iso_tp` | Build an ISO-TP segmenter/reassembler with Flow Control |
| 5 | `automotive_protocols/topic_05_uds` | Implement SecurityAccess seed/key and a DTC reader |
| 6 | `automotive_protocols/topic_06_uds_bootloader_flashing` | Narrate the full ECU reflash sequence |
| 7 | `examples/14_stm32_can_bxcan` | Wire bxCAN ISR -> J1939 decode task on real hardware |
| 8 | `c_practice/` + `dsa_practice/` | Confirm C fundamentals and problem solving still sharp |
| 9 | `examples/01`-`13` + `projects/Advanced_FreeRTOS_Lab` | Confirm FreeRTOS task/queue/sync architecture is fluent |
| 10 | This document | Full oral run-through, no notes |

---

## Oral Questions To Practice

1. Why does CAN arbitration favor lower numeric IDs, and what does "dominant vs recessive" mean electrically?
2. Walk through what happens to TEC/REC counters as a node goes Error Active -> Passive -> Bus-Off, and how it recovers.
3. Why does J1939 need a 29-bit extended CAN ID instead of the standard 11-bit ID?
4. Explain PDU1 vs PDU2 in J1939 and why it matters for whether a PGN is peer-to-peer or broadcast.
5. Walk through a J1939 BAM transport-protocol multi-packet transfer end to end.
6. When would a J1939 node use RTS/CTS instead of BAM?
7. What problem does ISO-TP solve that raw CAN can't, and what are the 4 frame types?
8. Walk through an ISO-TP multi-frame transfer including Flow Control, STmin, and block size.
9. What is the UDS seed-key SecurityAccess mechanism for, and why is a simple XOR unsuitable in a real production ECU?
10. What's the difference between UDS default, extended, and programming sessions?
11. Walk through the full UDS ECU reflashing sequence from tester-present to ECU reset.
12. Why must TesterPresent be sent periodically during a long diagnostic or flashing session?
13. What does a UDS negative response (0x7F) tell you, and how do you decode the NRC?
14. How is a DTC encoded, and what does the status byte tell you (pending vs confirmed)?
15. How would you debug a real vehicle network issue where an ECU intermittently drops off the CAN bus? (ties to debugger + bus-off theory)
16. Compare CAN, LIN, FlexRay, and Automotive Ethernet for cost/determinism/bandwidth tradeoffs.
17. How would you structure a FreeRTOS task architecture to receive CAN frames via ISR, decode J1939 in a parser task, and run diagnostics in a separate UDS server task?
18. Why is J1939 address claim needed, and what happens when two nodes claim the same source address?
19. What is the role of the CAN acceptance filter on a microcontroller, and why does it matter for real-time performance?
20. In an ISO-TP flow-controlled transfer, what happens if the receiver never sends a Flow Control frame — how should the sender time out?

---

## Coding Drills

Do these without looking at existing code:

| Drill | Target time |
|-------|-------------|
| Pack/unpack a J1939 29-bit ID (priority/PGN/source) | 15 min |
| Decode a CAN error frame and classify error state | 15 min |
| Build a J1939 BAM transport-protocol sender/receiver | 30 min |
| Build an ISO-TP segmenter/reassembler | 30 min |
| Implement ISO-TP Flow Control with STmin timing | 20 min |
| Build a UDS SecurityAccess seed/key exchange | 20 min |
| Encode/decode a DTC with status byte | 15 min |
| Simulate a UDS bootloader flash sequence | 30 min |
| Write bxCAN ISR that queues a frame to a decode task | 20 min |
| Explain examples/14_stm32_can_bxcan architecture | 5 min |

---

## Resume Project Summary

Use this wording in an interview:

> I built an automotive communication-protocols practice stack on STM32F411RE covering CAN 2.0A/B framing and arbitration, J1939 PGN/SPN addressing with BAM and RTS/CTS transport protocol, ISO-TP segmentation with Flow Control, and UDS diagnostic services including SecurityAccess, DTC handling, and a full ECU bootloader reflash simulation. It integrates with a FreeRTOS task architecture where a bxCAN ISR feeds a J1939 decode task and a separate UDS diagnostic server task, on top of the same firmware base used for the FreeRTOS practice project.

---

## Final Checklist

- [ ] I can draw the J1939 29-bit ID field breakdown from memory.
- [ ] I can explain CAN Error Active -> Passive -> Bus-Off and how a node recovers.
- [ ] I can walk through a J1939 BAM transfer and explain when RTS/CTS is used instead.
- [ ] I can explain the 4 ISO-TP frame types and when Flow Control is sent.
- [ ] I can explain UDS session types and the SecurityAccess seed-key flow.
- [ ] I can walk through the full UDS bootloader reflash sequence.
- [ ] I can decode a DTC and its status byte.
- [ ] I can explain why a mutex-protected UART matters when a CAN parser task also needs to print.
- [ ] I can explain the bxCAN ISR -> decode task -> UDS server task architecture end to end.
