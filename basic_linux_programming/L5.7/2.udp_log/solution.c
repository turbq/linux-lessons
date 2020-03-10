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

int main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "Usage %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int s=socket(AF_INET,SOCK_DGRAM,0);
    //printf("soket = %d\n",s);

    inet_aton("127.0.0.1",&local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(s, (struct sockaddr*) &local, sizeof(local));
    //printf("%d\n",result);

    char buf[STRLEN];
    while(1){
        int len = read(s,buf,STRLEN);
        if(strncmp(buf, "OFF\n", 4) == 0) {
            break;
        }
        printf("%s\n",buf);
        memset(buf,0,len);
    }

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
