#!/bin/sh -e

CFLAGS='-g -O -DLIBXTEND_LIBRARY_BUILD'

cd ..
./cave-man-install.sh
cd Test
cc $CFLAGS -o main-test main-test.c -L.. -lxtend
./main-test

# ffile_t
cc $CFLAGS -o ffile ffile.c -L.. -lxtend

# ffile_t macros
sed -e 's|xt_ff_getc|XT_FF_GETC|g' \
    -e 's|xt_ff_putc|XT_FF_PUTC|g' \
    ffile.c > ffile-macros.c
cc $CFLAGS -o ffile-macros -flto ffile-macros.c -L.. -lxtend

# FILE run time
time ./file testfile-FILE

# xt_ffile_t functions
time ./ffile testfile-functions

# xt_ffile_t macros
time ./ffile-macros testfile-macros

head -2 testfile*
cmp testfile-FILE testfile-functions
rm -f testfile* test file ffile ffile-macros
