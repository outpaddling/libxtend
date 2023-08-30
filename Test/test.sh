#!/bin/sh -e

CFLAGS='-g -O -DLIBXTEND_LIBRARY_BUILD'

cd ..
./cave-man-install.sh
cd Test
cc $CFLAGS -o main-test main-test.c -L.. -lxtend
./main-test

# ffile_t
cc $CFLAGS -o ffile ffile.c -L.. -lxtend
rm -f testfile*
time ./ffile testfile1

# ffile_t macros
sed -e 's|xt_ff_getc|XT_FF_GETC|g' \
    -e 's|xt_ff_putc|XT_FF_PUTC|g' \
    ffile.c > ffile-macros.c
cc $CFLAGS -o ffile-macros -flto ffile-macros.c -L.. -lxtend
time ./ffile-macros testfile2

# FILE
sed -e 's|xt_ffile_t|FILE|g' \
    -e 's|xt_ff_|f|g' \
    -e 's|O_WRONLY\|O_CREAT\|O_TRUNC|"w"|g' \
    -e 's|O_RDONLY|"r"|g' \
    ffile.c > file.c
cc $CFLAGS -o file file.c -L.. -lxtend
time ./file testfile3

head -2 testfile*
cmp testfile1 testfile2
rm -f testfile* test file ffile
