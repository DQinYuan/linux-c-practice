//
// Created by dqyuan on 2019/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    FILE *stream;
    char * filename = "test";

    errno = 0;

    stream = fopen(filename, "r");
    if (stream == NULL) {
        printf("open file %s failed, errno is %d\n", filename, errno);
        perror("open file fail");
    } else {
        printf("open file %s successfully\n", filename);
    }
}
