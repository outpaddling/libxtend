#!/bin/sh -e

cd ..
make clean all
cd Test
cc -o test test.c -L.. -lxtend
./test
