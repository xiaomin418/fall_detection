#include "fsl_uart_cmsis.h"

void uart0_init(void);
void uart0_Printf(char *pcFmt,...);
extern volatile bool rxOnGoing;

void uart2_init(void);
void uart2_Printf(char *pcFmt,...);

void uart4_init(void);
void uart4_Printf(char *pcFmt,...);