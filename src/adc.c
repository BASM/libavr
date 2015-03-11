
#include <avr/io.h>

#include <adc.h>

int adc_init(void) {


  ///ADC 
  // 000 0x00 -- 2
  // 001 0x01 -- 2
  // 010 0x02 -- 4
  // 011 0x03 -- 8
  // 100 0x04 -- 16
  // 101 0x05 -- 32
  // 110 0x06 -- 64
  // 111 0x07 -- 128
  ADCSRA |=  (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar 
  ADMUX |= (1 << REFS0) | (1 << REFS1); // Set ADC reference to AVCC

  // 0110 0x06 -- ADC6
  // 0111 0x07 -- ADC7
  // 1000 0x08 -- ADC8(temperature)
  // 1110 0x0e -- 1.1v
  // 1111 0x0f -- GND
  ADMUX |= 0x07;


  ADCSRA |= (1 << ADEN);  // Enable ADC
  ADCSRA |= (1 << ADSC);  // Start A2D Conversions

  return 0;
}


int adc_get(int num) {

  int r=0;
  ADCSRA|=(1<<ADIF);
  while ((ADCSRA&(1<<ADIF))){};

  ADMUX &= ~(0xf);
  ADMUX |= num&0x0f;

  ADCSRA |= (1 << ADSC); 

  while (!(ADCSRA&(1<<ADIF))){};
  //conversion is ready
  // reset converstion complete flag
  ADCSRA|=(1<<ADIF);

  // read data, ADCL - first
  r=ADCL;
  r=(ADCH<<8)|r;


  return r;
}
