#ifndef SERIAL_H
#define SERIAL_H

#include "io.h"
#include "def.h"

/** serial_configure_baud_rate:
 * Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s.
 * @param com The COM port to configure
 * @param divisor The divisor
 */
void serial_configure_baud_rate(const unsigned short com, const unsigned short divisor);

/** serial_configure_line:
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 *
 * @param com The serial port to configure
 */
void serial_configure_line(unsigned short com);

/** serial_configure_buffer:
 * Configures the buffer of the given serial port. The port is set to have 
 * a buffer of 14 bytes, clear rcv and tx FIFO queues, enable FIFO
 *
 * @param com The serial port to configure
 */
void serial_configure_buffer(unsigned short com);

/** serial_configure_modem:
 * Configures the modem of the given serial port. The port is set to have 
 * interrupt disabled
 *
 * @param com The serial port to configure
 */
void serial_configure_modem(unsigned short com);

/** serial_is_transmit_fifo_empty:
 * Checks whether the transmit FIFO queue is empty or not for the given COM
 * port.
 *
 * @param com The COM port
 * @return 0 if the transmit FIFO queue is not empty* 1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/** serial_transmit_data:
 * transmit data to specific com port
 *
 * @param com The COM port
 * @param data the data to be transmitted
 * @return 0 if the transmit succeed
 */
int serial_transmit_data(unsigned int com, unsigned char data);
#endif
