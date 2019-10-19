;Output a test pattern to the display
org 0x3400



start:
    
	ld a,0x7
	out (0x5),a
	ld a,0x30
	out (0x70), a
	
	ld a,0x1f
	out (0xee),a
	
	ld a, 0x18
	out (0x2),a
	
	in a,(0xee)
	or 1
	out (0xee),a
	
	ld h,0
	ld l,0xff
loop:
	ld (0x8001),a
	inc a
	dec hl
	djnz loop


	ret
hang:
	di
	in      a,(0x4e)
	or      0x08 
	out     (0x4e),a
	jr hang
