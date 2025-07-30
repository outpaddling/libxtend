#!/bin/sh -e

##########################################################################
#
#   Perform a cave-man install for development and testing purposes.
#   For production use, this software should be installed via a package
#   manager such as Debian packages, FreeBSD ports, MacPorts, pkgsrc, etc.
#       
#   History:
#   Date        Name        Modification
#   2021-07-12  Jason Bacon Begin
##########################################################################

# Default to ../local if LOCALBASE is not set
: ${LOCALBASE:=../local}

mkdir -p ${LOCALBASE}/lib

# OS-dependent tricks
# Set rpath to avoid picking up libs installed by package managers in
# /usr/local/lib, etc.
case $(uname) in
Darwin)
    CFLAGS="-Wall -g -O"
    LIBDIR=$(realpath $LOCALBASE/lib)
    LDFLAGS="-L. -L$LIBDIR -Wl,-rpath,$LIBDIR:/usr/lib:/lib"
    install=apple-install
    ;;

*)
    CFLAGS="-Wall -g -O"
    LIBDIR=$(realpath $LOCALBASE/lib)
    LDFLAGS="-L. -L$LIBDIR -Wl,-rpath,$LIBDIR:/usr/lib:/lib"
    install=install
    ;;

esac
if [ $(uname) = SunOS ]; then
    LDFLAGS="$LDFLAGS -lresolv  -lsocket   -lnsl"
fi
export CFLAGS LIBDIR LDFLAGS LOCALBASE
make clean $install
