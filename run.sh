#!/bin/bash

echo 'What do you want to run?'
echo '1 - C++'
echo '2 - C'
echo '3 - Python' 

read var

case $var in
    1) g++ -o solution cpp/solution.cpp && ./solution && rm solution ;;
    2) gcc -o solution c/solution.c && ./solution && rm solution ;;
    3) python3 python/solution.py;;
    *) echo 'Choose from 1 to 3'
esac

