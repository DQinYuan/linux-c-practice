#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char name[4];
    int  age;
}people;
main(int argc, char** argv)
{
    int i;
    people *p_map;
    char temp;
    p_map=(people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,
                        MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(fork() == 0)
    {
        sleep(2);
        for(i = 0;i<5;i++)
            printf("child read: the %d people's age is %d\n",i+1,(*(p_map+i)).age);
        (*p_map).age = 100;
        munmap(p_map,sizeof(people)*10); //实际上，进程终止时，会自动解除映射。
        exit(0);
    }
    temp = 'a';
    for(i = 0;i<5;i++)
    {
        temp += 1;
        memcpy((*(p_map+i)).name, &temp,2);
        (*(p_map+i)).age=20+i;
    }
    sleep(5);
    printf( "parent read: the first people,s age is %d\n",(*p_map).age );
    printf("umap\n");
    munmap( p_map,sizeof(people)*10 );
    printf( "umap ok\n" );
}