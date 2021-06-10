# libxtend

libxtend is a library of miscellaneous generic C functions, the likes of
which you might find in libc or libm.

They provide some convenient functionality lacking in standard library
functions as well some more esoteric features.

The Makefile is designed to be friendly to package managers, such as
[Debian packages](https://www.debian.org/distrib/packages),
[FreeBSD ports](https://www.freebsd.org/ports/),
[MacPorts](https://www.macports.org/), [pkgsrc](https://pkgsrc.org/), etc.
End users should install via one of these if at all possible.

To build locally for development purposes:

1. Clone the repository
2. Run "make depend" to update Makefile.depend
3. Run "make install"

The default install prefix is ../local.  Clone libxtend and dependent apps
into sibling directories so that ../local represents a common path to all of
them.

To facilitate easy packaging, the Makefile respects standard make/environment
variables such as CC, CFLAGS, PREFIX, etc.  For example, to install to
/myprefix:

```
make PREFIX=/myprefix install
```

View the Makefile for full details.
