#ifndef _XTEND_PROC_H_
#define _XTEND_PROC_H_

#ifdef __cplusplus
extern "C" {
#endif

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

#define get_home_dir(dir, maxlen) \
	    _Pragma("message(\"get_home_dir() is deprecated.  Use xt_get_home_dir().\")") \
	    xt_get_home_dir(dir, maxlen)

/* get-home-dir.c */
char *xt_get_home_dir(char *dir, size_t maxlen);

/* xt-get-user-name.c */
char *xt_get_user_name(char *user_name, size_t maxlen);

/* xt-get-primary-group-name.c */
char *xt_get_primary_group_name(char *primary_group_name, size_t maxlen);

/* parse-cmd.c */
char *xt_parse_cmd(char *argv[], int max_args, const char *cmd);

/* spawnlp.c */
int xt_spawnlp(int parent_action, int echo, char *infile, char *outfile, char *errfile, char *arg0, ...);

/* spawnvp.c */
int xt_spawnvp(int parent_action, int echo, char *argv[], char *infile, char *outfile, char *errfile);
void xt_redirect(char *infile, char *outfile, char *errfile);

/* va-usage.c */
void xt_va_usage(const char *format_string, ...);

/* xt-daemonize.c */
int xt_daemonize(int nochdir, int noclose);

#ifdef __cplusplus
}
#endif

#endif  // _XTEND_PROC_H_
