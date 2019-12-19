//
// Created by dqyuan on 2019/11/11.
//
#include "stdio.h"

struct person1 {
    char name[20];
    int age;
    char sex;
    char phone[15];
};

struct person2 {
    char name[21];
    int age;
    char sex;
    char phone[15];
};

int main() {
    struct person1 p1;
    struct person2 p2;
    printf("p1 size: %d, p2 size: %d \n", 
            sizeof(p1), sizeof(p2));
}
