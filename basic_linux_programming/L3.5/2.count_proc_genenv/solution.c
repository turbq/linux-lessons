#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int pid_check(char *dirname)
{
    int i=0;
    do{
        if ((dirname[i] >= 0x30) & (dirname[i] <= 0x39)){
            i++;
        } else {
            if (dirname[i] == '\0'){
                //printf("is pid\n");
                return 1;
            } else {
                //printf("is NOT pid\n");
                return 0;
            }
        }
    }while(i<256);
    //printf("not defined\n");
    return 1;
}

void comm_read(char *buf, char *pid)
{
    char path[256],currCh;
    sprintf(path, "/proc/%s/comm", pid);
    //printf("opening file %s\n",path);
    int fd = open(path, O_RDONLY);
    if(!fd){
        perror("fopen");
        exit(1);
    }
    //printf("success\n");
    do{
        read(fd, &currCh, 1);
        *buf = currCh;
        buf++;
    }while(currCh!='\n');
    *(buf--) = 0;
    *(buf--) = 0;
    //printf("comm_read success\n");
}

int proc_count(const char *name)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc/");
    if(!dir) {
        perror("diropen");
        exit(1);
    }
    
    char readName[256];
    int cnt=0;
    while ( (entry = readdir(dir)) != NULL) {
        if (entry->d_type & DT_DIR){
            //printf("%d - %s [%d] %d\n",
                //(int)entry->d_ino, entry->d_name,
                //entry->d_type, entry->d_reclen);     
            
            if(pid_check(entry->d_name)){
                //printf("comm_read\n");
                comm_read(readName, entry->d_name);
                //printf("%s\n", readName);
                if (strcmp(name, readName)==0){
                    cnt++; 
                    //printf("%s = %s\n", name, readName);
                } else {
                    //printf("%s != %s\n", name, readName);
                }
            }
        }
    }
    closedir(dir);
    
    return cnt;
}

int main()
{
    int procCnt = 0;
    procCnt = proc_count("genenv");
    printf("%d\n",procCnt);

    return 0;
}
