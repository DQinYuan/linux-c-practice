//
// Created by dqyuan on 2019/11/24.
//
/*
静态库：
gcc -o mylib.o -c mylib.c
ar rcs libmylib.a mylib.o
cp libmylib.a /usr/lib/libmylib.a

动态库：
gcc -fPIC -shared -o libttt.so mylib.c
 * */

#include "mylib.h"
#include <stdio.h>

void welcome()
{
    printf("Welcome to libmylib\n");
}

void outstring(const char * str)
{
    if (str != NULL)
        printf("%s\n", str);
}
