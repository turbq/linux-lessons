#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cnt1,cnt2;

void Sigusr1CNT_handler(int signalno)
{
    //printf("Called with %d\n",signalno);
    cnt1++;
}

void Sigusr2CNT_handler(int signalno)
{
    //printf("Called with %d\n",signalno);
    cnt2++;
}

void Sigterm_handler(int signalno)
{
    printf("%d %d\n",cnt1,cnt2);
    exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGUSR1, Sigusr1CNT_handler);
    signal(SIGUSR2, Sigusr2CNT_handler);
    signal(SIGTERM, Sigterm_handler);

    while(1);

    return 0;
}
