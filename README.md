# libxtend

## Purpose

libxtend is a library of miscellaneous generic C functions, the likes of
which you might find in libc or libm.

They provide some convenient functionality lacking in standard library
functions as well some more esoteric features.

## C programming at a higher level

You may have heard people grumbling that C is too "low-level" to work with
conveniently.  This perspective is not completely unjustified, but the reality is that
it doesn't have to be this way.

C was designed to be a minimal language, but not a low-level language.
Dennis Ritchie and friends
deliberately left out any feature that could be implemented reasonably well
by a library function.  For example, unlike earlier languages such as
Fortran and PL/I, C has no built-in input/output statements and no
syntactic support for character strings beyond string constants.  To
compare strings, for example, we use a library function, which is itself
written in C:
```
if ( strcmp(string1, string2) == 0 )
```
Languages with string support would look something like this:
```
if ( string1 == string2 )
```
The latter is regarded by C proponents as a purely cosmetic improvement, not
worthy of the additional complexity required to support it in the C compiler.
Note also that there is more than one way to interpret equality of
strings (e.g. case sensitive or case insentitive), so we would either
need another operator besides ==, or have to fall back on a function
anyway.

The idea was that the C language would provide only the essential features
of a portable, high-level programming language,
and community could extend it by developing a
limitless set of library functions such as strcmp() to make C programming as
easy as programming in more complex languages, albeit not quite as pretty.
Many excellent libraries exist for specific
purposes such as generating hash values, mathematics computations, etc. 
Unfortunately and inexplicably, until libxtend, the community hasn't really
stepped up to extend the limited offerings of the general libraries libc and
libm in a serious way.  I can't help but wonder how many times over the
decades someone has written their own version of
[strtrim()](https://github.com/outpaddling/libxtend/blob/main/string.c).

Libxtend aims to do just that, providing many of the functions people have
often wished were part of the standard libraries.

Better late than never.  Libxtend is here now, growing, fully documented, and
free to use for any purpose.  If you have any ideas or better yet,
functions to contribute, please let us know by opening an issue.

## Summary list of functions

This summary lists available functions.
It is also available via "man libxtend" when libxtend is properly installed
via a package manager.  Each function listed has its own man page with
a more detailed description.

| Function | Purpose |
|-|-|
| _xt_ff_fillbuff(3)  |  Read next block for a fast file stream |
| csv_read_field(3)  |  Read next comma |
| csv_read_field_malloc(3)  |  Read next comma |
| csv_skip_field(3)  |  Read and discard next comma |
| csv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| digits(3)  |  Compute the number of digits in an integer in any base |
| double_cmp(3)  |  Compare two doubles for sort(3), bsearch(3), etc. |
| dsv_line_copy(3)  |  Copy a generica tabular data object |
| dsv_line_free(3)  |  Destroy a generic tabular data object |
| dsv_line_init(3)  |  Initialize generic tabular data object |
| dsv_line_new(3)  |  Create a new generic tabular data object |
| dsv_line_read(3)  |  Read a line of generic tabular data |
| dsv_line_write(3)  |  Write a line of generic tabular data |
| dsv_read_field(3)  |  Read next field from tabular input |
| dsv_read_field_malloc(3)  |  Read next field from tabular input, |
| dsv_skip_field(3)  |  Read and discard next field from tabular input |
| dsv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| float_cmp(3)  |  Compare two floats for sort(3), bsearch(3), etc. |
| gcd(3)  |  Greatest common divisor |
| int_cmp(3)  |  Compare two ints for sort(3), bsearch(3), etc. |
| lcm(3)  |  Least common multiple |
| long_cmp(3)  |  Compare two longs for sort(3), bsearch(3), etc. |
| long_long_cmp(3)  |  Compare two long longs for sort(3), bsearch(3), etc. |
| ltostrn(3)  |  Convert a long to a string in any base from 2 to 36 |
| mv(3)  |  Library function equivalent of mv(1) |
| resolve_hostname(3)  |  Convert hostname to IP address |
| short_cmp(3)  |  Compare two shorts for sort(3), bsearch(3), etc. |
| str2u64(3)  |  Hash a string of up to 8 characters to a 64 |
| str_argv_cat(3)  |  Append argv |
| strblank(3)  |  Return true is a string is empty or only whitespace |
| strisint(3)  |  Return true if string represents an integer value |
| strisreal(3)  |  Return true if string represents a valid real value |
| strllower(3)  |  Copy string and convert upper case to lower |
| strlower(3)  |  Convert all upper case characters to lower |
| xt_redirect(3)  |  Redirect stdin, stdout and stderr if corresponding argument isn't NULL |
| strlupper(3)  |  Copy string and convert lower case to uppper |
| strptrcasecmp(3)  |  Compare two strings through char ** pointers without regard for upper/lower case |
| strptrcmp(3)  |  Compare two strings through char ** pointers |
| strshellcpy(3)  |  Expand a string containing shell metacharacters |
| strsplit(3)  |  Split a string into tokens |
| strsqueeze(3)  |  Squeeze a string by replacing middle with ... |
| strtr(3)  |  Library function equivalent of tr(1) |
| strtrim(3)  |  Trim junk from both ends of a string |
| strupper(3)  |  Covert all lower case characters to upper |
| strviscpy(3)  |  Copy a string, converting invisible characters |
| tsv_read_field(3)  |  Read next tab |
| tsv_read_field_malloc(3)  |  Read next tab |
| tsv_skip_field(3)  |  Read and discard next tab |
| tsv_skip_rest_of_line(3)  |  Read and discard rest of input line |
| xt | daemonize(3)  |
| xt_difftimeofday(3)  |  Compute difference between struct timeval values |
| xt_dprintf(3)  |  Print formatted output to a low |
| xt_factorial(3)  |  Fast factorial function |
| fast_cp(3)  |  Copy a file using optimal block size |
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
| xt_ff_t  |  Fast file stream class library |
| xt_ff_tmpfile(3)  |  Create a fast file stream connected to a temporary file |
| xt_ff_ungetc(3)  |  Put a character back into a fast file stream read buffer |
| xt_fgetline(3)  |  Read a line from a FILE stream, discarding newline |
| xt_file_mod_cmp(3)  |  Compare time stamps on two files |
| xt_fopen(3)  |  Open a raw or compressed file |
| xt_get_home_dir(3)  |  Get process owner's home directory |
| xt_get_user_name(3)  |  Get username of process owner |
| xt_inhale_strings(3)  |  Read list of strings into array |
| xt_n_choose_k(3)  |  Compute binomial coefficient N choose K |
| xt_parse_cmd(3)  |  Convert a command string to an argv |
| xt_read_line_malloc(3)  |  Read a line and allocate memory for it |
| rmkdir(3)  |  Recursively create directories |
| romantoi(3)  |  Convert Roman numeral string to int |
| xt_spawnlp(3)  |  Fork and exec a process from a variable argument list |
| xt_spawnvp(3)  |  Fork and exec a new process from an argv |
| xt_tic(3)  |  Record current high |
| xt_toc(3)  |  Report time since last xt_tic(3) |
| xt_va_usage(3)  |  Print usage message and terminate process |
| xt_valid_extension(3)  |  Determine whether filename extention is usable |

## Design and Implementation

The code is organized following basic object-oriented design principals, but
implemented in C to minimize overhead and keep the source code accessible to
those who don't have time to master the complexities of C++.

Structures are treated as classes, with accessor macros and mutator functions
provided, so dependent applications and libraries should not access
structure members directly.  Since the C language cannot enforce this, it's
up to application programmers to exercise self-discipline.

For detailed coding standards, see
https://github.com/outpaddling/Coding-Standards/.

## Building and installing

libxtend is intended to build cleanly in any POSIX environment on
any CPU architecture.  Please
don't hesitate to open an issue if you encounter problems on any
Unix-like system.

Primary development is done on FreeBSD with clang, but the code is frequently
tested on Linux, MacOS, NetBSD, and OpenIndiana as well.  MS Windows is not supported,
unless using a POSIX environment such as Cygwin or Windows Subsystem for Linux.

The Makefile is designed to be friendly to package managers, such as
[Debian packages](https://www.debian.org/distrib/packages),
[FreeBSD ports](https://www.freebsd.org/ports/),
[MacPorts](https://www.macports.org/), [pkgsrc](https://pkgsrc.org/), etc.
End users should install via one of these if at all possible.

I maintain a FreeBSD port and a pkgsrc package, which is sufficient to install
cleanly on virtually any POSIX platform.  If you would like to see a
package in another package manager, please consider creating a package
yourself.  This will be one of the easiest packages in the collection and
hence a good vehicle to learn how to create packages.

For an overview of available package managers, see the
[Repology website](https://repology.org/).

### Installing libxtend on FreeBSD:

FreeBSD is a highly underrated platform for many types of computing, with over
30,000 libraries and applications in the FreeBSD ports collection,
modern clang compiler, fully-integrated ZFS
filesystem, and renowned security, performance, and reliability.
FreeBSD has a somewhat well-earned reputation for being difficult to set up
and manage compared to user-friendly systems like [Ubuntu](https://ubuntu.com/).
However, if you're a little bit Unix-savvy, you can very quickly set up a
workstation, laptop, or VM using
[desktop-installer](http://www.acadix.biz/desktop-installer.php).
[GhostBSD](https://ghostbsd.org/) offers and experience very similar
to Ubuntu, but is build on FreeBSD rather than Debian Linux.  GhostBSD
packages lag behind FreeBSD by a few months, but this is not generally
an issue and there are workarounds.

To install the binary package on FreeBSD:

```
pkg install libxtend
```

You can just as easily build and install from source.  This is useful for
FreeBSD ports with special build options, for building with non-portable
optimizations such as -march=native, and for 
[work-in-progress ports](https://github.com/outpaddling/freebsd-ports-wip),
for which binary packages are not yet maintained.

```
cd /usr/ports/devel/libxtend && env CFLAGS='-march=native -O2' make install
cd /usr/ports/wip/libxtend && make install
```

### Installing via pkgsrc

pkgsrc is a cross-platform package manager that works on any Unix-like
platform. It is native to [NetBSD](https://www.netbsd.org/) and well-supported
on [Illumos](https://illumos.org/), [MacOS](https://www.apple.com/macos/),
[RHEL](https://www.redhat.com)/[CentOS](https://www.centos.org/), and
many other Linux distributions.
Using pkgsrc does not require admin privileges.  You can install a pkgsrc
tree in any directory to which you have write access and easily install any
of the nearly 20,000 packages in the collection.

The
[auto-pkgsrc-setup](https://github.com/outpaddling/auto-admin/blob/master/User-scripts/auto-pkgsrc-setup)
script will help you install pkgsrc in about 10 minutes.  Just download it
and run

```
sh auto-pkgsrc-setup
```

Then, assuming you selected current packages and the default prefix

```
source ~/Pkgsrc/pkg/etc/pkgsrc.sh   # Or pkgsrc.csh for csh or tcsh
cd ~/Pkgsrc/devel/libxtend
sbmake install clean clean-depends
```

See the pkgsrc documentation for more information.

Community support for pkgsrc is available through the
[pkgsrc-users](http://netbsd.org/mailinglists) mailing list.

### Other package managers

Packages for libxtend are known to exist in the following package managers.
These are maintained by third parties and not directly supported here.

[BioArchLinux](https://github.com/BioArchLinux/Packages)

### Building libxtend locally

Below are caveman install instructions for development purposes, not
recommended for regular use.

1. Clone the repository
2. Run "make depend" to update Makefile.depend
3. Run "make install"

The default install prefix is ../local.  Clone libxtend and dependent
apps into sibling directories so that ../local represents a common path to all
of them.

To facilitate incorporation into package managers, the Makefile respects
standard make/environment variables such as CC, CFLAGS, PREFIX, etc.

The library, headers, and man pages are installed under
`${DESTDIR}${PREFIX}`.  DESTDIR is empty by default and is primarily used by
package managers to stage installations.  PREFIX defaults to ../local.

Add-on libraries required for the build, such as biolibc, should be found
under either `${PREFIX}` or `${LOCALBASE}`, which defaults to `${PREFIX}`.
LOCALBASE can be set independently if you want to use libraries installed
by FreeBSD ports (/usr/local), MacPorts (/opt/local), pkgsrc (/usr/pkg), etc.

To install directly to /myprefix, assuming biolibc is installed there as well,
using a make variable:

```
make PREFIX=/myprefix clean depend install
```

Using an environment variable:

```
# C-shell and derivatives
setenv PREFIX /myprefix
make clean depend install

# Bourne shell and derivatives
PREFIX=/myprefix
export PREFIX
make clean depend install
```

Note that setting LOCALBASE instead of PREFIX will also work, since PREFIX
defaults to `${LOCALBASE}`.

View the Makefile for full details.
