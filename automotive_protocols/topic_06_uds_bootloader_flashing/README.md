# Topic 06 — UDS ECU Reflashing / Bootloader Flow
A flash tool reprograms an ECU's application firmware entirely over the UDS services from topics 04/05 — session control and security access unlock the ECU, then download/transfer/exit services move the image in, and a routine validates it before reset.

## Brief Theory

### Reflash sequence (happy path)
| Step | Service | SID (req/resp) | Purpose |
|------|---------|-----------------|---------|
| 1 | DiagnosticSessionControl | 0x10 / 0x50 | Enter extended session (0x03) — unlocks security access |
| 2 | SecurityAccess | 0x27 / 0x67 | Seed/key exchange to unlock reprogramming |
| 3 | DiagnosticSessionControl | 0x10 / 0x50 | Enter programming session (0x02) |
| 4 | RoutineControl (erase) | 0x31 / 0x71 | Start erase-memory routine on target flash range |
| 5 | RequestDownload | 0x34 / 0x74 | Announce address, size, data/compression format |
| 6 | TransferData (loop) | 0x36 / 0x76 | Send firmware in blocks until image fully sent |
| 7 | RequestTransferExit | 0x37 / 0x77 | Close the transfer, optionally pass final CRC |
| 8 | RoutineControl (check deps) | 0x31 / 0x71 | Validate checksum/CRC + completeness |
| 9 | ECUReset | 0x11 / 0x51 | Reset to default session, boot new application |

### Sequence diagram
```
Tester                                  ECU
  |--10 03 (extended session)---------->|
  |<--50 03---------------------------- |
  |--27 01 (request seed)-------------->|
  |<--67 01 seed[]---------------------- |
  |--27 02 key[]------------------------>|
  |<--67 02----------------------------- |
  |--10 02 (programming session)------->|
  |<--50 02------------------------------|
  |--31 01 erase routineId[range]------->|
  |<--71 01 (in progress/complete)-------|
  |--34 addr,size,fmt------------------->|
  |<--74 maxBlockLength------------------|
  |--36 bsc=1 data[block]---------------->|
  |<--76 bsc=1----------------------------|
  |     ... repeat, bsc wraps 1..0xFF ... |
  |--37 (+ final CRC)-------------------->|
  |<--77---------------------------------|
  |--31 01 checkProgDeps----------------->|
  |<--71 01 (pass/fail)-------------------|
  |--11 01 (hard reset)------------------>|
  |<--51 01-------------------------------|
```

### RequestDownload (0x34) fields
| Field | Meaning |
|-------|---------|
| dataFormatIdentifier | High nibble = compression method, low nibble = encryption method |
| addressAndLengthFormatIdentifier | High nibble = size of memorySize field (bytes), low nibble = size of memoryAddress field (bytes) |
| memoryAddress | Start address of the region to flash |
| memorySize | Total byte count to transfer |
| resp: maxNumberOfBlockLength | Largest chunk the ECU accepts per TransferData |

### Block sequence counter rules
| Rule | Detail |
|------|--------|
| Start value | 1 (not 0) on first TransferData after RequestDownload |
| Wrap | Increments 1..0xFF then wraps back to 0x00, 0x01, ... |
| Mismatch | ECU replies NRC 0x24 requestSequenceError, transfer aborts |
| Recovery | Tester must restart from RequestDownload (0x34) |

### TesterPresent / S3 timer
| Item | Detail |
|------|--------|
| S3 timer | ECU-side inactivity timeout in a non-default session (typically ~5s) |
| Trigger | Any diagnostic request resets S3; TransferData loops can be slow, so idle gaps risk timeout |
| TesterPresent (0x3E) | Sent periodically (sub-function 0x80 = suppress positive response) purely to reset S3 |
| Timeout consequence | ECU silently drops back to default session; programming session is lost and the whole flow must legally restart from extended session |

### Checksum / CRC validation gate
| Strategy | Detail |
|----------|--------|
| Additive checksum | Sum of all image bytes (mod 2^n), cheap but weak |
| CRC32 | Polynomial-based, computed over the reassembled image, strong error detection |
| Comparison | Computed value compared against an expected value sent by the tool or stored in a trailer |
| Gate | checkProgrammingDependencies routine (RoutineControl 0x31) must pass before ECUReset is trusted |

**Tips:** Treat every step as fallible — an aborted transfer, a dropped session, or a checksum mismatch must all be handled by restarting the sequence, never by continuing past a failure.

---

## Exercises
| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_request_download.c](solutions/ex01_request_download.c) | Build/parse RequestDownload (0x34) request and response | Address, size, format, maxBlockLength printed | Address/length format identifier |
| 02 | [ex02_transfer_data_loop.c](solutions/ex02_transfer_data_loop.c) | Split firmware image into blocks bounded by maxBlockLength, wrap block sequence counter | Blocks sent, one out-of-sequence block rejected (NRC 0x24) | Block sequence counter |
| 03 | [ex03_request_transfer_exit.c](solutions/ex03_request_transfer_exit.c) | Build/parse RequestTransferExit (0x37) with optional final CRC parameter | Transfer closed, CRC echoed | Transfer-request-specific parameter |
| 04 | [ex04_checksum_validation.c](solutions/ex04_checksum_validation.c) | Compute CRC32 over reassembled image, compare to expected | PASS/FAIL printed | CRC32 validation gate |
| 05 | [ex05_erase_routine_control.c](solutions/ex05_erase_routine_control.c) | Start erase RoutineControl (0x31), poll requestResults until complete | Progress polls then "erase complete" | RoutineControl start/poll |
| 06 | [ex06_check_programming_dependencies.c](solutions/ex06_check_programming_dependencies.c) | Post-flash routine: checksum ok + all blocks written + no pending prereq | PASS or FAIL with NRC-style reason | checkProgrammingDependencies |
| 07 | [ex07_tester_present_keepalive.c](solutions/ex07_tester_present_keepalive.c) | S3 timer countdown during a long TransferData loop, TesterPresent resets it | Session kept alive, or timeout forces restart | TesterPresent / S3 timer |
| 08 | [ex08_full_bootloader_flow.c](solutions/ex08_full_bootloader_flow.c) | Chain RequestDownload -> TransferData loop -> RequestTransferExit -> checkProgrammingDependencies -> ECUReset | Full request/response trace, one checksum-mismatch failure path shown | End-to-end bootloader state machine |

---

## Build & Run
```bash
cd automotive_protocols/topic_06_uds_bootloader_flashing/solutions
gcc ex01_request_download.c -o ex01 && ./ex01
```
