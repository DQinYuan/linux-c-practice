#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char name[4];
    int  age;
}people;

main(int argc, char** argv) // map a normal file as shared mem:
{
    int fd,i;
    people *p_map;
    char temp;

    fd=open("normal_file",O_CREAT|O_RDWR|O_TRUNC,00777);
    // 将文件长度设置为5个people大小 -1因为offset是从0开始的
    lseek(fd,sizeof(people)*5-1,SEEK_SET);
    write(fd,"",1);

    p_map = (people*) mmap( NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,
                            MAP_SHARED,fd,0 );
    close( fd );
    temp = 'a';
    // name分别为 b c  d e ...
    // age 分别为20 21 22 ...
    for(i=0; i<10; i++)
    {
        temp += 1;
        memcpy( ( *(p_map+i) ).name, &temp,2 );
        ( *(p_map+i) ).age = 20+i;
    }
    printf(" initialize over \n ");
    sleep(10);
    // 取消映射
    munmap( p_map, sizeof(people)*10 );
    printf( "umap ok \n" );
}