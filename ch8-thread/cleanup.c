#include <stdio.h>
#include <pthread.h>

void handlers(void *arg) {
    if(NULL != arg)
        printf("%s() : [%s]\n", __func__, (char*)arg);
}

void * thread_start(void *arg) {
    pthread_cleanup_push(handlers, "one");
    pthread_cleanup_push(handlers, "two");
    pthread_cleanup_push(handlers, "thr");
    printf("This is thread [%u]\n", (unsigned int)pthread_self());
    pthread_exit("he~he~");
    //do something
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    return NULL;
}

int main() {
    pthread_t pt;
    pthread_create(&pt, NULL, thread_start, NULL);

    void *r = NULL;
    pthread_join(pt, &r);
    if(NULL != r) {
        printf("thread return : [%s]\n", (const char*)r);
    }

    return 0;
}