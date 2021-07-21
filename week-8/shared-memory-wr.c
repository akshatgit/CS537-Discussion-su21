#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "shared-memory-slot.h"


#define THREAD_CNT 5


int
main(void) {
    int pagesize = getpagesize();

    // Create the shared memory region.
    int shmfd = shm_open("akshat", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (shmfd < 0) {
        perror("shm_open");
        return 1;
    }

    // Extend its size.
    int ret = ftruncate(shmfd, pagesize);
    if (ret != 0) {
        perror("ftruncate");
        return 1;
    }

    // Memory map.
    slot_t *shm_ptr = mmap(NULL, pagesize, PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Shared memory created, writing to it...\n");
    strcpy(shm_ptr[0].str, "Hello");
    shm_ptr[0].num = 123;

    // Wait for user hitting enter...
    printf("Written. Hit Enter to continue...");
    getchar();

    // Unmap.
    ret = munmap(shm_ptr, pagesize);
    if (ret != 0) {
        perror("munmap");
        return 1;
    }

    // Delete the shared memory region.
    ret = shm_unlink("josehu");
    if (ret != 0) {
        perror("shm_unlink");
        return 1;
    }

    return 0;
}
