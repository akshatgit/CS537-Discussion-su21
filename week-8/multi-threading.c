#include <stdio.h>
#include <pthread.h>


#define THREAD_CNT 5


static void *
worker_func(void *arg) {
    printf("Hello from worker %lu\n", pthread_self());
        // NOTE: on different platforms, pthread_self()
        // might return different things. I know that on
        // Macintosh it returns a pointer to a structure
        // describing the thread. On UNIX it returns a
        // long unsigned int.

    return NULL;
}


int
main(void) {
    pthread_t workers[THREAD_CNT];
    for (int i = 0; i < THREAD_CNT; ++i) {
        pthread_create(&workers[i], NULL, worker_func, NULL);
    }

    for (int i = 0; i < THREAD_CNT; ++i) {
        pthread_join(workers[i], NULL);
    }

    printf("Hello from main thread\n");
}
