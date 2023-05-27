#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{

    int i = 0;
    sem_unlink("S1");
    sem_unlink("S2");

    sem_t *mutex1 = sem_open("S1", O_CREAT, 0644, 0);
    sem_t *mutex2 = sem_open("S2", O_CREAT, 0644, 1);
    if (mutex1 == SEM_FAILED)
    {
        printf("Failed to open semaphore\n");
        return -1;
    }
    if (mutex2 == SEM_FAILED)
    {
        printf("Failed to open semaphore\n");
        return -1;
    }

    if (fork() == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            sem_post(mutex2);
            printf("%c\t", i + 65);
            sem_post(mutex1);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            sem_wait(mutex1);
            printf("%d\t", i);
            sem_post(mutex2);
        }
        printf("\n");
    }

    sem_close(mutex1);
    sem_unlink("S1");
    sem_close(mutex2);
    sem_unlink("S2");

    return 0;
}