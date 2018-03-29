#!/bin/bash
# Normalizer.sh
# Author: Samuel Labelle
# Date: 28 mars 2018
# Version: 0.0.1

for FILE in $@; do

PNGTYPE="PNG32"
#Some Imagemagick
echo "$FILE --> ${FILE%.*}_N.png"

magick convert "$FILE" +profile "*" "${PNGTYPE}:${FILE%.*}_N.png" >/dev/null 2>&1
done

echo "Done."
exit
