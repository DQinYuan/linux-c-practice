#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>

pthread_key_t key;

// 在线程退出时，将以key所关联的value为参数调用它
void destructor (char * str)
{
    printf ("thread %ld ends, param = %s\n", pthread_self(), str);
    free (str);
}

void * thread1(void *arg)
{
    char *selfstr = (char *) malloc(20);

    memset (selfstr, 0, 20);
    strcpy (selfstr, "this is thread1");
    printf ("thread %ld is running\n", pthread_self());
    pthread_setspecific (key, (void *) selfstr);
    sleep (3);
    printf ("thread %ld returns %s\n", pthread_self(), (char *)pthread_getspecific(key));
    sleep (4);
}

void * thread2(void *arg)
{

    char * selfstr = (char *)malloc(20);

    memset (selfstr,0,20);
    strcpy (selfstr, "this is thread2");
    printf ("thread %ld is running\n", pthread_self());
    pthread_setspecific (key, (void *) selfstr);
    sleep (1);
    printf ("thread %ld returns %s\n", pthread_self(), (char *)pthread_getspecific(key));
    sleep (6);
}

int main(void)
{
    pthread_t thid1, thid2;

    printf ("main thread begins running\n");
    pthread_key_create (&key, (void *)destructor);
    pthread_create (&thid1, NULL, thread1, NULL);
    pthread_create (&thid2, NULL, thread2, NULL);
    sleep (8);
    pthread_key_delete (key);
    printf ("main thread exit\n");
    return 0;
}