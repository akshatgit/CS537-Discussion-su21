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
    int shmfd = shm_open("akshat", O_RDWR, S_IRUSR | S_IWUSR);
    if (shmfd < 0) {
        perror("shm_open");
        return 1;
    }

    // Memory map.
    slot_t *shm_ptr = mmap(NULL, pagesize, PROT_READ, MAP_SHARED, shmfd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("%s %d\n", shm_ptr[0].str, shm_ptr[0].num);

    // Unmap.
    int ret = munmap(shm_ptr, pagesize);
    if (ret != 0) {
        perror("munmap");
        return 1;
    }

    return 0;    
}
