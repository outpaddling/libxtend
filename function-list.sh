#!/bin/sh -e

##########################################################################
#   Description:
#       
##########################################################################

usage()
{
    printf "Usage: $0 [--check]\n"
    exit 64     # sysexits(3) EX_USAGE
}


##########################################################################
#   Main
##########################################################################

check=no
if [ $# == 1 ] && [ $1 == --check ]; then
    check=yes
elif [ $# != 0 ]; then
    usage
fi

cat << EOM > functions.md
# Libxtend function list

Each function below is documented by a man page.  To view the documentation,
install libxtend using your chosen package manager and run \`man function\`
(e.g. \`man dsv_read_field\`).

This list does not include the numerous accessor and mutator functions
and macros available for classes (xt_dsv_t, xt_ff_t).  See
\$PREFIX/include/libxtend/\*-accessors.h and
\$PREFIX/include/libxtend/\*-mutators.h for a current list.

| Function | Purpose |
|----------|---------|
EOM

# Man page
cat << EOM > Man/libxtend.3
.TH LIBXTEND 3

.SH NAME
libxtend - extensions to standard libraries

.SH SYNOPSIS
.PP
.nf 
.na 
cc -I<prefix>/include file.c -L<prefix>/lib -lxtend
.ad
.fi

.SH "DESCRIPTION"
.B Libxtend
is a low-level C library containing functions like those found in
libc, libm, and other standard libraries.

.SH FUNCTIONS
.nf
.na
EOM

# auto-man2man is available in wip/auto-dev (FreeBSD ports and pkgsrc)
auto-man2man Man/xt_* >> Man/libxtend.3

cat << EOM >> Man/libxtend.3
.ad
.fi

.SH "SEE ALSO"
stdio(3)

.SH AUTHOR
.nf
.na
J Bacon
EOM

# Debug
# man Man/libxtend.3

# For github
for file in Man/*; do
    if [ $file != Man/libxtend.3 ] && ! echo $file | grep -q "_[gs]et_"; then
	name_line=$(auto-man2man $file)
	if [ -n "$name_line" ]; then
	    printf "| ${name_line% - *} | ${name_line#* - } |\n" >> functions.md
	fi
    fi
done

# Debug
if [ $check = yes ]; then
    more functions.md
    grip --export functions.md
    firefox ./functions.html
fi
