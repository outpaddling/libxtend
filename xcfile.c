#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "xtendc.h"

/***************************************************************************
 *  Description:
 *      Open a raw data file using foipen() or a gzipped, bzipped, or
 *      xzipped file using popen().  Must be used in conjunction with
 *      xc_fclose() to ensure that fclose() or pclose() is called where
 *      appropriate.
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-09  Jason Bacon Begin
 ***************************************************************************/

FILE    *xc_fopen(const char *filename, const char *mode)

{
    char    *ext = strrchr(filename, '.'),
	    cmd[XC_CMD_MAX + 1];
    
    if ( (strcmp(mode, "r") != 0 ) && (strcmp(mode, "w") != 0) )
    {
	fprintf(stderr, "xc_open(): Only \"r\" and \"w\" modes supported.\n");
	return NULL;
    }
    
    if ( ext == NULL )
    {
	fprintf(stderr, "xc_open(): No filename extension on %s.\n", filename);
	return NULL;
    }

    if ( *mode == 'r' )
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "zcat %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "bzcat %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "xzcat %s", filename);
	    return popen(cmd, mode);
	}
	else
	    return fopen(filename, mode);
    }
    else    // "w"
    {
	if ( strcmp(ext, ".gz") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "gzip -c > %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".bz2") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "bzip2 -c > %s", filename);
	    return popen(cmd, mode);
	}
	else if ( strcmp(ext, ".xz") == 0 )
	{
	    snprintf(cmd, XC_CMD_MAX, "xz -c > %s", filename);
	    return popen(cmd, mode);
	}
	else
	    return fopen(filename, mode);
    }
}


/***************************************************************************
 *  Description:
 *      Close a FILE stream with fclose() or pclose() as appropriate
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-04-10  Jason Bacon Begin
 ***************************************************************************/

int     xc_fclose(FILE *stream)

{
    struct stat stat;
    
    fstat(fileno(stream), &stat);
    if ( S_ISFIFO(stat.st_mode) )
	return pclose(stream);
    else
	return fclose(stream);
}
