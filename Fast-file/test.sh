#!/bin/sh -e

cd ..
./cave-man-install.sh
cd Fast-file
file=~/Save/FreeBSD-13.0-RELEASE-amd64-disc1.iso
for prog in iotest-ffile iotest-low iotest; do
    cc -I.. -O2 -o $prog $prog.c -L.. -lxtend
done

printf "Testing xt_ffopen() compression...\n"
./iotest-ffile test.sh temp.sh.gz
printf "Testing xt_ffopen() decompression...\n"
./iotest-ffile temp.sh.gz temp.sh
if diff temp.sh test.sh; then
    printf "Files match.\n"
    rm -f temp*
fi

printf "Buffering $file to level the playing field...\n"
cp $file copy.iso
rm copy.iso

printf "Testing ffstdin() and ffstdout()...\n"
/usr/bin/time ./iotest-ffile - - < $file > copy.iso
cmp $file copy.iso
rm copy.iso

for prog in iotest-ffile iotest-low iotest; do
    printf "$prog copying to copy.iso...\n"
    /usr/bin/time ./$prog $file copy.iso
    cmp $file copy.iso
    rm copy.iso $prog
done
