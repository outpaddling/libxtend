# libxtend

## Purpose

libxtend is a library of miscellaneous generic C functions, the likes of
which you might find in libc or libm.

They provide some convenient functionality lacking in standard library
functions as well some more esoteric features.

## C programming at a higher level

You may have heard people grumbling that C is too "low-level" to work with
conveniently.  This perspective is not unjustified, but the reality is that
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
tested on Linux, MacOS, and NetBSD as well.  MS Windows is not supported,
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

### Building libxtend locally

Below are cave man install instructions for development purposes, not
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
${DESTDIR}${PREFIX}.  DESTDIR is empty by default and is primarily used by
package managers to stage installations.  PREFIX defaults to ../local.

Add-on libraries required for the build, such as biolibc, should be found
under either ${PREFIX} or ${LOCALBASE}, which defaults to ${PREFIX}.
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
defaults to ${LOCALBASE}.

View the Makefile for full details.
