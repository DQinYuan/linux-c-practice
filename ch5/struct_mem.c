//
// Created by dqyuan on 2019/11/11.
//
#include "stdio.h"

struct inner {
    char c1;
    double d;
    char c2;
};

union data4u {
    struct inner t1;
    int i;
    char c;
};

struct data4s {
    struct inner t1;
    int i;
    char c;
};

struct inner1 {
    char c1;
    char c2;
    double d;
};

int main() {
    struct inner inn;
    struct inner1 inn1;
    union data4u d4u;
    struct data4s d4s;
    
    printf("%d %d %d %d\n", sizeof(inn), sizeof(inn1), sizeof(d4u), sizeof(d4s));
}