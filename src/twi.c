#include <inttypes.h>

#include <avr/power.h>

#include <util/delay.h>
#include <util/twi.h>

#include <twi.h>

static int twi_wait_int(void);
static int twi_p_start(void);
static int twi_wait_int(void);
static int twi_p_sla(uint8_t dev, int type);

int twi_err=0;

int twi_init(void)
{
    power_twi_enable();
    TWBR=0xFF;
    TWSR=3;
    return 0;
}

int twi_req_read(uint8_t dev, uint8_t addr)
{
  if(twi_p_start()) return 1;
  if(twi_p_sla(dev, TW_WRITE)) return 2;
  if(twi_p_write(addr)) return 3;

  if(twi_p_start()) return 4;
  if(twi_p_sla(dev, TW_READ)) return 5;
  return 0;
}


int twi_p_write(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);
  if(twi_wait_int())                {TWI_ERR(7); return 7;}
  if(TW_STATUS != TW_MT_DATA_ACK) {TWI_ERR(8); return 8;}
  return 0;
}

int twi_req_write(uint8_t dev, uint8_t addr)
{
  if(twi_p_start()) return 1;
  if(twi_p_sla(dev, TW_WRITE)) return 2;
  if(twi_p_write(addr)) return 3;
  twi_p_stop();
  _delay_us(100);
  
  if(twi_p_start()) return 4;
  if(twi_p_sla(dev, TW_WRITE)) return 5;
  if(twi_p_write(addr)) return 6;

  return 0;
}

int twi_p_read(int last)
{
  if(last==NOLAST)
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
  else
    TWCR = (1<<TWINT) | (1<<TWEN);
  if(twi_wait_int())                {TWI_ERR(9);  return -9;}

  if(last==NOLAST){
    if(TW_STATUS != TW_MR_DATA_ACK) {TWI_ERR(10); return -10;}
  }else{
    if(TW_STATUS != TW_MR_DATA_NACK) {TWI_ERR(11); return -11;}
  }

  return TWDR;
}

int twi_p_stop(void)
{
  TWCR = (1<<TWINT)|(1<<TWSTO)| (1<<TWEN);
  return 0;
}

static int twi_wait_int(void)
{
  uint32_t i=0;
  while (!(TWCR & (1<<TWINT)))
  {
    if(i++>=0xFFFF){
      TWCR = (1<<TWINT) | (1<<TWEN);
      if( (TWSR&0xF8) == 0 ) //BUS ERROR
        TWCR=0; //RESET
      return 1;
    }
    _delay_us(1);
  }
  return 0;
}

static int twi_p_start(){
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  if(twi_wait_int())             {TWI_ERR(1); return 1;}
  if( (TW_STATUS != TW_START) &&
      (TW_STATUS != TW_REP_START) ){
    TWI_ERR(2); return 2;}
  return 0;
}

static int twi_p_sla(uint8_t dev, int type)
{
  TWDR = (dev<<1) | type;
  TWCR = (1<<TWINT) | (1<<TWEN);
  if(twi_wait_int())                 {TWI_ERR(5); return 5;}
  if(type==TW_WRITE) {
    if(TW_STATUS != TW_MT_SLA_ACK) {TWI_ERR(6); return 6;}
  }else{//type==TW_READ
    if(TW_STATUS != TW_MR_SLA_ACK) {TWI_ERR(7); return 7;}
  }
  return 0;
}
