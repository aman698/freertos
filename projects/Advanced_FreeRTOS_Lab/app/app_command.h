#ifndef APP_COMMAND_H
#define APP_COMMAND_H

void AppCommand_Init(void);
void AppCommand_OnRxByteFromISR(uint8_t b);
void AppCommand_StartUartRx(void);

#endif
