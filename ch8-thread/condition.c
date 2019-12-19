#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	mutex;
pthread_cond_t	cond;

void handlers(void *arg) {
    if(NULL != arg)
        printf("%s() : [%s]\n", __func__, (char*)arg);
}

void *thread1(void *arg)
{
    pthread_cleanup_push (pthread_mutex_unlock, &mutex);
    pthread_cleanup_push(handlers, "one");

    while(1) {
        printf ("thread1 is running\n");
        pthread_mutex_lock (&mutex);
        pthread_cond_wait (&cond, &mutex);
        printf ("thread1 applied the condition\n");
        pthread_mutex_unlock (&mutex);
        sleep (4);
    }
    // 0表示正常退出时不调用pop进去的函数
    pthread_cleanup_pop (0);
    pthread_cleanup_pop (0);
}

void *thread2(void *arg)
{
    while(1) {
        printf ("thread2 is running\n");
        pthread_mutex_lock (&mutex);
        //pthread_cond_wait (&cond, &mutex);
        printf ("thread2 applied the condition\n");
        pthread_mutex_unlock (&mutex);
        sleep (1);
    }
}

int main(void)
{
    pthread_t tid1, tid2;

    printf ("condition variable study! \n");
    pthread_mutex_init (&mutex, NULL);
    pthread_cond_init (&cond, NULL);
    pthread_create (&tid1, NULL, (void *) thread1, NULL);
    pthread_create (&tid2, NULL, (void *) thread2, NULL);

    sleep(3);

/*    for (int i = 0; i < 10; i++) {
        pthread_cond_signal (&cond);
    }*/

    sleep(1);

    pthread_cancel(tid1);
    //pthread_cancel(tid2);

    // 如果把thread1的cleanup相关语句注释掉，thread2会卡住
    sleep (50);
}
