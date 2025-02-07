#!/bin/sh -e

make clean
rm -f iotest-stdio iotest-low iotest-ffile hl-test temp.sh.gz *.core \
    xt_ff_printf-test.txt *.iso temp-output
ls
git status
