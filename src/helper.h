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

/** gdt_init:
 * Initialize the code segment and data segment of the segment
 * descriptor
 */
void gdt_init();

/** kmemset:
 * To set a chunk of memory to be specific value
 */
void kmemset(void *ptr, const size_t sz, const char c);

/** init_seg_desc:
 *  initialize a specific segment descriptor
 */
void init_seg_desc(
		struct segment_desc *descriptor,
		const int base_addr,
		const int limit,
		const char granularity,
		const char operation_size_segment,
		const char code_segment,
		const char avl,
		const char seg_present,
		const char privilege,
		const char desc_type,
		const char desc_type_bit
		);

#endif
