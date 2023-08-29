#!/bin/sh -e

cd ..
./cave-man-install.sh
cd Test
cc -o main-test main-test.c -L.. -lxtend
./main-test

# ffile_t
cc -o ffile ffile.c -L.. -lxtend
rm -f testfile*
time ./ffile testfile1

# FILE
sed -e 's|ffile_t|FILE|g' \
    -e 's|ff|f|g' \
    -e 's|O_WRONLY\|O_CREAT\|O_TRUNC|"w"|g' \
    -e 's|O_RDONLY|"r"|g' \
    -e 's|FFGETC|getc|g' \
    ffile.c > file.c
cc -o file file.c -L.. -lxtend
time ./file testfile2

head -2 testfile*
cmp testfile1 testfile2
rm -f testfile* test file ffile
