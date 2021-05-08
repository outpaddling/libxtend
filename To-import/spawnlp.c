#include <stdio.h>
#include <stdarg.h>
#include "xtend.h"

#if defined(__STDC__) || defined(MIPS)
int     spawnlp(int parent_action,int echo,char *infile, char *outfile,
		char *errfile,char *arg0,...)
#else
int     spawnlp(parent_action,echo,infile, outfile, errfile, arg0)
int     parent_action,echo;
char    *infile, *outfile, *errfile, *arg0;
#endif

{
    va_list list;
    char    *argv[100];
    int     c;
    
    va_start(list,arg0);
    argv[0] = arg0;
    for (c=1; (argv[c] = (char *)va_arg(list,char *)) != NULL; ++c)
	;
    return(spawnvp(parent_action,echo,argv,infile,outfile,errfile));
}

