// 示例使用sigsuspend函数挂起等待事件的发生
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define	UNHAPPEN	0	// 未发生
#define	HAPPENED	1	// 已发生

/*定义全局变量以标识事件是否发生*/
int		flag_happen;

/*自定义的错误处理函数*/
void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}

void handler_sigint(int signo)
{
    flag_happen = HAPPENED;
}

int main()
{
    sigset_t	newmask, oldmask, zeromask;

    /*安装信号处理函数*/
    if (signal(SIGINT, handler_sigint) == SIG_ERR) {
        my_err("signal", __LINE__);
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGINT);

    /*屏蔽信号SIGINT*/
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT blocked\n");
    }

    while (flag_happen == UNHAPPEN)
        sigsuspend(&zeromask);

    printf("after event happened\n");
    /*... do something else...*/

    /*将信号屏蔽字恢复*/
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        my_err("sigprocmask", __LINE__);
    }

    return 0;
}
