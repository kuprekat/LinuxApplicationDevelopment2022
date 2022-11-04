#!/bin/bash

DELAY=0.02
if [ $# = 1 ]; then
    DELAY=$1
fi
INPUT_TEXT=$(cat - | od -An -t x1 -w1 -v)
COL=0
LINE=0
TEXT_COORDS=""
while read -r CHAR; do
    if [ $CHAR = '0a' ]; then
        COL=0
        ((LINE++))
        continue
    fi
    if [ $CHAR != '20' ]; then
        TEXT_COORDS+="${LINE} ${COL} ${CHAR}\n"
    fi
    ((COL++))
done <<< $INPUT_TEXT
TEXT_COORDS="$(echo -ne "$TEXT_COORDS" | shuf)"
LAST_LINE=$LINE

tput clear
while read -r LINE COL CHAR; do
    sleep $DELAY
    tput cup "$LINE" "$COL"
    echo -ne "\x${CHAR}"
done <<< $TEXT_COORDS
tput cup $LAST_LINE 0
