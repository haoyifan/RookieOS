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
	kmemset((void*)gdt, sizeof(struct segment_desc), 0);

	// code segment
	init_seg_desc(
		&gdt[1],
		GDT_BASE_CS,
		GDT_LIMIT_CS,
		GRANULARITY_SET,
		OPERATION_SIZE_SEGMENT_32_BIT,
		CODE_SEG_MODE_UNUSED,
		AVL_AVAILABLE, 
		SEGMENT_PRESENT, 
		PRIVILEGE_LEVEL_0,
		CODE_DATA__DESCRIPTOR,
		DATA_TYPE_ACCESSED | DATA_TYPE_EXPAND_DOWN | DATA_TYPE_WRITE
	);


	// data segment
	init_seg_desc(
		&gdt[2],
		GDT_BASE_DS,
		GDT_LIMIT_DS,
		GRANULARITY_SET,
		OPERATION_SIZE_SEGMENT_32_BIT,
		CODE_SEG_MODE_UNUSED,
		AVL_AVAILABLE, 
		SEGMENT_PRESENT, 
		PRIVILEGE_LEVEL_0,
		CODE_DATA__DESCRIPTOR,
		CODE_TYPE_ACCESSED | CODE_TYPE_CONFORMING | CODE_TYPE_READ
	);

	struct gdt gdt_desc;
	gdt_desc.address = (unsigned int) gdt;
	gdt_desc.size = sizeof(gdt);

	load_gdt((unsigned int)&gdt_desc);

	return;
}

void kmemset(void *ptr, const size_t sz, const char c) {
	char *_ptr = (char*)ptr;

	size_t i = 0;
	for(; i < sz; ++i, ++_ptr) {
		*_ptr = c;	
	}
}

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
		) {

	descriptor->base_h = (base_addr >> 24);
	descriptor->base_l = (base_addr & 0xffffff);

	descriptor->limit_h = (limit >> 28);
	descriptor->limit_l = (limit & 0xffff);

	descriptor->granularity |= granularity;
	descriptor->op_size |= operation_size_segment;
	descriptor->code_seg |= code_segment;
	descriptor->avl |= avl;
	descriptor->seg_present |= seg_present;
	descriptor->dpl |= privilege;
	descriptor->descriptor_type |= desc_type;
	descriptor->type |= desc_type_bit;

}
