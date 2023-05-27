
struct dsv_line
{
    size_t      array_size,
		num_fields;
    char        **fields,
		*delims;
};

#include "dsv.h"
