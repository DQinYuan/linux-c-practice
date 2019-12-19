#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
typedef struct{
    char name[4];
    int  age;
}people;
main(int argc, char** argv)
{
    int fd,i;
    int pagesize,offset;
    people *p_map;
    // 获得页面大小
    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize is %d\n",pagesize);
    fd = open("testfile",O_CREAT|O_RDWR|O_TRUNC,00777);
    // 文件大小刚好比两个页面稍微小一点
    lseek(fd,pagesize*2-100,SEEK_SET);
    write(fd,"",1);
    offset = 0; //此处offset = 0编译成版本1；offset = pagesize编译成版本2
    p_map = (people*)mmap(NULL,pagesize*3,PROT_READ|PROT_WRITE,MAP_SHARED,fd,offset);
    close(fd);

    for(i = 1; i<10; i++)
    {
        (*(p_map+pagesize/sizeof(people)*i-2)).age = 100;
        printf("access page %d over\n",i);
        (*(p_map+pagesize/sizeof(people)*i-1)).age = 100;
        printf("access page %d edge over, now begin to access page %d\n",i, i+1);
        (*(p_map+pagesize/sizeof(people)*i)).age = 100;
        printf("access page %d over\n",i+1);  // 在page 3时出现段错误
    }
    munmap(p_map,sizeof(people)*10);
}