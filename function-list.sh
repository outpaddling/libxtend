#!/bin/sh -e

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
#auto-man2man Man/* | awk -F - '$1 !~ "libxtend" { printf("| %s | %s |\n", $1, $2); }' \
#    >> functions.md

# Debug
# grip --export functions.md
# firefox ./functions.html
