//
// Created by dqyuan on 2019/11/11.
//
#include "stdio.h"

struct bit_data
{
    int a: 6;
    int b: 4;
    int : 0;
    int c: 4;
    int d;
} t1;

int main() {
    printf("t1 size: %d\n", sizeof(t1));
}
