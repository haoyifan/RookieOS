#include "driver.h"


int write(const char *buf, const unsigned int len) {

	unsigned int i = 0;

	for(; i < len; ++i) {
		fb_write_cell(2 * i, *(buf + i), FB_WHITE, FB_BLACK);	
		fb_move_cursor(i + 1);
	}

	return 0;
}

