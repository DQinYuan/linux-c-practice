#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int arg, char *argv[],char ** environ)
{
    int	fd[2];
    pid_t	pid;
    int	stat_val;

    if (pipe(fd))
    {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    switch (pid)
    {
        case -1:
            perror ("fork failed!\n");
            exit(1);
        case 0:
            // 替换标准呢输入
            close (STDIN_FILENO);
            dup (fd[0]);

            execve ("ctrlprocess",(void *)argv,environ);
            exit (0);
        default:
            close(fd[0]);
            /*将命令行第一个参数写进管道*/
            char *cmd = "exit\n";
            write (fd[1], cmd, strlen(cmd));
            break;
    }
    wait (&stat_val);
    exit (0);
}
