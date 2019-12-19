// 示例pause挂起等待事件的发生
// 有bug的写法（反面示例）
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define	UNHAPPEN	0	// 未发生
#define	HAPPENED	1	// 已发生

/*定义全局变量以标识事件是否发生*/
int	flag_happen;

void handler_sigint(int signo)
{
    flag_happen = HAPPENED;
}

int main()
{
    /*安装信号处理函数*/
    if (signal(SIGINT, handler_sigint) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (flag_happen == UNHAPPEN)
        // 如果此时发生事件将导致进程永久挂起
        pause();

    printf("after event happened\n");
    /*... you can do something else here ...*/

    return 0;
}
