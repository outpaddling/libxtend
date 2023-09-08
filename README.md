# libxtend

## Purpose

libxtend is a library of miscellaneous generic C functions, the likes of
which you might find in libc or libm.

They provide some convenient functionality lacking in standard library
functions as well some more esoteric features.

Libxtend also provides portable alternatives to functions that are
not well-standardized across platforms and compilers.

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

This [function summary](./functions.md) lists currently available API
functions.
It is also available via "man libxtend" when libxtend is properly installed
via a package manager.  Each function listed has its own man page with
a more detailed description.

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
End users should install using a package manager.  Note that pkgsrc can be used by anyone, on virtually any POSIX operating system, with or without administrator privileges..

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
[GhostBSD](https://ghostbsd.org/) offers an experience very similar
to Ubuntu, but is built on FreeBSD rather than Debian Linux.  GhostBSD
packages lag behind FreeBSD ports slightly, but this is not generally
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

## Instructions for packagers

If you would like to add this project to another package manager
rather than use FreeBSD ports or pkgsrc, basic manual build instructions
for package can be found
[here](https://github.com/outpaddling/Coding-Standards/blob/main/package.md).
Your contribution is greatly appreciated!
