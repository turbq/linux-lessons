#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHM_SIZE 1000

int main()
{
    int shmid1,shmid2;
    key_t key1,key2;
    int *shm1,*shm2,*num;
    
    key1 = 5678;
    key2 = 7747;

    if((shmid1 = shmget(key1, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if((shm1 = shmat(shmid1, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    if((shmid2 = shmget(key2, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if((shm2 = shmat(shmid2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    num = shm1;

    int i=0;
    for(i=0; i<100; i++)
        *num++ = i;
    *num = 0;
    
    num = shm2;

    for(i=100; i>0; i--)
        *num++ = i;
    *num = 0;

    printf("key1 = %d\nkey2 = %d\n", key1, key2);

    return 0;
}
