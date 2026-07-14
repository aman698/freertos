# Master Study Plan — Embedded Automotive BSP Developer Prep

This repo is one integrated prep system spanning embedded C, DSA, FreeRTOS, automotive communication protocols, STM32 hardware integration, and debugging. This plan sequences all of it into a 10-week program that ends with two interview-ready oral maps and a working capstone.

---

## Overview Table

| Week | Focus | Folder(s) | Milestone |
|------|-------|-----------|-----------|
| 1-2 | Embedded C fundamentals | `c_practice/` | All 15 topics solved without looking at solutions |
| 3-4 | Data structures & algorithms in C | `dsa_practice/` | All 10 topics solved |
| 5 | FreeRTOS basics | `examples/01`-`07`, `PRACTICE_GUIDE.md` | Tasks/queues/mutex/timers mastered |
| 6 | FreeRTOS advanced | `examples/08`-`13`, `ADVANCED_PRACTICE_GUIDE.md`, capstone | Capstone project explainable end-to-end |
| 7 | Serial comms + CAN bus | `automotive_protocols/topic_01`, `topic_02` | Can explain CAN arbitration/bit-timing/error-states from memory |
| 8 | J1939 + ISO-TP | `automotive_protocols/topic_03`, `topic_04` | Can pack/unpack J1939 ID and run an ISO-TP segmenter by hand |
| 9 | UDS + bootloader flashing | `automotive_protocols/topic_05`, `topic_06`, `topic_07` | Can narrate the full UDS reflash sequence |
| 10 | Hardware integration + debugger + mock interview | `examples/14_stm32_can_bxcan`, `docs/DEBUGGING_GUIDE.md`, `AUTOMOTIVE_INTERVIEW_PREP.md`, `FREERTOS_INTERVIEW_PREP.md` | Full mock interview pass, both interview-prep docs completed |

---

## Daily rhythm (suggested)

- Read the day's topic `README.md` (theory framing, no code yet)
- Skim the matching section of `THEORY_REFERENCE.md` (weeks 5-6) or `automotive_protocols/PROTOCOLS_THEORY_REFERENCE.md` (weeks 7-9)
- Attempt the exercises without looking at any provided solution
- Compare your attempt to the reference solution and note gaps
- Fill in the matching practice log (`PRACTICE_LOG.md`, `PRACTICE_LOG_ADVANCED.md`, or `automotive_protocols/PRACTICE_LOG_PROTOCOLS.md`)

---

## Definition of "ready to interview"

- [ ] All `c_practice/` and `dsa_practice/` topics solved cold, no reference
- [ ] Every item in `FREERTOS_INTERVIEW_PREP.md`'s Final Checklist is true without notes
- [ ] Every item in `AUTOMOTIVE_INTERVIEW_PREP.md`'s Final Checklist is true without notes
- [ ] Capstone (`projects/Advanced_FreeRTOS_Lab/`) architecture explainable in 5 minutes
- [ ] `examples/14_stm32_can_bxcan` bxCAN ISR -> J1939 decode flow explainable end-to-end
- [ ] Full UDS bootloader reflash sequence narrated without hesitation
- [ ] Comfortable debugging a hung task or dropped CAN frame live using `docs/DEBUGGING_GUIDE.md`
- [ ] Can do a 45-minute mock interview covering C, DSA, FreeRTOS, and protocols without notes

---

## Cross-links

- [README.md](README.md)
- [FREERTOS_INTERVIEW_PREP.md](FREERTOS_INTERVIEW_PREP.md)
- [AUTOMOTIVE_INTERVIEW_PREP.md](AUTOMOTIVE_INTERVIEW_PREP.md)
- [automotive_protocols/README.md](automotive_protocols/README.md)
