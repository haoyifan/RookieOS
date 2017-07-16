#include "serial.h"

void serial_configure_baud_rate(const unsigned short com, const unsigned short divisor)
{
	outb(SERIAL_LINE_COMMAND_PORT(com),
			SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com),
			(divisor >> 8) & 0x00FF);
	outb(SERIAL_DATA_PORT(com),
			divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
	/* Bit:		| 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content: | d | b | prty  | s |  dl |
	 * Value:	| 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com) {

	/* Bit:		| 7 6 | 5  | 4 |  3  |  2  |  1  | 0 |
	 * Content: | lvl | bs | r | dma | clt | clr | e |
	 * Value:	| 1 1 | 0  | 0 |  0  |  1  |  1  | 1 | = 0xC7
	 */
	outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com) {

	/* Bit:		| 7 | 6 | 5  | 4  |  3  |  2  |  1  |  0  |
	 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
	 * Value:	| 0 | 0 | 0  | 0  |  0  |  0  |  1  |  1  |
	 */
	outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com)
{
	/* 0x20 = 0010 0000 */
	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_transmit_data(unsigned int com, unsigned char data) {
	outb(SERIAL_DATA_PORT(com), data);

	return 0;
}
