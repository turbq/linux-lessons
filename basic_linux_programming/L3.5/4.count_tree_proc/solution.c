#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include <ctype.h>

/* prototypes */
void count_children(char *pid);
void get_init(char*);
int get_child(char *pid);
int get_ppid(char*);
void get_token(int fd, char *token);

int main(int argc, char *argv[])
{
    //check if argument exist 
    if(argc!=2){
        printf("no argument\n");
        printf("use pid to watch children\n");
        exit(1);
    }

    //print current pid
    char *proc_pid = argv[1];
    //printf("%s\n", proc_pid);

    //count children
    count_children(proc_pid);

    return 0;
}

/* definitions */
void count_children(char *pid)
{
    int childCounter = 0;
    int newPid = 1;
    //get child
    //if not last get next
    while(newPid){
        childCounter++;
        newPid = get_child(pid);
        sprintf(pid,"%d",newPid);
    }
    //printf("last child\n");
    printf("%d\n",childCounter);
}

void get_init(char *pid)
{
    int ppid=0;
    do{
        //get ppid of current
        ppid = get_ppid(pid);
        sprintf(pid,"%d",ppid);
    //check for init if not get next ppid
    }while((ppid!=0)&&(ppid!=1));
}

int get_child(char *pid)
{
    char path[PATH_MAX];
    sprintf(path, "/proc/%s/task/%s/children", pid, pid);
    //printf("path = %s\n",path);

    int fd = open(path, O_RDONLY);
    char *token;
    
    token = malloc(sizeof(char)*20);
    if(!token){
        printf("no memory");
    }
    //printf("trying to get token\n");
    get_token(fd, token);
    //printf("success\n");

    //printf("%s\n", token);
    close(fd);
    int itoken = atoi(token);
    free(token);
    return itoken;
}

int get_ppid(char *pid)
{
    char path[PATH_MAX];
    sprintf(path, "/proc/%s/status", pid);
    //printf("path = %s\n",path);

    int fd = open(path, O_RDONLY);
    //printf("%d\n",fd);
    char *token;
    do{
        free(token);
        token = malloc(sizeof(char)*20);
        if(!token){
            printf("no memory");
        }
        get_token(fd, token);
        //printf("token = %s\n",token);
    }while(!(strcmp(token, "PPid")==0));
    //printf("ppid found\n");
    get_token(fd, token);
    //printf("PPid = %s\n", token);
    printf("%s\n", token);
    close(fd);
    return atoi(token);
}

void get_token(int fd, char *token)
{
    char ch,*temp;
    temp = token;
    *temp = '\0';
    while(1){
        if(!read(fd, &ch, 1)){
            //printf("EOF\n");
            break;
        }
        if(isspace(ch)){
            break;
        } else {
            if(!(ch==':'))
                *temp++ = ch;
        }
    }
    *temp = '\0';
}
