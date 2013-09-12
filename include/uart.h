#ifndef _UART_H_
#define _UART_H_
///
// Call it before parse usage..
//
int uart_init(void);

/**
 * Switch on printf and frends.
 *
 */
int uart_stdio(void);

/** Switch on only stdin
 */
void uart_stdin(void);

/** Switch on only stdout
 */
void uart_stdout(void);

/** Switch on only stderr
 */
void uart_stderr(void);

/** Block and wait char from UART.
 *
 */
int getch(void);

/** Wait char from UART don't block.
 */
int trych(void);

#endif /* _IR_H_ */
