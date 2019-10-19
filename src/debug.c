#include <stdio.h>
#include <stdarg.h>

int debug_verbosity;

void dprintf(int level, char *msg, ...)
{
    va_list fmtargs;
    va_start(fmtargs,msg);
    if (level<=debug_verbosity) {
	vfprintf(stderr,msg,fmtargs);
    }
    va_end(fmtargs);
}
