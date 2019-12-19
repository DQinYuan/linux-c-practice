//
// Created by dqyuan on 2019/11/9.
// gcc -g gdbtest.c -o test

#include "stdio.h"

int get_sum(int n) {
    int sum = 0, i;
    for (i=0; i < n; i++){
        sum += i;
    }
    return sum;
}

int main(){
    int i = 100, result;
    result = get_sum(i);
    printf("1+2+...+%d=%d\n", i, result);
    return 0;
}

