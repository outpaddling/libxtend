#!/bin/sh -e

: ${PREFIX:=../local}
: ${LOCALBASE:=/usr/local}

# Undefined macro in stdlib.h
extras=-D_Noreturn=""

if [ $# -gt 0 ]; then
    files="$@"
else
    files=*.c
fi

for file in $files; do
    cproto $extras -I$LOCALBASE/include $file
done
