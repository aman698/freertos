# Topic 01 — Serial Communication Basics (UART, SPI, I2C for ECU Comms)
Every diagnostic tool plugged into a J1962 connector and every sensor read on an ECU board rides on one of three serial protocols — get their framing, clocking, and addressing rules wrong and the byte on the wire is garbage before a single CAN frame ever gets involved.

## Brief Theory

| Field | Bits | Purpose | Automotive Use |
|-------|------|---------|-----------------|
| Start bit | 1, always logic 0 | Marks frame start, lets receiver sync its clock | K-Line wakes the receiver UART on this falling edge |
| Data bits | 5-9 (usually 8) | Payload byte | OBD-II diagnostic request/response bytes |
| Parity bit | none / even / odd | Single-bit error detection | ISO 9141-2 uses 8E1 framing |
| Stop bit(s) | 1 or 2 | Marks frame end, guarantees idle gap | Confirms line idle before next byte starts |
| Baud rate | bits per second | Sets bit time = 1 / baud | K-Line diagnostics typically run 10400 baud |

| SPI Mode | CPOL | CPHA | Clock Idle Level | Data Sampled On | Automotive Role |
|----------|------|------|-------------------|-------------------|-------------------|
| 0 | 0 | 0 | Low | 1st (leading) edge | Default for MCP2515-style standalone CAN controllers |
| 1 | 0 | 1 | Low | 2nd (trailing) edge | Some sensor/codec ICs |
| 2 | 1 | 0 | High | 1st (leading) edge | CAN transceiver config registers on some parts |
| 3 | 1 | 1 | High | 2nd (trailing) edge | Certain SPI flash/EEPROM parts |

| I2C Concept | Detail | Automotive Use |
|-------------|--------|-----------------|
| 7-bit addressing | 112 usable device addresses | ECU board EEPROM (e.g. 0x50), IO expander |
| 10-bit addressing | Extended address space, rarely used | Dense sensor clusters sharing one bus |
| R/W bit | LSB of the address byte on the wire: 0 = write, 1 = read | Distinguishes a config write from a sensor read |
| ACK / NACK | Receiver pulls SDA low on the 9th clock to ACK a byte | Confirms an EEPROM byte or command was accepted |
| Multi-master arbitration | Masters compare driven vs. sensed SDA bit-by-bit and back off on mismatch | Bus contention resolves by whichever master drives more zeros |

| Protocol | Physical Layer | Common ECU Use | Notes |
|----------|------------------|-------------------|-------|
| UART (K-Line) | Single wire, ISO 9141-2 / ISO 14230 | Legacy OBD-II diagnostic connector | 5-baud slow-init or fast-init handshake before normal UART framing |
| SPI | 4-wire: SCLK, MOSI, MISO, CS | MCU to standalone CAN controller (e.g. MCP2515) or transceiver config | Full duplex, one master drives many chip-selects |
| I2C | 2-wire: SDA, SCL | EEPROM, sensors, IO expanders on the ECU board | Shared bus, software-addressed, slower than SPI |

**Tips:** A UART byte time is not just `8 / baud` — forgetting the start, parity, and stop bits under-estimates transmission time and breaks timeout budgets. SPI has no addressing scheme at all, so mode mismatch (wrong CPOL/CPHA) silently shifts every sampled bit rather than throwing an error. I2C's open-drain bus means a stuck-low SDA line (a device that never releases the bus) hangs every other device on that line, which is why a bus-recovery routine is standard ECU firmware.

---

## Exercises
| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|-----------------------------|--------------|
| 01 | [ex01_uart_frame_time.c](solutions/ex01_uart_frame_time.c) | Compute UART bit time and full frame/byte time for several baud/parity/stop configs | Bit time and frame time in microseconds per config | Frame time = total bits / baud |
| 02 | [ex02_uart_checksum_parity.c](solutions/ex02_uart_checksum_parity.c) | Compute an even-parity bit per byte and an XOR checksum over a message buffer | Per-byte parity bits and final XOR checksum | XOR checksum & parity error detection |
| 03 | [ex03_spi_mode_encode_decode.c](solutions/ex03_spi_mode_encode_decode.c) | Pack CPOL/CPHA into a 2-bit SPI mode number and decode it back | Mode 0-3 with idle level and sampling edge printed | CPOL/CPHA to SPI mode mapping |
| 04 | [ex04_spi_shift_transfer.c](solutions/ex04_spi_shift_transfer.c) | Simulate a full-duplex SPI byte exchange bit by bit (MOSI out, MISO in) | Per-clock bit stream, then the received MISO byte | Full-duplex shift register transfer |
| 05 | [ex05_i2c_address_packing.c](solutions/ex05_i2c_address_packing.c) | Pack a 7-bit I2C device address and R/W bit into the wire address byte, then decode it | Wire byte for write/read, then decoded address and direction | (addr7 << 1) \| R/W wire format |
| 06 | [ex06_i2c_write_transaction.c](solutions/ex06_i2c_write_transaction.c) | Simulate START, address+W, data bytes, and STOP with per-byte ACK/NACK | Byte-by-byte ACK/NACK trace, abort on NACK | I2C write transaction framing |
| 07 | [ex07_uart_baud_divisor.c](solutions/ex07_uart_baud_divisor.c) | Compute an STM32-style USART BRR divisor (mantissa + fraction) from peripheral clock and baud rate | Mantissa, fraction, and packed BRR register value | Clock/baud to BRR register math |
| 08 | [ex08_kline_slow_init.c](solutions/ex08_kline_slow_init.c) | Simulate the ISO 9141-2 K-Line 5-baud slow-init handshake (0x33, sync, key bytes, inverted echo) | Step-by-step tool/ECU handshake trace | K-Line 5-baud slow-init sequence |
| 09 | [ex09_obd2_connector_pinout.c](solutions/ex09_obd2_connector_pinout.c) | Print the J1962 OBD-II connector pin-to-signal mapping from a struct table | Pin number next to its signal name for all listed pins | J1962 diagnostic connector pinout |
| 10 | [ex10_protocol_picker.c](solutions/ex10_protocol_picker.c) | Given a small set of communication needs, recommend UART/SPI/I2C/CAN and print why | Need paired with recommended protocol and one-line reason | Protocol selection trade-offs |

---

## Build & Run
```bash
cd automotive_protocols/topic_01_serial_comm_basics/solutions
gcc ex01_uart_frame_time.c -o ex01 && ./ex01
```
