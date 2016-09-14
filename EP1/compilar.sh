#!/bin/bash

gcc -Wall -O2 -ansi -pedantic -Wno-unused-result ep1.c -o ep1

if [[ $? -eq 0 ]]; then
        ./ep1
fi
