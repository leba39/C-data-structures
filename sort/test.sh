#!/bin/bash
#SORT TEST SCRIPT

bbl_out=bbl_results.txt
leba_out=ms_leba_results.txt
morton_out=ms_morton_results.txt

if ! test -e bbl_test.c || ! test -e ms_test_leba.c || ! test -e ms_test_morton.c || ! test -e makefile
then
    echo "Sources not found! Quitting."
    exit
fi

if test -e bbl && test -e ms_leba && test -e ms_morton
then
    echo "Binaries found!"
else
    echo "Compiling sources..."
    make all
fi

echo "TESTING..."
echo "B U B B L E   S O R T" > $bbl_out
echo "M S   L E B A   S O R T" > $leba_out
echo "M S   M O R T O N   S O R T" > $morton_out

start=256
multiply=2
for((n=1 ; n<=10 ; n++))
do
    echo "PASS NUMBER: $n > N=$start"
    echo "INPUT N: $start" | tee -a $bbl_out $leba_out >> $morton_out
    (time ./bbl $start) > /dev/null 2>> $bbl_out
    (time ./ms_leba $n) > /dev/null 2>> $leba_out
    (time ./ms_morton $n) > /dev/null 2>> $morton_out

    start=$[start*multiply]
done
