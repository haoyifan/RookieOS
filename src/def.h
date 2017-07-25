#ifndef DEF_H
#define DEF_H

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/* Framebuffer base address */
#define FB_ADDRESS ((volatile char *)0x000B8000)

/*Framebuffer color */
#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_REG 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

/* The I/O ports */
/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */
#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/* The I/O port commands */
/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/* Base and limit of code and data segment */
#define GDT_BASE_CS 0x00000000
#define GDT_BASE_DS 0x10000000
#define GDT_LIMIT_CS 0xffffffff
#define GDT_LIMIT_DS 0xffffffff

/* Granularity */
#define GRANULARITY_CLEAR 0x0
#define GRANULARITY_SET 0x1

/* Default operation size */
#define OPERATION_SIZE_SEGMENT_16_BIT 0x0
#define OPERATION_SIZE_SEGMENT_32_BIT 0x1

/* 64-bit code segment (IA-32e mode only) */
#define CODE_SEG_MODE_UNUSED 0x0 
#define CODE_SEG_MODE_COMPATIBLE 0x0 
#define CODE_SEG_MODE_64 0x1 

/* Available for use by system software */
#define AVL_UNAVAILABLE 0x0
#define AVL_AVAILABLE 0x1

/* Segment present */
#define SEGMENT_NOT_PRESENT 0x0
#define SEGMENT_PRESENT 0x1

/* Descriptor privilege level */
#define PRIVILEGE_LEVEL_0 0x0
#define PRIVILEGE_LEVEL_1 0x1
#define PRIVILEGE_LEVEL_2 0x2
#define PRIVILEGE_LEVEL_3 0x3

/* Descriptor type */
#define SYSTEM_DESCRIPTOR 0x0
#define CODE_DATA__DESCRIPTOR 0x1

/* Data segment type bit */
#define DATA_TYPE_ACCESSED 0x1
#define DATA_TYPE_WRITE (0x1 << 1)
#define DATA_TYPE_EXPAND_DOWN (0x1 << 2)

/* Code segment type bit */
#define CODE_TYPE_ACCESSED 0x1
#define CODE_TYPE_READ (0x1 << 1)
#define CODE_TYPE_CONFORMING (0x1 << 2)

/* NOTE: since we use gcc compiler, we could use 
 * 0bxxx to express binary number. This is not a
 * portable method to express binary in C, since 
 * the standard does not have anything about binary
 * in C language
 */
/* System-segment and Gata-descriptor types */
/* For 32-bit mode */
#define TSS_16_BIT_AVAILABLE 0b0001
#define LDT 0b0010
#define TSS_16_BIT_BUSY 0b0011
#define CALL_GATE_16_BIT 0b0100
#define TASK_GATE 0b0101
#define INTERRUPT_GATE_16_BIT 0b0110
#define TRAP_GATE_16_BIT 0b0110
#define TSS_32_BIT_AVAILABLE 0b1001
#define TSS_32_BIT_BUSY 0b1011
#define CALL_GATE_32_BIT 0b1100
#define INTERRUPT_GATE_32_BIT 0b1110
#define TRAP_GATE_32_BIT 0b1111

/* For IA-32e mode */
#define UPPER_8_BYTE 0b0000
#define LDT 0b0010
#define TSS_64_BIT_AVAILABLE 0b1001
#define TSS_64_BIT_BUSY 0b1011
#define CALL_GATE_64_BIT 0b1100
#define INTERRUPT_GATE_64_BIT 0b1110
#define TRAP_GATE_64_BIT 0b1111

/* 
 * struct for segment descriptor
 */
struct segment_desc {
	unsigned char base_h	: 8;
	unsigned char granularity : 1;
	unsigned char op_size : 1;
	unsigned char code_seg : 1;
	unsigned char avl : 1;
	unsigned char limit_h	: 4;
	unsigned char seg_present : 1;
	unsigned char dpl : 2;
	unsigned char descriptor_type : 1;
	unsigned char type : 4;
	unsigned int base_l		: 24;
	unsigned short limit_l	: 16;
} __attribute__((packed));

/*
 * struct for Global Descriptor Table
 */
struct gdt {
	unsigned int address;
	unsigned short size;
} __attribute__((packed));

typedef unsigned long size_t;
#endif
