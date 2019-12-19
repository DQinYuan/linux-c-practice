//
// Created by dqyuan on 2019/11/19.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// 信号处理函数本质上是中断当前线程，利用当前线程的资源来执行回调函数
void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
    sleep(10);
}

int main()
{
    // 安装信号处理函数
    signal(SIGINT, handler_sigint);

    while (1){
        printf("aaaa\n");
    }

    return 0;
}
