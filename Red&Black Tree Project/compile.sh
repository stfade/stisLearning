#!/bin/bash

if [ $1 -eq 1 ]
then
    clang -fsanitize=address rb_tree.c -c
    clang -fsanitize=address user.c -c
    clang -fsanitize=address  main.c -o main rb_tree.o user.o
else
    gcc  rb_tree.c -c
    gcc  user.c -c
    gcc  main.c -o main rb_tree.o user.o
fi
./main
