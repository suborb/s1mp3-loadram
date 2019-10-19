//loadram.h: main source code header
//Copyright 2006 Jeroen Domburg <s1fwx@jeroen.ietsmet.nl>
//This software is licensed under the GNU GPL.

#ifndef __LOADRAM_H_
#define __LOADRAM_H_

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef LINUX
#include <sys/types.h>

#include <unistd.h>

#include <scsi/sg.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <string.h>
#include <stdint.h>
#include <errno.h>
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
#define DWORD uint32
#define BYTE uint8
#define ERROR_NOT_ENOUGH_MEMORY ENOMEM
#define ERROR_READ_FAULT EIO
#define ERROR_SUCCESS 0
#define ERROR_INVALID_DATA EIO
#define ERROR_WRITE_FAULT EIO
#define ERROR_BAD_FORMAT EINVAL
#define ERROR_BAD_COMMAND EBADMSG
#define LPSTR char *
#define LPCSTR const char *
#define LPTSTR char *
#define LPVOID void *
#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>

typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;
typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#endif

#include "device.h"

int display_error(int);
int extract_to_file(char *filename, FILE *fh_src, size_t fofs, uint32 fsize, uint32 *sum32p);


#endif	// __LOADRAM_H_

