#include "sharemem.h"

int main()
{
    int	semid, shmid;
    char	*shmaddr;

    if ((shmid = createshm(".", 'm', SHM_SIZE)) == -1)
    {
        exit (1);
    }

    if((shmaddr = shmat (shmid, NULL, 0)) == (char *)-1)
    {
        perror ("attach shared memory error!\n");
        exit (1);
    }

    if((semid = opensem("." ,'s')) == -1)
    {
        exit (1);
    }

    while(1)
    {
        printf("reader: ");
        wait_sem(semid,0);		/* 等待信号值为1 */
        sem_p(semid,0);			/* P操作 */

        printf("%s\n", shmaddr);
        sleep(10);			/* 使writer处于阻塞状态 */

        sem_v(semid,0);			/* V操作 */
        sleep(10);			/* 等待writer进行写操作 */
    }
}
