#!/bin/sh -e

cd ..
./cave-man-install.sh

cd Test
cc -o test test.c -L.. -lxtend
./test

cc -o ffile ffile.c -L.. -lxtend
rm -f testfile
time ./ffile
rm -f testfile
sed -e 's|ffile_t|FILE|g' -e 's|ff|f|g' \
    -e 's|O_WRONLY\|O_CREAT\|O_TRUNC|"w"|g' ffile.c > file.c
cc -o file file.c -L.. -lxtend
time ./file
rm -f testfile test file ffile
