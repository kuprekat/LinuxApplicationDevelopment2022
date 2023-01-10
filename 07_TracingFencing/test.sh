#!/bin/bash

OK=0
ARGS_ERR=1
OPEN_ERR=2
READ_ERR=3
CLOSE_ERR=5


./move "infile.txt"
if [ $? == $ARGS_ERR ]; then
    echo "Arguments error test: OK"
else
    echo "Arguments error test: FAILED" 
fi

strace -eread -e fault=read:error=EISDIR:when=3 ./move "infile.txt" "outfile.txt"
if [ $? == $READ_ERR ] && [ -e "./infile.txt" ] && [ ! -e "./outfile.txt" ]; then
    echo "Read file test: OK"
else
    echo "Read file test: FAILED"
fi

strace -eclose -e fault=close:error=EBADF:when=3 ./move "infile.txt" "outfile.txt"
if [ $? == $CLOSE_ERR ] && [ -e "./infile.txt" ] && [ ! -e "./outfile.txt" ]; then
    echo "Close file test: OK"
else
    echo "Close file test: FAILED"
fi

strace -eopenat -e fault=openat:error=EACCES:when=3 ./move "infile.txt" "outfile.txt"
if [ $? == $OPEN_ERR ] && [ -e "./infile.txt" ] && [ ! -e "./outfile.txt" ]; then
    echo "Open file test: OK"
else
    echo "Open file test: FAILED"
fi

./move "inblablafile.txt" "outfile.txt"
if [ $? == $OPEN_ERR ]; then
    echo "Open file test: OK"
else
    echo "Open file test: FAILED"
fi

./move "infile.txt" "outfile.txt"
if [ $? == $OK ]  && [ -e "./outfile.txt" ] && [ ! -e "./infile.txt" ]; then
    echo "Common test: OK"
else
    echo "Common test: FAILED" 
fi

LD_PRELOAD=./my_lib.so ./move "PROTECT_infile.txt" "outfile.txt"
if [ $? == $OK ]  && [ -e "./outfile.txt" ] && [ -e "./PROTECT_infile.txt" ]; then
    echo "Protected file test: OK"
else
    echo "Protected file test: FAILED" 
fi

cmp "PROTECT_infile.txt" "outfile.txt"
if [ $? == $OK ]; then
    echo "Protected file comparasion test: OK"
else
    echo "Protected file comparasion test: FAILED" 
fi

echo "Done"
