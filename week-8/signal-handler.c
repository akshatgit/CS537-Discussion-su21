#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


static void
my_handler(int sig) {
    printf("Captured signal %d\n", sig);
    printf("Terminating...\n");
    exit(0);
}


int
main(void) {
    signal(SIGINT,  my_handler);
    signal(SIGTERM, my_handler);

    printf("Going into an infinite loop...\n");
    while (1) {}

    return 0;
}
