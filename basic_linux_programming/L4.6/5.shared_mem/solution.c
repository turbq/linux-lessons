#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1000

int main(int argc, char *argv[])
{
    //check if argument exist 
    if(argc!=3){
        fprintf(stderr, "Usage %s <key1> <key2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    key_t key1, key2, myKey=75274;
    int shmid1, shmid2, myShmid;
    int *mem1, *mem2, *myMem;
    key1 = atoi(argv[1]);
    key2 = atoi(argv[2]);

    //attach memory1
    if((shmid1 = shmget(key1, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if((mem1 = shmat(shmid1, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    //attach memory2
    if((shmid2 = shmget(key2, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if((mem2 = shmat(shmid2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    //make new region for sum
    if((myShmid = shmget(myKey, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if((myMem = shmat(myShmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    //make sum of integer objects from memory1+memory2
    int i=0;
    for(i=0; i<100; i++) {
        myMem[i] = mem1[i] + mem2[i];
        //printf("sum = %d\n", myMem[i]);
    }

    printf("%d\n", myKey);

    return 0;
}
