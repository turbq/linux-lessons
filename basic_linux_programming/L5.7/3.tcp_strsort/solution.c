#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define STRLEN 5120

struct sockaddr_in local;

void get_token(int fd, char *token);
int cmp(const void *elem1, const void *elem2);

int main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "Usage %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int ss=socket(AF_INET,SOCK_STREAM,0);
    int cs;
    //printf("soket = %d\n",s);

    inet_aton("127.0.0.1",&local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss,5);
    //printf("%d\n",result);

    cs=accept(ss,NULL,NULL);

    char buf[STRLEN];
    while(1){
        int len = read(cs,buf,STRLEN);
        if(strncmp(buf, "OFF\n", 4) == 0) {
            break;
        }
        qsort(buf, len, 1, cmp);
        write(cs,buf,len);
        memset(buf,0,len);
    }

    return 0;
}

int cmp(const void *elem1, const void *elem2)
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if(f<s) return 1;
    if(f>s) return -1;

    return 0;
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
