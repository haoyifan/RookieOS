#include "driver.h"


int fb_write(const char *buf, const unsigned int len) {

	unsigned int i = 0;

	for(; i < len; ++i) {
		fb_write_cell(2 * i, *(buf + i), FB_WHITE, FB_BLACK);	
		fb_move_cursor(i + 1);
	}

	return 0;
}

int serial_write(const char *buf, const unsigned int len) {

	serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
	serial_configure_line(SERIAL_COM1_BASE);
	serial_configure_buffer(SERIAL_COM1_BASE);
	serial_configure_modem(SERIAL_COM1_BASE);

	unsigned int i = 0;

	for(; i < len; ++i) {
		while(!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE));

		serial_transmit_data(SERIAL_COM1_BASE, *(buf + i));
	}

	return 0;
}
