#include "helper.h"
#include "load_gdt.h"

void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	volatile char *fb = FB_ADDRESS;
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void gdt_init() {

	/* The first one is null descriptor*/
	/* The second one is code segment descriptor*/
	/* The third one is data segment descriptor*/
	struct segment_desc gdt[3];

	// null segment
	gdt[0].base_h = 0;
	gdt[0].base_l = 0;
	gdt[0].limit_h = 0;
	gdt[0].limit_l = 0;
	gdt[0].attr = 0;
	gdt[0].attribute = 0;

	// code segment
	gdt[1].base_h = (GDT_BASE_CS >> 24);
	gdt[1].base_l = (GDT_BASE_CS) & 0xffffff;
	gdt[1].limit_h = (GDT_LIMIT_CS >> 28);
	gdt[1].limit_l = (GDT_LIMIT_CS) & 0xffff;
	gdt[1].attr = 0;
	gdt[1].attribute = 0;

	// data segment
	gdt[2].base_h = (GDT_BASE_DS >> 24);
	gdt[2].base_l = (GDT_BASE_DS) & 0xffffff;
	gdt[2].limit_h = (GDT_LIMIT_DS >> 28);
	gdt[2].limit_l = (GDT_LIMIT_DS) & 0xffff;
	gdt[2].attr = 0;
	gdt[2].attribute = 0;

	struct gdt gdt_desc;
	gdt_desc.address = (unsigned int) gdt;
	gdt_desc.size = sizeof(gdt);

	load_gdt((unsigned int)&gdt_desc);

	return;
}

