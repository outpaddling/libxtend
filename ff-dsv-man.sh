#!/bin/sh -e

##########################################################################
#   Title:
#       Optional, defaults to the name of the script sans extention
#
#   Section:
#       Optional, defaults to 1
#
#   Synopsis:
#       
#   Description:
#       
#   Arguments:
#       
#   Returns:
#
#   Examples:
#
#   Files:
#
#   Environment:
#
#   See also:
#       
#   History:
#   Date        Name        Modification
#   2024-11-20  Jason Bacon Begin
##########################################################################

usage()
{
    printf "Usage: $0\n"
    exit 64     # sysexits(3) EX_USAGE
}


##########################################################################
#   Main
##########################################################################

if [ $# != 0 ]; then
    usage
fi

cd Man
for page in xt_dsv*; do
    ff_page=xt_ff_${page#xt_}
    echo $page $ff_page
    sed -e 's|xtend/dsv.h|xtend/ff-dsv.h|g' \
	-e 's|xt_dsv_|xt_ff_dsv_|g' \
	-e 's|xt_csv_|xt_ff_csv_|g' \
	-e 's|xt_tsv_|xt_ff_tsv_|g' \
	$page > $ff_page
done
