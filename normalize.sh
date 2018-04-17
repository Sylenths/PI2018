#!/bin/bash
# normalize.sh
# Author: Samuel Labelle
# Date: 13 avril 2018
# Version: 0.0.2

FILENAME_APPEND="_N"
PNGTYPE="PNG32"

if [ "$1" = "" ]; then
    echo 'ERROR: Missing parameters' ; exit 1;
fi

if [ "$1" = "-h" ]; then
    echo "Normaliser's help:"
    echo ""
    echo "USAGES:"
    echo ""
    echo "normalise.sh <FILES>"
    echo "normalise.sh -o <FILES>"
    echo "normalise.sh [-o] -d <dir>"
    echo ""
    echo "OPTIONS"
    echo ""
    echo "-h          Display this help message."
    echo "-o          Must be first option, activates overwriting of original files."
    echo "-d <dir>    Must be first option (or second if -o is present before it);"
    echo "            Normalises directory <dir>"
    echo ""
    echo "NOTE: If you wish to normalise the current directory with -d,"
    echo "      leave <dir> without value."
    exit
fi

if [ "$1" = "-o" ]; then
    echo Overwriting of original files activated.
    FILENAME_APPEND=""
    shift
fi

if [ "$1" = "-d" ]; then

    if [ "$2" != "" ]; then
        cd $2 || { echo 'ERROR: Invalid Directory.' ; exit 1; }
        echo "Normalising content of \"$2\"."
    else
        echo "Normalising content of Current Directory."
    fi
    FILELIST=$(ls)
else
    FILELIST=$@
fi

for FILE in $FILELIST; do

    echo "$FILE --> ${FILE%.*}${FILENAME_APPEND}.png"
    # Where the magick happens
    magick convert "$FILE" +profile "*" "${PNGTYPE}:${FILE%.*}${FILENAME_APPEND}.png" >/dev/null 2>&1

done

echo "Done."
exit
