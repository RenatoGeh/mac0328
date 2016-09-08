#!/bin/bash

:> out.put
for i in 100 500 1000 5000 10000; do
   printf "START -- Kosaraju-Sharir ($i, 1, 2)\n" >> out.put
   (time ./a.out $i 1 2) &>> out.put
   printf "\nSTOP\nSTART -- Naive ($i, 1, 1)\n" >> out.put
   (time ./a.out $i 1 1) &>> out.put
   printf "\nSTOP\n" >> out.put
done
