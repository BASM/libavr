/** Work whish ADC
 */


/** ADC initialization
 *
 * options: FIXME
 *
 */

int adc_init(void);

/** Get result from ADC.
 *
 * number -- number of channel on ADC.
 *
 * 0x01-0x07 -- Channels
 * 0x08      -- Termpearture
 * 0x0e      -- 1.1v
 * 0x0f      -- GND
 *
 */

int adc_get(int number);

