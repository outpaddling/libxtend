############################################################################
#
#              Another Programmer's Editor Makefile Template
#
# This is a template Makefile for a simple library.
# It is meant to serve as a starting point for creating a portable
# Makefile, suitable for use under ports systems like *BSD ports,
# MacPorts, Gentoo Portage, etc.
#
# The goal is a Makefile that can be used without modifications
# on any Unix-compatible system.
#
# Variables that are conditionally assigned (with ?=) can be overridden
# via the command line as follows:
#
#       make VAR=value
#
# For example, MacPorts installs to /opt/local instead of the default
# ../local, and hence might use the following:
# 
#       make PREFIX=/opt/local
#
# Different systems may also use different compilers and keep libraries in
# different locations:
#
#       make CC=gcc CFLAGS=-O2 LDFLAGS="-L/usr/X11R6 -lX11"
#
# Variables can also inheret values from parent Makefiles (as in *BSD ports).
#
# Lastly, they can be overridden by the environment, e.g.
# 
#       setenv CFLAGS "-O -Wall -pipe"
#       make
#
# All these override methods allow the Makefile to respect the environment
# in which it is used.
#
# You can append values to variables within this Makefile (with +=).
# However, this should not be used to add compiler-specific flags like
# -Wall, as this would disrespect the environment.
############################################################################

############################################################################
# Installed targets

LIB     = xtend
SLIB    = lib${LIB}.a

# Dynamic/shared library
# Increment when the API changes
API_VER = 1
# Increment for changes that don't affect the API
LIB_VER = 0

# Standard Unix (BSD, Linux, etc.)
SONAME  = lib${LIB}.so.${API_VER}
DLIB    = ${SONAME}.${LIB_VER}

# MacOS
INSTALL_NAME    = lib${LIB}.${API_VER}.dylib
DYLIB           = lib${LIB}.${API_VER}.${LIB_VER}.dylib
CURRENT_VERSION = ${API_VER}.${LIB_VER}
# Need absolute pathname embedded in Apple dylib, or it will only be found
# if the relative path to it is the same as from the build directory.
# Big Sur lacks a realpath command but it can be installed via pkgsrc-wip.
# GNU make 3.81 on Big Sur doesn't support !=, so we must use the gmake
# shell extension and this will fail if not using gmake.
# Fortunately most platforms don't need this.
DYLIB_PATH ?= $(shell realpath ${PREFIX}/lib)

HEADERS = xtend.h xtend-protos.h

############################################################################
# List object files that comprise BIN.

OBJS    = valid-extension.o xcfile.o strisnum.o strptrcmp.o difftimeofday.o \
	  fast-cp.o gcd.o fd-purge.o fgetline.o file-mod-cmp.o get-home-dir.o \
	  ltostrn.o strshellcpy.o num_size.o parse-cmd.o rmkdir.o \
	  spawnlp.o spawnvp.o strlbasecpy.o strblank.o va-usage.o viscpy.o \
	  xt-malloc.o

############################################################################
# Compile, link, and install options

# Where to find local libraries and headers.  For MacPorts, override
# with LOCALBASE=/opt/local.
LOCALBASE   ?= ../local

# Install in ../local, unless defined by the parent Makefile, the
# environment, or a command line option such as PREFIX=/opt/local.
PREFIX      ?= ${LOCALBASE}
MANPREFIX   ?= ${PREFIX}

############################################################################
# Build flags
# Override with "make CC=gcc", "make CC=icc", etc.
# Do not add non-portable options (such as -Wall) using +=
# Make sure all compilers are part of the same toolchain.  Do not mix
# compilers from different vendors or different compiler versions unless
# you know what you're doing.

# Defaults that should work with GCC and Clang.
CC          ?= cc
CFLAGS      ?= -Wall -g -O

# Link command:
# Use ${FC} to link when mixing C and Fortran
# Use ${CXX} to link when mixing C and C++
# When mixing C++ and Fortran, use ${FC} and -lstdc++ or ${CXX} and -lgfortran
LD          = ${CC}

CPP         ?= cpp

AR          ?= ar
RANLIB      ?= ranlib

INCLUDES    += -I${LOCALBASE}/include
CFLAGS      += -fPIC ${INCLUDES}
CXXFLAGS    += -fPIC ${INCLUDES}
FFLAGS      += -fPIC ${INCLUDES}
LDFLAGS     += -L${LOCALBASE}/lib

############################################################################
# Assume first command in PATH.  Override with full pathnames if necessary.
# E.g. "make INSTALL=/usr/local/bin/ginstall"
# Do not place flags here (e.g. RM = rm -f).  Just provide the command
# and let flags be specified separately.

CP      ?= cp
MV      ?= mv
MKDIR   ?= mkdir
LN      ?= ln
RM      ?= rm

# No full pathnames for these.  Allow PATH to dtermine which one is used
# in case a locally installed version is preferred.
PRINTF  ?= printf
INSTALL ?= install
STRIP   ?= strip
CHMOD   ?= chmod

############################################################################
# Standard targets required by package managers

all:    ${SLIB} ${DLIB}

apple:  ${SLIB} ${DYLIB}

${SLIB}: ${OBJS}
	${AR} r ${SLIB} ${OBJS}
	${RANLIB} ${SLIB}

${DLIB}: ${OBJS}
	${CC} -shared ${CFLAGS} -Wl,-soname=${SONAME} -o ${DLIB} ${OBJS}

${DYLIB}: ${OBJS}
	$(CC) $(CFLAGS) -dynamiclib \
	    -install_name ${DYLIB_PATH}/${INSTALL_NAME} \
	    -current_version ${CURRENT_VERSION} \
	    -compatibility_version ${API_VER} \
	    -o ${DYLIB} ${OBJS}

############################################################################
# Include dependencies generated by "make depend", if they exist.
# These rules explicitly list dependencies for each object file.
# See "depend" target below.  If Makefile.depend does not exist, use
# generic source compile rules.  These have some limitations, so you
# may prefer to create explicit rules for each target file.  This can
# be done automatically using "cpp -M" or "cpp -MM".  Run "man cpp"
# for more information, or see the "depend" target below.

# Rules generated by "make depend"
# If Makefile.depend does not exist, "touch" it before running "make depend"
include Makefile.depend

############################################################################
# Self-generate dependencies the old-fashioned way

depend:
	rm -f Makefile.depend
	for file in *.c; do \
	    ${CC} ${INCLUDES} -MM $${file} >> Makefile.depend; \
	    ${PRINTF} "\t\$${CC} -c \$${CFLAGS} $${file}\n\n" >> Makefile.depend; \
	done

############################################################################
# Remove generated files (objs and nroff output from man pages)

clean:
	rm -f ${OBJS} ${SLIB} lib*.so.* lib*.dylib *.nr

# Keep backup files during normal clean, but provide an option to remove them
realclean: clean
	rm -f .*.bak *.bak *.BAK *.gmon core *.core

############################################################################
# Install all target files (binaries, libraries, docs, etc.)

common-install:
	${MKDIR} -p ${DESTDIR}${PREFIX}/lib \
	    ${DESTDIR}${PREFIX}/include \
	    ${DESTDIR}${PREFIX}/man/man3
	for file in ${HEADERS}; do \
	    ${INSTALL} -m 0444 $${file} ${DESTDIR}${PREFIX}/include; \
	done
	${INSTALL} -m 0444 Man/*.3 ${DESTDIR}${MANPREFIX}/man/man3

install: all common-install
	${INSTALL} -m 0444 ${SLIB} ${DESTDIR}${PREFIX}/lib
	${INSTALL} -m 0555 ${DLIB} ${DESTDIR}${PREFIX}/lib
	${INSTALL} -ls ${DLIB} ${DESTDIR}${PREFIX}/lib/${SONAME}
	${INSTALL} -ls ${DLIB} ${DESTDIR}${PREFIX}/lib/lib${LIB}.so

install-strip: install
	${CHMOD} 0655 ${DESTDIR}${PREFIX}/lib/${DLIB}
	${STRIP} ${DESTDIR}${PREFIX}/lib/${DLIB}
	${CHMOD} 0555 ${DESTDIR}${PREFIX}/lib/${DLIB}

apple-install: apple common-install
	${INSTALL} -m 0444 ${SLIB} ${DESTDIR}${PREFIX}/lib
	${INSTALL} -m 0555 ${DYLIB} ${DESTDIR}${PREFIX}/lib
	ln -sf ${DYLIB} ${DESTDIR}${PREFIX}/lib/${INSTALL_NAME}
	ln -sf ${DYLIB} ${DESTDIR}${PREFIX}/lib/lib${LIB}.dylib

help:
	@printf "Usage: make [VARIABLE=value ...] all\n\n"
	@printf "Some common tunable variables:\n\n"
	@printf "\tCC        [currently ${CC}]\n"
	@printf "\tCFLAGS    [currently ${CFLAGS}]\n"
	@printf "\tCXX       [currently ${CXX}]\n"
	@printf "\tCXXFLAGS  [currently ${CXXFLAGS}]\n"
	@printf "\tF77       [currently ${F77}]\n"
	@printf "\tFC        [currently ${FC}]\n"
	@printf "\tFFLAGS    [currently ${FFLAGS}]\n\n"
	@printf "View Makefile for more tunable variables.\n\n"

