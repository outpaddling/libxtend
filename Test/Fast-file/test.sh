#!/bin/sh -e

##########################################################################
#   Function description:
#       
#   Arguments:
#       
#   Returns:
#       
#   History:
#   Date        Name        Modification
#   2024-11-20  Jason Bacon Begin
##########################################################################

line()
{
    printf "\n===============\n"
    return 0
}


##########################################################################
#   Function description:
#       
#   Arguments:
#       
#   Returns:
#       
#   History:
#   Date        Name        Modification
#   2024-11-20  Jason Bacon Begin
##########################################################################

check_results()
{
    if cmp $file copy.iso; then
	printf "Source and target files match, test succeeded.\n"
	rm copy.iso
    else
	printf "Error copying file!\n"
	exit 1
    fi
    return 0
}


cd ../..
./cave-man-install.sh
cd Test/Fast-file
for prog in iotest-ffile iotest-low iotest-stdio; do
    # The need for -Wno-implicit-function-declaration is bizarre
    cc -I../.. -O2 -Wno-implicit-function-declaration -o $prog $prog.c -L../.. -lxtend
done

line
rm -f temp.sh*
printf "Testing xt_ffopen() compression...\n"
./iotest-ffile test.sh temp.sh.gz
printf "Testing xt_ffopen() decompression...\n"
./iotest-ffile temp.sh.gz temp.sh
if diff temp.sh test.sh; then
    printf "Source and target files match, test succeeded.\n"
    rm -f temp*
fi

file=FreeBSD-14.1-RELEASE-amd64-disc1.iso
site=https://download.freebsd.org/releases/ISO-IMAGES/14.1
line
printf "Downloading large file $file to test throughput...\n"
for tool in curl wget fetch; do
    if which $tool; then
	fetch=$tool
	break
    fi
done
if [ -z "$fetch" ]; then
    printf "No download tool found, tried curl, wget, and fetch.\n" >> /dev/stderr
    exit 1
fi
if [ $fetch = curl ]; then
    fetch='curl -Ok'
fi
if [ ! -e $file ]; then
    if [ ! -e $file.xz ]; then
	$fetch $site/$file.xz
    fi
    printf 'Uncompressing...\n'
    unxz $file.xz
fi

line
cat << EOM

Running 'cp $file copy.iso',
so the file is buffered for the first test.
Otherwise, the 2nd and subsequent tests will have an advantage.

EOM
cp $file copy.iso
rm copy.iso

for prog in iotest-low iotest-ffile iotest-stdio; do
    line
    printf "Copying with './$prog $file copy.iso'...\n"
    /usr/bin/time ./$prog $file copy.iso
    check_results
    
    if [ $prog = iotest-ffile ]; then
	line
	printf "Copying with './$prog - - < $file > copy.iso'...\n"
	/usr/bin/time ./iotest-ffile - - < $file > copy.iso
	check_results
    fi
done
