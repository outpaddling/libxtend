#include "xtend.h"

char   *strbasecpy(dest, src, dest_base, len)
char   *dest, *src, *dest_base;
int     len;

{
    char   *save_dest, *end;

    save_dest = dest;
    len -= dest-dest_base;
    end = src + len;
    while ((*src != '\0') && (src < end))
	*dest++ = *src++;
    *dest = '\0';
    return (save_dest);
}
