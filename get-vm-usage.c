#include <stdio.h>
#include <unistd.h>

#include "proc.h"

/***************************************************************************
 *  Use auto-c2man to generate a man page from this comment
 *
 *  Name:
 *      xt_get_vm_usage() - Report current virtual memory usage
 *
 *  Library:
 *      #include <xtend/proc.h>
 *      -lxtend
 *
 *  Description:
 *      .B xt_get_vm_usage()
 *      returns the process' current virtual memory usage in bytes.
 *  
 *  Arguments:
 *      None
 *
 *  Returns:
 *      Current virtual memory use, or 0 if an error occurs
 *
 *  Examples:
 *      #include <xtend/proc.h>
 *
 *      printf("VM usage = %zu\n", xt_get_vm_usage());
 *
 *  See also:
 *      ps(1)
 *
 *  History: 
 *  Date        Name        Modification
 *  2025-10-05  Jason Bacon Begin
 ***************************************************************************/

size_t  xt_get_vm_usage(void)

{
    size_t  vm_usage;
    FILE    *fp;
    char    cmd_str[XT_CMD_MAX_CHARS + 1];
    
    // Spawning a "ps" process is the only portable way to get this info.
    // On BSD, we could get this using the libprocstat() API.
    // Linux has no API, there we parse /proc files.
    snprintf(cmd_str, XT_CMD_MAX_CHARS + 1, "ps -o vsz= %u", getpid());
    if ( (fp = popen(cmd_str, "r")) != NULL )
    {
        fscanf(fp, "%zu", &vm_usage);
        pclose(fp);
    }
    else
        vm_usage = 0;   // 0 is impossible, so good sentinel value

    return vm_usage;
}
