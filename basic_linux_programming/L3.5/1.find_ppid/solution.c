#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void isReadValid(ssize_t status)
{
    if(status>0){
        printf("read success\n");
    } else if(!status){
        printf("EOF\n");
    } else {
        printf("error reading file\n");
    }
}

pid_t get_ppid()
{
    char readId[20],ch,readPpid[20];

    int fd = open("/proc/self/status", O_RDONLY);
    printf("file descriptor = %d\n",fd);
    for (int i=0; i<20; i++){
        ssize_t status = read(fd, &ch, 1);
        if(ch != ':'){
            readId[i] = ch;
        } else if(strcmp(readId, "PPid")==0){
            printf("ppid field found\n");
            while(*readPpid != 0x20){
                read(fd, &readPpid, 1);
                *readPpid+=sizeof(readPpid);
            }
            i=20;
        } else {
            while(ch != '\n'){ //finding newline
                read(fd, &ch, 1);
                //printf("%c",ch);
            }
            printf("newline found\n");
            printf("%s\n",readId);
            do{
                readId[i]=0;
            }while(i--);
            isReadValid(status);
            printf("%s\n",readId);
        }
    }

    pid_t pid = 10;
    printf("%s\n",readPpid);
    printf("'%c'\n",ch);
    //printf("%s\n",readId);

    return pid;
}

int main()
{
    pid_t ppid = get_ppid();
    printf("%d\n", ppid);

    return 0;
}
