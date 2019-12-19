#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/*自定义的错误处理函数*/
void my_err(const char * err_string, int line)
{
    fprintf(stderr, "line:%d  ", line);
    perror(err_string);
    exit(1);
}

/*SIGINT的处理函数*/
void hander_sigint(int signo)
{
    printf("recv SIGINT\n");
}

int main()
{
    sigset_t	newmask, oldmask, pendmask;	// 定义信号集

    /*安装信号处理函数*/
    if (signal(SIGINT, hander_sigint) == SIG_ERR) {
        my_err("signal", __LINE__);
    }

    /*睡眠10秒*/
    sleep(10);

    /*初始化信号集newmask并将SIGINT添加进去*/
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    /*屏蔽信号SIGINT*/
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT blocked\n");
    }

    sleep(10);

    /*获取未决信号队列*/
    if (sigpending(&pendmask) < 0) {
        my_err("sigpending", __LINE__);
    }
    /*检查未决信号队列里面是否有SIGINT*/
    switch (sigismember(&pendmask, SIGINT)) {
        case 0:
            printf("SIGINT is not in pending queue\n");
            break;
        case 1:
            printf("SIGINT is in pending queue\n");
            break;
        case -1:
            my_err("sigismember", __LINE__);
            break;
        default:
            break;
    }

    /*解除对SIGINT的屏蔽*/
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        my_err("sigprocmask", __LINE__);
    } else {
        printf("SIGINT unblocked\n");
    }

    while(1)
        ;

    return 0;
}
