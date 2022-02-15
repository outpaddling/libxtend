#!/bin/sh -e

file=~/Save/FreeBSD-13.0-RELEASE-amd64-disc1.iso
for prog in iotest-low iotest-ffile iotest; do
    cc -o $prog $prog.c
    printf "$prog copying to copy.iso...\n"
    /usr/bin/time ./$prog $file copy.iso
    cmp $file copy.iso
done
rm copy.iso
