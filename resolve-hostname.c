#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "string.h"     // strlcpy() on Linux
#include "net.h"

/***************************************************************************
 *  Name:
 *      resolve_hostname() - Convert hostname to IP address
 *
 *  Library:
 *      #include <xtend/string.h>
 *      -lxtend
 *
 *  Description:
 *      Resolve a host name to an IP address.
 *  
 *  Arguments:
 *      hostname    Name of the host to be resolved
 *      ip          Character array to receive IP address
 *      ip_buff_len Size of ip array including null byte
 *
 *  Returns:
 *      XT_OK on success, XT_FAIL otherwise
 *
 *  Examples:
 *      #define IP_MAX_CHARS    64
 *
 *      char    *hostname = "my.site.edu",
 *              ip[IP_MAX_CHARS + 1];
 *
 *      if ( resolve_hostname(hostname, ip, IP_MAX_CHARS + 1) == XT_OK )
 *      {
 *      }
 *
 *  See also:
 *      gethostbyname(3), getaddrinfo(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2021-09-28  Jason Bacon Begin
 ***************************************************************************/

int     resolve_hostname(const char *hostname, char *ip, size_t ip_buff_len)

{
    struct hostent  *ent;
    struct in_addr  **address_list;

    /*
     *  FIXME: Reimplement with getaddrinfo() to better support IPv6
     *  gethostbyname() is simpler and will suffice for now
     */
    
    if ( (ent = gethostbyname(hostname)) == NULL )
    {
	herror("resolve_hostname(): gethostbyname() failed");
	fprintf(stderr, "hostname = %s\n", hostname);
	fputs("Check /etc/hosts and /etc/resolv.conf.\n", stderr);
	return XT_FAIL;
    }

    // Just take first address
    address_list = (struct in_addr **)ent->h_addr_list;
    strlcpy(ip, inet_ntoa(*address_list[0]), ip_buff_len);
    
    return XT_OK;
}
