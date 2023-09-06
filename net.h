#ifndef _XTEND_NET_H_
#define _XTEND_NET_H_

#ifdef __cplusplus
extern "C" {
#endif

int xt_resolve_hostname(const char *hostname, char *ip, size_t ip_buff_len);

#ifndef _XTEND_COMMON_H_
#include "common.h"
#endif

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_NET_H_
