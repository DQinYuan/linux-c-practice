// 示例利用信号传递数据，本程序发送数据
// 选项-d 后跟待传递的数据，选项-s 后跟待发送的信号，选项-p 后跟目的进程ID
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    union sigval	value;
    int		signum = SIGTERM;	// 默认发送SIGTERM
    pid_t		pid;
    int		i;

    /*初始化*/
    value.sival_int = 0;

    /*检查参数的个数*/
    if (argc != 3 && argc != 5 && argc != 7) {
        printf("./send_data_signo <-d data> <-s signum> [-p][data]\n");
        exit(1);
    }

    /*从命令行参数解析出信号编号、PID以及待传递的数据*/
    for (i=1; i<argc; i++) {
        if (!strcmp(argv[i], "-d")) {
            value.sival_int = atoi(argv[i+1]);
            continue;
        }
        if (!strcmp(argv[i], "-s")) {
            signum = atoi(argv[i+1]);
            continue;
        }
        if (!strcmp(argv[i], "-p")) {
            pid = atoi(argv[i+1]);
            continue;
        }
    }

    /*利用sigqueue给pid发送信号signum，并携带数据value*/
    if (sigqueue(pid, signum, value) < 0) {
        perror("sigqueue");
        exit(1);
    }

    return 0;
}
