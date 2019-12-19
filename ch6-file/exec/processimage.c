#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[],char **environ)
{
    int i;

    printf("I am a process image!\n");
    printf("My pid = %d, parentpid = %d\n", getpid(), getppid());
    printf("uid = %d,gid = %d\n", getuid(), getgid());

    for(i=0; i< argc; i++)
        printf("argv[%d]:%s\n",i ,argv[i]);
}