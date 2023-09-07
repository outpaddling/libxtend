# Libxtend function list

Each function below is documented by a man page.  To view the documentation,
install libxtend using your chosen package manager and run 
(e.g. ).

This list does not include the numerous accessor and mutator functions
and macros available for classes (xt_dsv_t, xt_ff_t).  See
$PREFIX/include/libxtend/\*-accessors.h and
$PREFIX/include/libxtend/\*-mutators.h for a current list.

| Function | Purpose |
|----------|---------|
| xt_csv_read_field(3)  |  Read next comma |
| xt_csv_read_field_malloc(3)  |  Read next comma |
| xt_csv_skip_field(3)  |  Read and discard next comma |
| xt_csv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| xt_daemonize(3)  |  Detach process from terminal |
| xt_difftimeofday(3)  |  Compute difference between struct timeval values |
| xt_digits(3)  |  Compute the number of xt_digits in an integer in any base |
| xt_double_cmp(3)  |  Compare two doubles for sort(3), bsearch(3), etc. |
| xt_dprintf(3)  |  Print formatted output to a low |
| xt_dsv_line_copy(3)  |  Copy a generica tabular data object |
| xt_dsv_line_free(3)  |  Destroy a generic tabular data object |
| xt_dsv_line_init(3)  |  Initialize generic tabular data object |
| xt_dsv_line_new(3)  |  Create a new generic tabular data object |
| xt_dsv_line_read(3)  |  Read a line of generic tabular data |
| xt_dsv_line_write(3)  |  Write a line of generic tabular data |
| xt_dsv_read_field(3)  |  Read next field from tabular input |
| xt_dsv_read_field_malloc(3)  |  Read next field from tabular input, |
| xt_dsv_skip_field(3)  |  Read and discard next field from tabular input |
| xt_dsv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| xt_factorial(3)  |  Fast factorial function |
| xt_fast_cp(3)  |  Copy a file using optimal block size |
| xt_fclose(3)  |  Close a FILE stream opened by xt_fopen(3) |
| xt_fd_purge(3)  |  Discard unread input from input FILE buffer |
| xt_ff_close(3)  |  Close a string created by xt_ff_open(3) |
| xt_ff_close_raw(3)  |  Close a stream created by xt_ff_open_raw(3) |
| xt_ff_dopen(3)  |  Create a fast file stream from a file descriptor |
| xt_ff_getc(3)  |  Read next character from a fast file stream |
| xt_ff_gets(3)  |  Read a line from a fast file stream |
| xt_ff_open(3)  |  Open a fast file stream for a raw or compressed file |
| xt_ff_open_raw(3)  |  Open a fast file stream for a raw file |
| xt_ff_pclose(3)  |  Close a stream created by xt_ff_popen(3) |
| xt_ff_popen(3)  |  Create a fast file stream connected to a process |
| xt_ff_printf(3)  |  Print formatted data to a fast file stream |
| xt_ff_putc(3)  |  Write a character to a fast file stream |
| xt_ff_puts(3)  |  Print a string to a fast file stream |
| xt_ff_read(3)  |  Read a fixed number of bytes from a fast file stream |
| xt_ff_read_line_malloc(3)  |  Read a line from a fast file stream, |
| xt_ff_rewind(3)  |  Reposition file descriptor to beginning of file |
| xt_ff_seeko(3)  |  Reposition file descriptor under a fast file stream |
| xt_ff_stdin(3)  |  Create a fast file stream attached to descriptor 0 |
| xt_ff_stdout(3)  |  Create a fast file stream connected to descriptor 1 |
| xt_ff_tmpfile(3)  |  Create a fast file stream connected to a temporary file |
| xt_ff_ungetc(3)  |  Put a character back into a fast file stream read buffer |
| xt_fgetline(3)  |  Read a line from a FILE stream, discarding newline |
| xt_file_mod_cmp(3)  |  Compare time stamps on two files |
| xt_float_cmp(3)  |  Compare two floats for sort(3), bsearch(3), etc. |
| xt_fopen(3)  |  Open a raw or compressed file |
| xt_gcd(3)  |  Greatest common divisor |
| xt_get_home_dir(3)  |  Get process owner's home directory |
| xt_get_user_name(3)  |  Get username of process owner |
| xt_inhale_strings(3)  |  Read list of strings into array |
| xt_int_cmp(3)  |  Compare two ints for sort(3), bsearch(3), etc. |
| xt_lcm(3)  |  Least common multiple |
| xt_long_cmp(3)  |  Compare two longs for sort(3), bsearch(3), etc. |
| xt_long_long_cmp(3)  |  Compare two long longs for sort(3), bsearch(3), etc. |
| xt_ltostrn(3)  |  Convert a long to a string in any base from 2 to 36 |
| xt_mv(3)  |  Library function equivalent of xt_mv(1) |
| xt_n_choose_k(3)  |  Compute binomial coefficient N choose K |
| xt_parse_cmd(3)  |  Convert a command string to an argv |
| xt_read_line_malloc(3)  |  Read a line and allocate memory for it |
| xt_resolve_hostname(3)  |  Convert hostname to IP address |
| xt_rmkdir(3)  |  Recursively create directories |
| xt_romantoi(3)  |  Convert Roman numeral string to int |
| xt_short_cmp(3)  |  Compare two shorts for sort(3), bsearch(3), etc. |
| xt_spawnlp(3)  |  Fork and exec a process from a variable argument list |
| xt_spawnvp(3)  |  Fork and exec a new process from an argv |
| xt_str2u64(3)  |  Hash a string of up to 8 characters to a 64 |
| xt_str_argv_cat(3)  |  Append argv |
| xt_strblank(3)  |  Return true is a string is empty or only whitespace |
| xt_strisint(3)  |  Return true if string represents an integer value |
| xt_strisreal(3)  |  Return true if string represents a valid real value |
| xt_strllower(3)  |  Copy string and convert upper case to lower |
| xt_strlower(3)  |  Convert all upper case characters to lower |
| xt_redirect(3)  |  Redirect stdin, stdout and stderr if corresponding argument isn't NULL |
| xt_strlupper(3)  |  Copy string and convert lower case to uppper |
| xt_strptrcasecmp(3)  |  Compare two strings through char ** pointers, case insensitive |
| xt_strptrcmp(3)  |  Compare two strings through char ** pointers |
| xt_strshellcpy(3)  |  Expand a string containing shell metacharacters |
| xt_strsplit(3)  |  Split a string into tokens |
| xt_strsqueeze(3)  |  Squeeze a string by replacing middle with ... |
| xt_strtr(3)  |  Library function equivalent of tr(1) |
| xt_strtrim(3)  |  Trim junk from both ends of a string |
| xt_strupper(3)  |  Covert all lower case characters to upper |
| xt_strviscpy(3)  |  Copy a string, converting invisible characters |
| xt_tic(3)  |  Record current high |
| xt_toc(3)  |  Report time since last xt_tic(3) |
| xt_tsv_read_field(3)  |  Read next tab |
| xt_tsv_read_field_malloc(3)  |  Read next tab |
| xt_tsv_skip_field(3)  |  Read and discard next tab |
| xt_tsv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| xt_va_usage(3)  |  Print usage message and terminate process |
| xt_valid_extension(3)  |  Determine whether filename extention is usable |
