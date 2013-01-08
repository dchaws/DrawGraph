#!/bin/bash

# Script to read input from stdin,
# create temporary tex file, complile to dvi,
# convert to pdf and open it up.

tempdir=/Users/haws/local/tmp/
tempbasename="temp"

./drawgraph -H > ${tempdir}${tempbasename}.tex
latex -output-directory=${tempdir} ${tempdir}${tempbasename} 
dvipdf ${tempdir}${tempbasename}.dvi ${tempdir}${tempbasename}.pdf
open ${tempdir}${tempbasename}.pdf
