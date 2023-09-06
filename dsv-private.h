
#ifndef _XTEND_DSV_PRIVATE_H_
#define _XTEND_DSV_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

struct xt_dsv_line
{
    size_t      num_fields_array_size,
		num_fields;
    char        **fields,
		*delims;
};

#ifdef __cplusplus
}
#endif

#include "dsv.h"

#endif  // _XTEND_DSV_PRIVATE_H_
