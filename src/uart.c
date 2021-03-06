/*
 * uart.c  - uart utils
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
static void uart_bchar(char c){
      while ( !( UCSR0A & (1<<UDRE0)) );
      UDR0 = c;
}

int bchar_put(char ch)
{
  if(ch == '\n')
    uart_bchar('\r');
  uart_bchar(ch);
  return 0;
}

int getbyte_nonblock(void) {
  if ( (UCSR0A & (1<<RXC0)) )
    return UDR0;
  else
    return -1;
}

int getbyte(void) {
  while ( (UCSR0A & (1<<RXC0)) ==0 );
  return UDR0;
}

#endif /* UART_STDOUT */

int uart_init(void){
#ifndef F_CPU
#error Please set F_CPU!
#endif
  UCSR0A = 0;
  UCSR0B = 0x18;
  UCSR0B |= RXEN0;
  UCSR0C = 0x06;


//#define BAUD 9600
#define BAUD 38400
//#define BAUD 115200
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif
    return 0;
}
