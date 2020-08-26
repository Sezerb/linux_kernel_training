/*reader.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mqueue.h>


void exit_sys(const char *msg);
void exit_fail(const char *msg);

int main(int argc, char **argv)
{
    mqd_t mq;
    char msg[8192];
    struct mq_attr attr;
    int n;   
    
    
    if ((mq = mq_open("/mymq", O_RDONLY)) < 0)
        exit_sys("mq_open");
    
    
    if (mq_getattr(mq, &attr) < 0)
        exit_sys("mq_getattr");
    
    printf("Maximum number of messages:%ld\n", attr.mq_maxmsg);
    printf("Maximum message size:%ld\n", attr.mq_msgsize);
    
    for (;;) {
        if ((n = mq_receive(mq, msg, 8192, NULL)) < 0)
            exit_sys("mq_receive");
        
        if (n == 0)
            break;
        
        if (!strcmp(msg, "quit"))
            break;
        
        printf("Message:%s\n", msg);
    }
    
    mq_close(mq);   
    
    return 0;
}

void exit_fail(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void exit_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
