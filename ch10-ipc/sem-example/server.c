#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RESOURCE	5

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main(void)
{
    key_t		key;
    int		semid;
    // 非阻塞申请
    struct sembuf	sbuf = {0, -1, IPC_NOWAIT};
    union semun	semopts;

    if ((key = ftok(".", 's')) == -1)
    {
        perror ("ftok error!\n");
        exit(1);
    }

    if ((semid = semget (key,1,IPC_CREAT|0666)) == -1)
    {
        perror ("semget error!\n");
        exit (1);
    }

    // 设置信号量的初始值为5
    semopts.val = MAX_RESOURCE;
    if (semctl (semid,0,SETVAL, semopts) == -1)
    {
        perror ("semctl error!\n");
        exit (1);
    }

    while (1)
    {
        if(semop(semid, &sbuf, 1) == -1)
        {
            perror ("semop error!\n");
            exit (1);
        }
        sleep (3);
    }

    exit (0);
}
