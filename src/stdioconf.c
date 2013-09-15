/*
 * stdio.c  - libc stdio connector
 * Creation Date: 2012-05-20
 *
 * Copyright (C) 2012 Leonid Myravjev (asm@asm.pp.ru)
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <avr/io.h>
#include <avr/wdt.h>

#include <uart.h>

#define UART_STDOUT
#ifdef UART_STDOUT
#include <stdio.h>

static int uart_get_nonblock(FILE* file) {
  return getbyte_nonblock();
}
static int uart_put(char ch,FILE *file) {
  return bchar_put(ch);
}

static FILE fd_uart_stdio=FDEV_SETUP_STREAM(uart_put, uart_get_nonblock, _FDEV_SETUP_RW);

void stdioconf_stdin(void) {
    stdin=&fd_uart_stdio;
}
void stdioconf_stdout(void) {
    stdout=&fd_uart_stdio;
}
void stdioconf_stderr(void) {
    stderr=&fd_uart_stdio;
}

int getch(void) {
  int res;
  while((res=getchar())==-1){};
  return res;
}

int trych(void) {
  return getchar();
}


int stdioconf_stdio(void){
  stdioconf_stdout();
  stdioconf_stderr();
  stdioconf_stdin();
  //FIXME add stdio
    return 0;
}//*/
#endif /* UART_STDOUT */
