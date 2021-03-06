#ifndef _UART_H_
#define _UART_H_
///
// Call it before parse usage..
//
int uart_init(void);

int getbyte_nonblock(void);
int bchar_put(char ch);

/**
 * Switch on printf and frends.
 *
 */
int stdioconf_stdio(void);

/** Switch on only stdin
 */
void stdioconf_stdin(void);

/** Switch on only stdout
 */
void stdioconf_stdout(void);

/** Switch on only stderr
 */
void stdioconf_stderr(void);

/** Block and wait char from UART.
 *
 */
int getch(void);

int getbyte(void);
/** Wait char from UART don't block.
 */
int trych(void);

#endif /* _IR_H_ */
