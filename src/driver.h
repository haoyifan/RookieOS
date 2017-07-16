#ifndef DRIVER_H
#define DRIVER_H

#include "helper.h"
#include "serial.h"

int fb_write(const char *buf, const unsigned int len);
int serial_write(const char *buf, const unsigned int len);

#endif
