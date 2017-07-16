#ifndef HELPER_H
#define HELPER_H

#include "def.h"
#include "io.h"

/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 * 
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write_cell:
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 *
 * @param i The location in the framebuffer
 * @param c The character
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

#endif
