#!/bin/sh -e

cd ..
./cave-man-install.sh
cd Fast-file
file=~/Save/FreeBSD-13.0-RELEASE-amd64-disc1.iso
for prog in iotest-ffile iotest-low iotest; do
    cc -I.. -O2 -o $prog $prog.c -L.. -lxtend
done

printf "Buffering $file to level the playing field...\n"
cp $file copy.iso
rm copy.iso

printf "Testing ffstdin()...\n"
/usr/bin/time ./iotest-ffile - - < $file > copy.iso
cmp $file copy.iso
rm copy.iso

for prog in iotest-ffile iotest-low iotest; do
    printf "$prog copying to copy.iso...\n"
    /usr/bin/time ./$prog $file copy.iso
    cmp $file copy.iso
    rm copy.iso $prog
done
