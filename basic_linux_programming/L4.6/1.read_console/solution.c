#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    //check if argument exist 
    if(argc!=3){
        fprintf(stderr, "Usage %s <progname> <parameter>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //get someprog name and its param
    char command[256];
    sprintf(command, "%s %s", argv[1], argv[2]);

    //launch, pipe its output and read
    FILE *fp;
    fp = popen(command, "r");
    if(!fp){
        perror("popen");
        exit(EXIT_FAILURE);
    }

    //count quantity of zeros
    char tmp=0;
    int cnt=0;

    do{
        tmp = fgetc(fp);
        if(tmp=='0'){
            //printf("0x%02x++\n", tmp);
            cnt++;
        } else {
            //printf("0x%02x\n", tmp);
        } 
        //usleep(100000);
    } while(~tmp);
    printf("%d\n",cnt);

    pclose(fp);

    return 0;
}
