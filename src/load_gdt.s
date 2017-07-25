global load_gdt

; Load the global descriptro table
; The first argument to the function is
; the address of the global descriptor table
load_gdt:
	mov eax, [esp + 8]
	lgdt [eax]

	; code here uses the previous cs
	jmp 0x08:flush_cs ; specify cs when jumping to flush_cs

flush_cs:
	; now we’ve changed cs to 0x08

	ret

