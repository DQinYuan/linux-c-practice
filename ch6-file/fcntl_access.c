//
// Created by dqyuan on 2019/11/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
    exit(1);
}

int main() {
    int ret;
    int access_mode;
    int fd;

    if ((fd = open("example_64", O_CREAT|O_TRUNC|O_RDWR)) == -1) {
        // C语言中 __LINE__会被替换为自己所在的行号
        my_err("open", __LINE__);
    }

    /*设置文件打开方式*/
    if ((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0) {
        my_err("fcntl", __LINE__);
    }

    /*获取文件打开方式*/
    // F_GETFL 标志值的最后一个参数传0
    if ((ret = fcntl(fd, F_GETFL, 0)) < 0) {
        my_err("fcntl", __LINE__);
    }
    // flag的最后两位是访问标志
    access_mode = ret & O_ACCMODE;
    if (access_mode == O_RDONLY) {
        printf("example_64 access mode: read only");
    } else if (access_mode == O_WRONLY) {
        printf("example_64 access mode: write only");
    } else if (access_mode == O_RDWR) {
        printf("example_64 access mode: read + write");
    }

    if (ret & O_APPEND) {
        printf(", append");
    }
    if (ret & O_NONBLOCK) {
        printf(", nonblock");
    }
    if (ret & O_SYNC) {
        printf(", sync");
    }
    printf("\n");

    return 0;
}