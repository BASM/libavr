#include <stdio.h>
#include <uart.h>

int main(void){

  uart_init();
  uart_stdio();

  printf("Hello world!\n");

  return 0;
}
