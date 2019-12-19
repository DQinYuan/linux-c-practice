//
// Created by dqyuan on 2019/11/24.
//
/*
 * 使用静态库：gcc -o test test.c -lmylib
 *
 * 使用动态库：gcc -o test test.c ./libttt.so
  * */

#include "mylib.h"
#include <stdio.h>

int main()
{
    printf("create and use library\n");
    welcome();
    outstring("It's successful");
}