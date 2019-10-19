org 0x3800
;2ndstage.asm
;This is a really small program, to be used by loadram as a second stage loader.
;It basically is a really simple usb implementation, with the initialisation
;code left out, because the original os already did that for us.

;This code lives from 0x3800 to 0x3fff, cause that way all the bytes under that 
;can be overwritten. It'll jump to 0x600 when it's finished, so .aps can be 
;uploaded that way without any modification.
;
;This code is (c) 2006 J. Domburg and licensed under the GNU GPL. No warranty 
;of any kind is explicitely or implicitely stated.
;
;15? jun 2006: Initial release (Sprite_tm)
;18 jun 2006: Cleaned up, code now is relocatable.

start:
;disable any nasty ints which could come and haunt us
    di
;Load SP with a sane value >0x3400
    ld hl,0x3ff0
    ld sp,hl

;enable lcd xs for progress indicator kinda thingy
    ld a,0x7
    out (0x5),a
    ld a,0x30
    out (0x70),a
    ld a,0x1f
    out (0x70),a
    ld a,0x1f
    out (0xee),a
    ld a,0x18
    out (2),a

;put a bunch of ffs to the lcd so we can see we're in the 2nd stage bootloader
    ld a,0xff
    ld (0x8001),a
    ld (0x8001),a
    ld (0x8001),a
    ld (0x8001),a
    ld (0x8001),a
    ld (0x8001),a
    ld (0x8001),a


;USB works as following: it can only transfer to B1/B2. B1/B2 together are
;called ZRAM2, and ZRAM2 is banked from 0x4000 when r5=...111. B0 is the 
;same as ZRAM1. Logically, B1=0x4000-0x47FF and B2=0x4800-0x4FFF if both
;are mapped to uC, else whatever is selected shows up at 0x4000.

    ;bank in zram2 (b1/2)
    in a,(0x5)
    or 0x7
    out (0x5),a
    
    ;writing of usb data will start @ addr 0
    ld de,0x0

nextpacketpiece:
;let usb use b1 memory
    in a,(0x70)
    and 0xcf
    or 0x10
    out (0x70),a
    
;set usb to ep1 output mode
    
    ;set ep1 out
    ld a,3
    out (0x60),a
    ld a,0
    out (0x61),a
    ld a,0x3f
    out (0x66),a
    ;start address (in b1) = 0 (in b1, mind you)
    xor a
    out (0x62),a
    out (0x63),a
    ;byte counter (0x800)
    ld hl,0x800
    ld a,h
    out (0x64),a
    ld a,l
    out (0x65),a
    
    ;Indicator
    ld a,0xaa
    ld (0x8001),a
    
wait:
    ;feed the watchdog
    in      a,(0x4e)
    or      0x08
    out     (0x4e),a

    ;ep1 thingy occured yet?
    in a,(0x68)
    and a,8
    jr z,wait

    ;indicator
    ld a,0x55
    ld (0x8001),a

wait2:
    ;feed the watchdog
    in      a,(0x4e)
    or      0x08
    out     (0x4e),a

    ;ep1 thingy occured yet?
    in a,(0x68)
    and a,8
    jr nz,wait2

    ;indicator
    ld a,0xff
    ld (0x8001),a

;let uC use b1
    in a,(0x70)
    or 0x30
    out (0x70),a

;move usb received data from b1 to where it belongs
    ld hl,0x4000
    ld bc,0x800
    ldir
    
;check if this was the last write (de=0x3800)
    ld a,d
    cp 0x38
    jr z,lastpacket
    
;Nope -> get next piece of code
    jr nextpacketpiece
    
;Yes -> jump to start of code (at 0x600)
lastpacket:
    ld hl,0x600
    push hl
    ret

