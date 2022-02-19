#!/bin/sh -e

cd ..
make
cd Fast-file
file=~/Save/FreeBSD-13.0-RELEASE-amd64-disc1.iso
for prog in iotest-ffile iotest-low iotest; do
    cc -I.. -O2 -o $prog $prog.c fast-file.c -L.. -lxtend
    printf "$prog copying to copy.iso...\n"
    /usr/bin/time ./$prog $file copy.iso
    cmp $file copy.iso
done
rm copy.iso
