#!/bin/bash

FILENAME="headers.tex"

if [ -f $FILENAME ]; then
    rm $FILENAME
fi

for i in ../../src/*.h; do

echo "\subsection{`basename $i`}"  >> $FILENAME
echo "\lstinputlisting{$i}" >> $FILENAME

done