#include "driver.h"

int main() {
	const char str[] = "Hello world";
	fb_write(str, sizeof(str));
	serial_write(str, sizeof(str));
	gdt_init();

	return 0;
}
