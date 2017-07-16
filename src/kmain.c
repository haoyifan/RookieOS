#include "driver.h"

int main() {
	fb_write("Hello World", 11);
	serial_write("Serial Hello World", 18);
	return 0;
}
