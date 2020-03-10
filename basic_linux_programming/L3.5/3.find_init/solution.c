#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>

/* prototypes */
void get_init(char*);
void isReadValid(ssize_t);
int seekToChar(const char, int);
void get_ppid(char*);

int main(int argc, char *argv[])
{
    //check if argument exist 
    if(argc!=2){
        printf("no argument\n");
        printf("use pid to watch parents\n");
        exit(1);
    }

    //print current pid
    char *proc_pid = argv[1];
    printf("pid = %s\n", proc_pid);

    //get all ppids to init process
    get_init(proc_pid);

    return 0;
}

/* definitions */
void get_init(char *pid)
{
    //get ppid of current
    get_ppid(pid);
    //check for init if not get next ppid
}

void get_ppid(char *pid)
{
    char path[PATH_MAX];
    sprintf(path, "/proc/%s/status", pid);
    printf("path = %s\n",path);

    int fd = open("/proc/self/status", O_RDONLY);
    /*
    char readId[20],ch,readPpid[20];

    int i;
    for (i=0; i<20; i++){
        ssize_t status = read(fd, &ch, 1);
        if(ch != ':'){
            readId[i] = ch;
        } else if(strcmp(readId, "PPid")==0){
            read(fd,&ch,1);
            break;
        } else {
            ch = seekToChar('\n', fd);
            do{
                readId[i]=0;
            }while(i--);
            readId[++i]=ch;
        }
    }
    i=0;
    while(ch!='\n'){
        read(fd,&ch,1);
        readPpid[i]=ch;
        i++;
    }
    readPpid[i-1]='\0';
    close(fd);
    printf("%s\n",readPpid);
    return;
    */
}

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

int seekToChar(const char ch, int filedescriptor)
{
    char tmp;
    while(tmp != ch){
        read(filedescriptor, &tmp, 1); 
    }
    read(filedescriptor, &tmp, 1); 
    return tmp;
}

