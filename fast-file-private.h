#ifndef _XTEND_FAST_FILE_PRIVATE_H_
#define _XTEND_FAST_FILE_PRIVATE_H_

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned char   *buff;
    unsigned char   *start_ptr;
    ssize_t         bytes_read;
    ssize_t         buff_index;
    ssize_t         disk_block_size;
    ssize_t         buff_size;
    int             fd;
    int             flags;
    pid_t           child_pid;
}   xt_ffile_t;

#include "fast-file.h"

#ifdef  __cplusplus
}
#endif

#endif
