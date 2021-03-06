#ifndef _XTEND_PROC_H_
#define _XTEND_PROC_H_

/*
 *  Process control
 */

/* spawn*() parent_action */
#define P_NOWAIT  0
#define P_WAIT    1

/* spawn*() echo */
#define P_NOECHO  0
#define P_ECHO    1

#define P_TERM_STATUS(s)    ((s) & 0xff)
#define P_EXIT_CODE(s)      (((s) & 0x0000ff00) >> 8)
#define P_EXEC_FAILED(s)    ((s) & 0x8000)

#ifndef _XTEND_COMMON_H_
#include "common.h"
#endif

/* parse-cmd.c */
char *parse_cmd(char *argv[], int max_args, const char *cmd);

/* spawnlp.c */
int spawnlp(int parent_action, int echo, char *infile, char *outfile, char *errfile, char *arg0, ...);

/* spawnvp.c */
int spawnvp(int parent_action, int echo, char *argv[], char *infile, char *outfile, char *errfile);
void redirect(char *infile, char *outfile, char *errfile);

/* va-usage.c */
void va_usage(const char *format_string, ...);

#endif  // _XTEND_PROC_H_
