/* About
 *
 * Library for work with TWI interface
 * on AVR microcontrollers.
 *
 * Work cycle:
 * * Call twi_init if not calling.
 * * Send request WRITE or READ data
 * * Send of recive data
 * * Send STOP (end transmission)
 */


#define NOLAST 0
#define LAST 1
#define TWI_ERR(a) twi_err=a
extern int twi_err;

/* Init TWI lirbrary
 *
 * You must call this function before
 * any other functions (in this libarary).
 */
int twi_init(void);

/* Request read from TWI device.
 *
 * * dev -- address of device
 * * addr -- address of register
 */
int twi_req_read(uint8_t dev, uint8_t addr);

/* Request write to TWI device.
 *
 * * dev -- address of device
 * * addr -- address of register
 */

int twi_req_write(uint8_t dev, uint8_t addr);

/* Read data from TWI device.
 *
 * Before you need request for reading
 *  (by twi_req_read)
 *
 * Read data, for last byte you
 * must set LAST byte for TWI "NACK" send.
 *
 * After LAST byte you must twi_p_stop() call.
 */
int twi_p_read(int last);

/* Write data to TWI device.
 *
 * Before you need request for writing
 *  (by twi_req_write)
 *
 * Send data char by char to TWI device.
 *
 * After byte you must twi_p_stop() call.
 */
int twi_p_write(uint8_t data);

/* End of transmission.
 *
 * Send STOP signal to TWI device.
 */
int twi_p_stop(void);


