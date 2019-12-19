//
// Created by dqyuan on 2019/11/16.
//

#include <stdio.h>

// 系统预定义的全局变量
extern char **environ;
// 也可以通过下面的main完整形式获得环境变量
// int main(int argc, char * argv[], char ** envp)
int main(int argc, char * argv[])
{
    int i;

    printf("Environment:\n");

    for (i=0;environ[i]!=NULL;i++)
        printf("%s\n", environ[i]);

    return 0;
}