;Output a test pattern to the display
org 0
defs 0x600

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
	
	ld hl,text
	ld c,64
loop:
	ld a,(hl)
	ld (0x8001),a
	inc hl
	dec c
	jr nz,loop

hang:
	di
	in      a,(0x4e)
	or      0x08 
	out     (0x4e),a
	jr hang

text:
defb @00000000
defb @00000000
defb @00000000
defb @00000000
defb @00000000
defb @00000000
defb @11111110
defb @00010000
defb @11111110
defb @00000000
defb @11111110
defb @10010010
defb @10000010
defb @00000000
defb @11111110
defb @00000010
defb @00000010
defb @00000000
defb @11111110
defb @00000010
defb @00000010
defb @00000000
defb @01111100
defb @10000010
defb @01111100
defb @00000000
defb @00000000
defb @00000000
defb @11111100
defb @00000010
defb @01111100
defb @00000010
defb @11111100
defb @00000000
defb @01111110
defb @10000001
defb @01111110
defb @00000000
defb @11111110
defb @10011000
defb @01110110
defb @00000000
defb @11111110
defb @00000010
defb @00000010
defb @00000000
defb @11111110
defb @10000010
defb @01111100
defb @00000000
defb @11001011
defb @00000000
defb @00000000
defb @00000000
defb @01100110
defb @00000000
defb @01000010
defb @00111100
defb @00000000
defb @00000000
defb @00000000
defb @00000000

