#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include "../string.h"

int     main(int argc,char *argv[])

{
    char    string[100] = "  Aldred E. Neumann.";
    
    strtrim(string, " .");
    puts("Should be 'Alfred E. Neumann'");
    printf("'%s'\n", string);
    
    strlcpy(string, "       ", 100);
    strtrim(string, " .");
    puts("Should be ''");
    printf("'%s'\n", string);
    return EX_OK;
}

