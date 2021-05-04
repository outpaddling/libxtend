#include <string.h>
#include "biostring.h"

int     strptrcmp(const char **p1, const char **p2)

{
    return strcmp(*p1, *p2);
}
