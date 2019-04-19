#include <errno.h>
#include <semaphore.h>

int destroynamed(char *name, sem_t *sem) {
    int error = 0;

    if (sem_close(sem) == -1)
       error = errno;
    if ((sem_unlink(name) != -1) && !error)
       return 0;
    if (error)        /* set errno to first error that occurred */
       errno = error;
    return -1;
}
