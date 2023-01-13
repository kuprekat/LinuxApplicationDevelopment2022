#!/bin/bash

OK=0

echo 'TEST: backslash in the end'
./esub "b.a"  "qwerty\\"  "abracadabra" 2> test1.txt
echo 'Backslash in the end of substitution' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: invalid reference (no pocket with this number)'
./esub "(b.a)(c.d)"  "qwe\5rty"  "abracadabra" 2> test1.txt
echo 'Invalid reference in substitution (no pocket with this number)' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi


echo 'TEST: invalid reference (not a number)'
./esub "(b.a)(c.d)"  "qwe\rty"  "abracadabra" 2> test1.txt
echo 'Invalid reference in substitution (not a number)' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: no match'
./esub "b..a"  "hehe"  "abracadabra" 2> test1.txt
echo 'abracadabra' | sed -E 's/b..a/hehe/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: simple test (no pockets)'
./esub "b.a"  "hehe"  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/b.a/hehe/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: multiple slash'
./esub "b.a"  "--slash--\\\\\\\\"  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/b.a/--slash--\\\\/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: multiple pockets'
./esub "(b.a)(c.d)"  "-\2-\1-\2-\1-"  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/(b.a)(c.d)/-\2-\1-\2-\1-/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: empty substitution and result'
./esub "a.*a"  ""  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/a.*a//' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: multiple pockets (one inside another)'
./esub "(b.a(c.d))"  "a\2\1a\1"  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/(b.a(c.d))/a\2\1a\1/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'TEST: empty pockets'
./esub "(b.a)*(c.d)"  "-\2-\1-"  "abracadabra" > test1.txt
echo 'abracadabra' | sed -E 's/(b.a)*(c.d)/-\2-\1-/' > test2.txt
cmp test1.txt test2.txt
if [ $? == $OK ]; then
    echo "OK" 
fi

echo 'DONE'
