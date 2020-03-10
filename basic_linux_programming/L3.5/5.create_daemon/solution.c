#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    //fork создание процесса демона
    pid_t pid = fork();
    switch(pid){
        case -1:
            perror("fork");
            return -1;
        case 0:
            //child
            //printf("child my pid = %i, returned pid = %i\n",
                //getpid(), pid);
            break;
        default:
            //parent
            //printf("parent my pid = %i, returned pid = %i\n",
                //getpid(), pid);
            //exit parent
            exit(1);
            break;
    }
    //в демоне перейти в корневой каталог
    DIR *dir;
    //struct dirent *entry;

    dir = opendir("/");
    if(!dir) {
        perror("diropen");
        exit(1);
    }
    //установить в демоне новый идентификатор сессии setsid(2)
    pid = setsid();
    if(pid==-1){
        perror("pid");
        exit(1);
    }
    printf("%d\n",pid);

    //закрыть файлы стандартного I/O
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    sleep(1000);
    
    return 0;
}
