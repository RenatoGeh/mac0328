#!/bin/bash

gcc $1 DIGRAPHlists.c -ansi -pedantic -Wall
./a.out ${@:2}
