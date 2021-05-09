#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/***************************************************************************
 *  Library:
 *      #include <xtend.h>
 *      -lxtend
 *
 *  Description:
 *      Verify that the filename extension on filename is either the
 *      valid extension provided or that extension followed by a
 *      compression extension, e.g. .gz, .bz2, .xz.
 *
 *  Arguments:
 *      filename:   Name of the file to be checked
 *      valid_ext:  Valid extension, not include .gz, .bz2, or .xz
 *
 *  Returns:
 *      true (defined in stdbool.h) if filename has a valid extension
 *      false if not
 *
 *  See also:
 *      gzip(1), bzip2(1), xz(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-05-04  Jason Bacon Begin
 ***************************************************************************/

bool    valid_extension(const char *filename, const char *valid_ext)

{
    char    *zip_exts[] = { ".gz", ".bz2", ".xz" },
	    *ext,
	    *compressed;
    size_t  c;

    if ( (ext = strrchr(filename, '.')) != NULL )
    {
	if ( strcmp(ext, valid_ext) == 0 )
	    return true;
	for (c = 0; c < sizeof(zip_exts) / sizeof(*zip_exts); ++c)
	{
	    if ( strcmp(ext, zip_exts[c]) == 0 )
	    {
		compressed = strdup(filename);
		// Already confirmed there's an extension, clip it
		*strrchr(compressed, '.') = '\0';
		if ( ((ext = strrchr(compressed, '.')) != NULL) &&
		     (strcmp(ext, valid_ext) == 0) )
		{
		    free(compressed);
		    return true;
		}
		free(compressed);
		break;
	    }
	}
    }
    fprintf(stderr, "Error: %s should have a %s[.%s] extension\n",
	    filename, valid_ext, "gz|bz2|xz");
    return false;
}
