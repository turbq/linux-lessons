#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define max(x,y) ((x) > (y) ? (x) : (y))

int digit=0;

int read_and_report(int fd)
{
    char buf[100];
    //printf("FD %d is ready to read\n",fd);

    int bytes = read(fd,buf,99);
    buf[bytes] = 0;

    //printf("Get %d bytes from %d : %s\n", bytes, fd, buf);

    if(bytes){
        int tmp = bytes;
        while((--tmp)>=0) {
            //printf("buf[%d] = 0x%02x\n", tmp, buf[tmp]);
            digit += (buf[tmp] - 0x30);
        }
    }

    return bytes;
}

int main(/*inc c, char **v*/)
{
    int f1 = open("./in1", O_RDONLY|O_NONBLOCK);
    int f2 = open("./in2", O_RDONLY|O_NONBLOCK);

    if (!(f1&&f2)) {
        printf("Error with opening pipes\n");
    }

    //printf("Descriptors: %d %d\n", f1,f2);

    fd_set read_set;

    while(1) {
        int nfds = 0;
        FD_ZERO(&read_set);
        if(f1 > 0){
            FD_SET(f1, &read_set);
            nfds = max(nfds, f1);
        }
        if(f2 > 0){
            FD_SET(f2, &read_set);
            nfds = max(nfds, f2);
        }

        int result = select(nfds+1, &read_set, NULL, NULL, NULL);
        //printf("select returned %d\n",result);
        if (result == -1) {
            perror("select");
        } else if (result) {
            if(FD_ISSET(f1, &read_set)) {
                if(read_and_report(f1) == 0) {
                    f1 = -1;
                    //printf("f1 closed\n");
                }
            }
            if(FD_ISSET(f2, &read_set)) {
                if(read_and_report(f2) == 0) {
                    f2 = -1;
                    //printf("f2 closed\n");
                }
            }
            if((f1 == -1)&&(f2 == -1))
                break;
        }
    }
    printf("%d\n",digit);

    return 0;
}
