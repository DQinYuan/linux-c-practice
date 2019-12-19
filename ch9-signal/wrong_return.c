#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf	env;	 // 保存待跳转位置的栈信息

/*信号SIGRTMIN+15的处理函数*/
void handler_sigrtmin15(int signo)
{
    printf("recv SIGRTMIN+15\n");
    longjmp(env, 1);	// 返回到env处，注意第二个参数的值
}

/*信号SIGRTMAX-15的处理函数*/
void handler_sigrtmax15(int signo)
{
    printf("recv SIGRTMAX-15\n");
    longjmp(env, 2);	// 返回到env处，注意第二个参数的值
}

int main()
{
    /*设置返回点*/
    switch (setjmp(env)) {
        case 0:
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        case 2:
            printf("return from SIGRTMAX-15\n");
            break;
        default:
            break;
    }

    /*捕捉信号，安装信号处理函数*/
    signal(SIGRTMIN+15, handler_sigrtmin15);
    signal(SIGRTMAX-15, handler_sigrtmax15);

    while (1);

    return 0;
}
