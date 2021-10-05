#ifndef _XT_NET_H_
#define _XT_NET_H_

int resolve_hostname(const char *hostname, char *ip, size_t ip_buff_len);

#ifndef _XT_COMMON_H
#include "common.h"
#endif

#endif
