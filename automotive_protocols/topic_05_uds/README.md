# Topic 05 — UDS / ISO 14229 (Unified Diagnostic Services)
UDS is the request/response diagnostic protocol every scan tool, OEM flashing tool, and dealer tester speaks over ISO-TP/CAN to read data, clear faults, and reflash an ECU.

## Brief Theory

| SID | Service | Purpose |
|-----|---------|---------|
| 0x10 | DiagnosticSessionControl | Change diagnostic session (default/programming/extended) |
| 0x11 | ECUReset | Request hard/soft/key-off-on reset |
| 0x14 | ClearDiagnosticInformation | Clear stored DTCs |
| 0x19 | ReadDTCInformation | Report stored/pending/confirmed DTCs |
| 0x22 | ReadDataByIdentifier | Read a data value by 2-byte DID |
| 0x23 | ReadMemoryByAddress | Read raw memory contents |
| 0x27 | SecurityAccess | Seed/key unlock for protected services |
| 0x28 | CommunicationControl | Enable/disable normal communication |
| 0x2E | WriteDataByIdentifier | Write a data value by 2-byte DID |
| 0x31 | RoutineControl | Start/stop/query a diagnostic routine |
| 0x34 | RequestDownload | Begin a memory download (reflash) |
| 0x36 | TransferData | Transfer a block of download/upload data |
| 0x37 | RequestTransferExit | Finalize a transfer |
| 0x3E | TesterPresent | Keep session alive (suppress S3 timeout) |

| Response type | Format | Example |
|----------------|--------|---------|
| Positive response | request SID + 0x40 | 0x10 → 0x50 |
| Negative response | 0x7F, echoed SID, NRC | 0x7F 0x10 0x12 |

| NRC | Name |
|-----|------|
| 0x10 | generalReject |
| 0x11 | serviceNotSupported |
| 0x12 | subFunctionNotSupported |
| 0x13 | incorrectMessageLengthOrInvalidFormat |
| 0x22 | conditionsNotCorrect |
| 0x24 | requestSequenceError |
| 0x31 | requestOutOfRange |
| 0x33 | securityAccessDenied |
| 0x35 | invalidKey |
| 0x36 | exceedNumberOfAttempts |
| 0x37 | requiredTimeDelayNotExpired |
| 0x78 | requestCorrectlyReceived-ResponsePending |

| Session type (sub-fn of 0x10) | Meaning |
|--------------------------------|---------|
| 0x01 | defaultSession |
| 0x02 | programmingSession |
| 0x03 | extendedDiagnosticSession |

| SecurityAccess sub-function | Meaning |
|------------------------------|---------|
| odd (0x01, 0x03, ...) | requestSeed for a security level |
| even (0x02, 0x04, ...) | sendKey for a security level |

| DTC byte | Content |
|----------|---------|
| Byte 0-2 | 3-byte DTC number (system + fault code) |
| Byte 3 | Status byte: bit0 testFailed, bit1 testFailedThisOperationCycle, bit2 pendingDTC, bit3 confirmedDTC, bit6 confirmedDTCSinceLastClear, bit7 warningIndicatorRequested |

**Tips:** every service in this topic is simulated in a single translation unit — no real CAN/ISO-TP stack is used, only the SID/sub-function/NRC byte layout that rides on top of it.

---

## Exercises
| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_session_control.c](solutions/ex01_session_control.c) | Build DiagnosticSessionControl (0x10) request/response frames | Request, positive response with timing bytes, negative response printed | Session control framing |
| 02 | [ex02_ecu_reset.c](solutions/ex02_ecu_reset.c) | Build ECUReset (0x11) request/response for hard/key-off-on/soft reset | Reset type echoed in positive response | Reset sub-functions |
| 03 | [ex03_negative_response.c](solutions/ex03_negative_response.c) | Build a generic 0x7F negative response and decode NRC to text | NRC byte mapped to human-readable string | NRC lookup |
| 04 | [ex04_security_access_seed_key.c](solutions/ex04_security_access_seed_key.c) | Simulate SecurityAccess (0x27) seed request and illustrative key computation | Seed bytes, computed key, access granted | Seed/key handshake |
| 05 | [ex05_security_access_lockout.c](solutions/ex05_security_access_lockout.c) | Simulate wrong-key lockout after N attempts | 0x36 after max attempts, then 0x37 until delay elapses | Attempt-counter lockout |
| 06 | [ex06_read_data_by_id.c](solutions/ex06_read_data_by_id.c) | Simulate ReadDataByIdentifier (0x22) against a static DID table | VIN/SW version/engine hours returned, unknown DID rejected | DID lookup |
| 07 | [ex07_write_data_by_id.c](solutions/ex07_write_data_by_id.c) | Simulate WriteDataByIdentifier (0x2E) with write-protected DIDs | Writable DID accepted, read-only DID rejected with NRC | Write protection |
| 08 | [ex08_routine_control.c](solutions/ex08_routine_control.c) | Simulate RoutineControl (0x31) start/stop/requestResults on a named routine | Routine status byte changes across sub-functions | Routine state |
| 09 | [ex09_dtc_encode_decode.c](solutions/ex09_dtc_encode_decode.c) | Pack/unpack a 3-byte DTC + status byte | DTC bytes and human-readable status flags printed | DTC bit layout |
| 10 | [ex10_read_dtc_information.c](solutions/ex10_read_dtc_information.c) | Simulate ReadDTCInformation (0x19) sub-function 0x02 with status mask filter | Only DTCs matching mask reported | DTC status filtering |
| 11 | [ex11_tester_present.c](solutions/ex11_tester_present.c) | Simulate an S3 session timer kept alive by TesterPresent (0x3E) | Session stays active when kept alive, times out otherwise | Session keep-alive |
| 12 | [ex12_full_session_demo.c](solutions/ex12_full_session_demo.c) | Chain SessionControl → SecurityAccess → ReadDataByIdentifier → ECUReset | Full request/response trace across four services | Multi-service session |

---

## Build & Run
```bash
cd automotive_protocols/topic_05_uds/solutions
gcc ex01_session_control.c -o ex01 && ./ex01
```
