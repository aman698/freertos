# Topic 07 — LIN, FlexRay & Automotive Ethernet (Brief Survey)

Beyond CAN and J1939, a BSP developer will meet three more vehicle networks, each trading cost, speed, and determinism differently: LIN for cheap actuators, FlexRay for hard real-time control, and Automotive Ethernet for high-bandwidth data.

## Brief Theory

**LIN (Local Interconnect Network)**

| Aspect | Detail |
|--------|--------|
| Topology | Single master, multiple slaves, 1-wire bus |
| Speed | Up to 20 kbps |
| Frame trigger | Master header = Break + Sync byte (0x55) + Protected Identifier (PID) |
| PID | 6-bit frame ID + 2 parity bits |
| Response | Addressed slave replies with data bytes + checksum |
| Checksum | Classic = data bytes only; Enhanced = PID + data bytes |
| Typical use | Low-cost actuators: window lift, mirrors, seats, HVAC flaps |

**FlexRay**

| Aspect | Detail |
|--------|--------|
| Topology | Dual-channel (A/B), bus or star |
| Speed | Up to 10 Mbps per channel |
| Access method | TDMA — communication cycle divided into segments |
| Static segment | Fixed-length slots, one frame ID per slot, deterministic |
| Dynamic segment | Minislots, frames sent only if needed, less time-critical |
| Typical use | Safety-critical / high-bandwidth: steer-by-wire, active chassis |

**Automotive Ethernet**

| Aspect | Detail |
|--------|--------|
| Physical layer | 100BASE-T1 / 1000BASE-T1, single twisted pair |
| Topology | Point-to-point links, switched network |
| Middleware | SOME/IP (Scalable service-Oriented MiddlewarE over IP) |
| Discovery | Offer / Find / Subscribe messages advertise & request services |
| Framing model | Service-oriented, not fixed-signal like CAN/LIN/FlexRay |
| Typical use | ADAS cameras, infotainment, gateway backbone |

**Network comparison**

| Network | Typical Speed | Topology | Determinism | Cost Tier | Typical Domain |
|---------|---------------|----------|-------------|-----------|----------------|
| CAN | Up to 1 Mbps (FD up to 8 Mbps) | Multi-drop bus | Priority arbitration, soft real-time | Low | Powertrain, body |
| LIN | Up to 20 kbps | Single-wire, single master | Master-scheduled polling | Very low | Simple actuators/sensors |
| FlexRay | Up to 10 Mbps | Dual-channel bus/star | Hard real-time, TDMA slots | High | Chassis, safety-critical control |
| Automotive Ethernet | 100 Mbps – 1 Gbps+ | Switched point-to-point | Best-effort / QoS-managed | Medium-high | ADAS, infotainment, backbone |

**Tips:** Pick the network by dominant constraint — LIN when cost rules out anything more, FlexRay when timing must be guaranteed, Automotive Ethernet when payload size dominates, and CAN as the default middle ground for everything else.

---

## Exercises
| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_lin_pid_builder.c](solutions/ex01_lin_pid_builder.c) | Build & verify a LIN Protected Identifier (6-bit ID + 2 parity bits) | PID hex printed, corrupted PID flagged | LIN PID parity |
| 02 | [ex02_lin_checksum.c](solutions/ex02_lin_checksum.c) | Compute LIN classic vs enhanced checksum over a data buffer | Both checksums printed side by side | LIN checksum |
| 03 | [ex03_lin_schedule_table.c](solutions/ex03_lin_schedule_table.c) | Simulate a LIN master schedule table driving frame requests | Frame sequence printed over several ticks | LIN scheduling |
| 04 | [ex04_flexray_static_slot.c](solutions/ex04_flexray_static_slot.c) | Compute the active FlexRay static-segment slot ID from a time offset | Cycle + slot ID printed per offset | FlexRay TDMA |
| 05 | [ex05_someip_offer_service.c](solutions/ex05_someip_offer_service.c) | Build a minimal SOME/IP OfferService message struct | Service/instance/version/TTL fields printed | SOME/IP discovery |
| 06 | [ex06_protocol_picker.c](solutions/ex06_protocol_picker.c) | Pick the best-fit network for illustrative requirement scenarios | Chosen network + reason per scenario | Protocol selection |

---

## Build & Run
```bash
cd automotive_protocols/topic_07_lin_flexray_ethernet/solutions
gcc ex01_lin_pid_builder.c -o ex01 && ./ex01
```
