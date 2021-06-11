# libxtend

Purpose
=======

libxtend is a library of miscellaneous generic C functions, the likes of
which you might find in libc or libm.

They provide some convenient functionality lacking in standard library
functions as well some more esoteric features.

Design and Implementation
=========================

The code is organized following basic object-oriented design principals, but
implemented in C to minimize overhead and keep the source code accessible to
scientists who don't have time to master the complexities of C++.

Structures are treated as classes, with accessor and mutator functions
(or macros) provided, so dependent applications and libraries need not access
structure members directly.  Since the C language cannot enforce this, it's
up to application programmers to exercise self-discipline.

Building and installing
=======================

The Makefile is designed to be friendly to package managers, such as
[Debian packages](https://www.debian.org/distrib/packages),
[FreeBSD ports](https://www.freebsd.org/ports/),
[MacPorts](https://www.macports.org/), [pkgsrc](https://pkgsrc.org/), etc.
End users should install via one of these if at all possible.

I maintain a FreeBSD port and a pkgsrc package.

## Installing libxtend on FreeBSD:

FreeBSD is a highly underrated platform for scientific computing, with over
1,800 scientific libraries and applications in the FreeBSD ports collection
(of more than 30,000 total), modern clang compiler, fully-integrated ZFS
filesystem, and renowned security, performance, and reliability.
FreeBSD has a somewhat well-earned reputation for being difficult to set up
and manage compared to user-friendly systems like [Ubuntu](https://ubuntu.com/).
However, if you're a little bit Unix-savvy, you can very quickly set up a
workstation, laptop, or VM using
[desktop-installer](http://www.acadix.biz/desktop-installer.php).  If
you're new to Unix, you can also reap the benefits of FreeBSD by running
[GhostBSD](https://ghostbsd.org/), a FreeBSD distribution augmented with a
graphical installer and management tools.  GhostBSD does not offer as many
options as desktop-installer, but it may be more comfortable for Unix novices.

```
pkg install libxtend
```

## Installing via pkgsrc

pkgsrc is a cross-platform package manager that works on any Unix-like
platform. It is native to [NetBSD](https://www.netbsd.org/) and well-supported
on [Illumos](https://illumos.org/), [MacOS](https://www.apple.com/macos/),
[RHEL](https://www.redhat.com)/[CentOS](https://www.centos.org/), and
many other Linux distributions.
Using pkgsrc does not require admin privileges.  You can install a pkgsrc
tree in any directory to which you have write access and easily install any
of the nearly 20,000 packages in the collection.  The
[auto-pkgsrc-setup](http://netbsd.org/~bacon/) script can assist you with
basic setup.

First bootstrap pkgsrc using auto-pkgsrc-setup or any
other method.  Then run the following commands:

```
cd pkgsrc-dir/devel/libxtend
bmake install clean
```

There may also be binary packages available for your platform.  If this is
the case, you can install by running:

```
pkgin install libxtend
```

See the [Joyent Cloud Services Site](https://pkgsrc.joyent.com/) for
available package sets.

## To build libxtend locally

Below are cave-man install instructions for development purposes, not
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
package managers to stage installations.  PREFIX defaults to ${LOCALBASE}.

To install directly to /myprefix, assuming libxtend is installed there as well,
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
