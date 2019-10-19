//device.h: usb functions using libusb
//Copyright 2006 Jeroen Domburg <s1fwx@jeroen.ietsmet.nl>
//This software is licensed under the GNU GPL.

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "cppcompat.h"
#include "loadram.h"
#include "stdio.h"
#include "device.h"
#ifdef	WIN32
#include "../include/usb.h"
#else
#include <usb.h>
#endif


#ifdef LINUX
#define HANDLE int
#endif

#define CMD_HEADER_ID "USBC"
#define CMD_MAX_TX 0x4000
#define CMD_BUFSIZE (CMD_MAX_TX + 0x50)

enum E_CMD_ID {
  CMD_INIT,
  CMD_ENTER_FMODE,
  CMD_SHUTDOWN,
  CMD_GET_SYSINFO,
  CMD_READ_BREC,
  CMD_WRITE_BREC,
  CMD_READ_FLASH,
  CMD_WRITE_FWARE
};
#define	CMD_ID	enum E_CMD_ID

enum E_CMD_MODE {
  CMD_MODE_WRITE=0x00,
  CMD_MODE_READ=0x80
};
#define	CMD_MODE	enum E_CMD_MODE


#define _CMD_INIT 0xCC
#define _CMD_ENTER_FMODE 0xCB
#define _CMD_SHUTDOWN 0x20
#define _CMD_READ_SYSINFO(_offset)  0x8905 | ((_offset) << 16)
#define _CMD_RWX_BREC(_offset)      0x8009 | ((_offset) << 16)
#define _CMD_READ_FLASH(_offset)    0x8008 | ((_offset) << 16)
#define _CMD_WRITE_FWARE(_offset)   0x0C08 | ((_offset) << 16)



#pragma pack(1)
typedef struct S_CMD
{
  uint8   id[4];      //[00] = "USBC" (0x55,0x53,0x42,0x43)
  uint32  undef0x04;  //[04] tag -> gets returned in reply
  uint32  size;       //[08] = size of data
  uint8   mode;       //[0C] = 0x80 on read, 0 otherwise
  uint8   undef0x0D;  //[0D]
  uint8   undef0x0E;  //[0E] = 0x0C
  uint32  cmd;        //[0F] = 0x05=>info, 0x09=>boot flash, 0x08=>flash
  uint32  unkwn0x13;  //[13]
  uint32  unkwn0x17;  //[17]
  uint32  undef0x1B;  //[1B] = 0
} CMD;                //[1F]
#pragma pack()

#define	LP_CMD	struct S_CMD *

/*Send binary object to ram code:
id=USBC
size=2400
mode=0 (write)
undefD=fe
undefE=10
cmd=0c003005 (byte2=?, byte3-4=addr, c00 here)
unknw13=0008cb03 (byte 3 = page (08=not-paged mem))
unknw17=00004124 (xferlen=2400) ('00' is in prev byte
unknw1B=00000041
Then an xfer containing the data, 0x2400 bytes (out, down) to endpoint 0x1

Setup calling thingy:
id=USBC
size=0
mode=F8 (??)
undefD=00
undefE=10
cmd=9f0c0010 //boot from addr 0c00?
unknw13=00240000
unknw17=00e57000

Reboot the device into that code
id=USBC
size=0
mode=F8 (??)
undefD=00
undefE=10
cmd=a0020020 //boot from addr 0000? (24-8) are CallingTaskAdd.
unknw13=00080000
unknw17=00e57000

*/

#define	USB_HANDLE	struct usb_dev_handle *

void    device_set_cmd(LP_CMD cmd, CMD_ID cmd_id, uint16 ofs, uint32 size);
//ofs=0
//size = CMD_MAX_TX

USB_HANDLE  device_open();
bool device_close(USB_HANDLE hd);
long    device_send(USB_HANDLE, void *, uint32);
long device_send_cmd(USB_HANDLE, LP_CMD , void *, uint32);
long device_send_cmd_id(USB_HANDLE, CMD_ID , void *, uint32);
//max_data=0;
//data=NULL

bool	device_detect(char drive);

#endif
