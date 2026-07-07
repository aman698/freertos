# Topic 15 - State Machines

A finite state machine (FSM) models firmware as states, events, transitions, and actions. FSMs are clearer than deeply nested `if` logic for buttons, protocols, menus, and parsers.

## Brief Theory

| Part | Meaning | Example |
|------|---------|---------|
| State | Current mode | `IDLE`, `RUN`, `FAULT` |
| Event | Input that may cause transition | button, timeout, byte |
| Transition | Rule from state + event to next state | `IDLE + START -> RUN` |
| Action | Code run during transition/state | start motor, send ACK |
| Table-driven FSM | Data table controls transitions | scalable protocol logic |

**Tips:** Use `enum` for states/events. Always handle default/invalid cases. Keep transition logic separate from hardware actions when possible.

---

## Exercises

| # | File | Problem | Expected Output (summary) | Key Concept |
|---|------|---------|---------------------------|-------------|
| 01 | [ex01_simple_toggle_fsm.c](solutions/ex01_simple_toggle_fsm.c) | Toggle LED state | ON/OFF sequence | State enum |
| 02 | [ex02_button_debounce.c](solutions/ex02_button_debounce.c) | Debounce button samples | Press detected | Debounce FSM |
| 03 | [ex03_traffic_light.c](solutions/ex03_traffic_light.c) | Cycle traffic states | Light sequence | Timed states |
| 04 | [ex04_motor_control.c](solutions/ex04_motor_control.c) | Start/stop/fault motor | Motor transitions | Events |
| 05 | [ex05_uart_line_parser.c](solutions/ex05_uart_line_parser.c) | Collect line until newline | Line printed | Parser FSM |
| 06 | [ex06_protocol_parser.c](solutions/ex06_protocol_parser.c) | Parse framed packet | Payload accepted | Byte FSM |
| 07 | [ex07_table_driven_fsm.c](solutions/ex07_table_driven_fsm.c) | Transition table | Next states printed | Table FSM |
| 08 | [ex08_state_entry_actions.c](solutions/ex08_state_entry_actions.c) | Run entry actions | Entry text printed | Actions |
| 09 | [ex09_timeout_state.c](solutions/ex09_timeout_state.c) | Timeout waiting state | Timeout event | Timeout |
| 10 | [ex10_menu_navigation.c](solutions/ex10_menu_navigation.c) | Menu next/select FSM | Menu states | UI FSM |
| 11 | [ex11_error_recovery.c](solutions/ex11_error_recovery.c) | Fault and reset recovery | Recovered state | Fault handling |
| 12 | [ex12_embedded_task_fsm.c](solutions/ex12_embedded_task_fsm.c) | Sensor task lifecycle | Init/read/send loop | Task FSM |

---

## Build & Run

```bash
cd c_practice/topic_15_state_machines/solutions
gcc ex01_simple_toggle_fsm.c -o ex01 && ./ex01
```
