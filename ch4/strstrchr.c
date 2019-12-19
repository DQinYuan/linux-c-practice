//
// Created by dqyuan on 2019/11/9.
//
#include <string.h>
#include "stdio.h"

int main() {
    char *s1 = "Linux C Program", *s2="nux", *p;

    p = strstr(s1, s2);
    if(p!=NULL) {
        printf("%s\n", p);
    } else {
        printf("Not Found");
    }
    
    p = strchr(s1,  'C');
    if(p!=NULL){
        printf("%s\n", p);
    } else{
        printf("Not Found");
    }
}
