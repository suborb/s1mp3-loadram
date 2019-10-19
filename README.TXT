LoadRAM v0.3.3-ALL (imported from archive.org)

loadram V0.3 (c) J. Domburg <loadram@jeroen.ietsmet.nl>. This software 
is licensed under the GPL.

This is a tool to upload small programs to the atj20xx memory and execute them.

It can upload 2 types of programs: small subroutines and complete apps.

Small subroutines:
The programs should be linked to address 0x3400 and in binary form. Usage:
put the mp3 player in firmware upgrade mode, use 'loadram program.bin'. You
can return to fw upgrade mode immediately by executing a 'ret'. Programs
uploaded this way can't be larger than 3072 bytes, though programs
larger than 1K may fail too, depending on your fw.

Complete programs:
These need a second stage loader, which is provided with the program. Usage:
put the mp3 player in firmware upgrade mode, use 
'loadram 2ndstage.bin program.bin'. The programs are loaded from address
0x0 and run from address 0x600, so you can upload any .ap file made by the
S1SDK directly. Programs are limited to 14336 bytes because they overwrite
the 2nd stage bootloader otherwise. The program hangs for a few secs after
the program has been loaded, that's because the 2nd stage loader immedia-
tely jumps to the program without tending to the USB bus first.

Two modes of operations are supported: ADFU and firmware-upgrade mode.
Firmware-upgrade-mode requires that the player is manually set to
the firmware upgrade. loadram defaults to that mode.
ADFU-mode is the rescue-mode your player boots in if anything
is wrong with its flash (e.g. pins shorted). Use the command
argument '-u' to use this mode. Note: This mode doesn't support
returning from the called subroutine

RECORD.AP is the animation example from the S1SDK. If you want to try the
program, you can upload it to your player.

Disclaimer:
THIS IS PRE-ALPHA CODE! While it probably won't fuck up your player, I can't
guarantee that. If you destroy anything using this software, I'm not 
responsible.
