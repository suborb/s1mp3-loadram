# fixed up for linux & win32

ifneq ($(ENV),WIN32)
CCFLAGS=-O2 -I/usr/src -DLINUX -Wall
EXT=
DEL=rm -f
DEST=
else
CC=gcc
CCFLAGS=-O2 -I. -DWIN32 -Wall -Llib/gcc
EXT=.exe
DEL=@del
DEST=win32-bin/
endif
LDFLAGS=-lusb

all: loadram

loadram: src/*.c src/*.h
	$(CC) $(CCFLAGS) src/*.c $(LDFLAGS) -o $(DEST)$@$(EXT)
	@echo $@ compiled successfully


clean:
	$(DEL) *.o
	$(DEL) loadram$(EXT)
	$(DEL) src/*.map src/*.obj src/*.sym
	@echo Clean successful

2ndstage: src/2ndstage.asm
	z80asm -b src/2ndstage.asm
	if [ -e 2ndstage.err ]; then cat 2ndstage.err; fi
	mv -f src/2ndstage.bin .

