#ifndef _XTEND_COMMON_H_
#define _XTEND_COMMON_H_

#define XT_FORMAT_MAX_CHARS 4096
#define XT_CMD_MAX_CHARS    4096

#define XT_OK               0
#define XT_FAIL             -1
#define XT_MALLOC_FAILED    -2

// FIXME: Return this instead of EOF in dsv_read*()
// Don't trust that EOF is -1 on all platforms
#define XT_READ_EOF             -1
#define XT_READ_BUFF_OVERFLOW   -2

#endif // _XTEND_COMMON_H
