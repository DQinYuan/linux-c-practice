//
// Created by dqyuan on 2019/11/9.
//
#include <string.h>

int main() {
    char *s = "Linux C";
    char d[20];
    strncpy(d, s, sizeof(s));
}
