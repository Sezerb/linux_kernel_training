/*----------------------------------------------------------------------------------------------------------------------
    POSIX modern messaj kuyurukları:
    Dikkat: Bazı sürümlerde (Red Hat 7 gibi)  mq_open fonksiyonunun 4. parametresinin hiç olmazsa NULL geçilmesi 
    gerekebilir
----------------------------------------------------------------------------------------------------------------------*/
/*writer.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mmap.h>
#include <mqueue.h>

void exit_sys(const char *msg);
void exit_fail(const char *msg);

int main(int argc, char **argv)
{
    mqd_t mq;
    char msg[1024];
    
    if ((mq = mq_open("/mymq", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, NULL)) < 0)
        exit_sys("mq_open");
    
    for (;;) {
        printf("Input text:\n");
        gets(msg);
        
        if (mq_send(mq, msg, strlen(msg) + 1, 0) < 0)
            exit_sys("mq_send");
        
        if (!strcmp(msg, "quit"))
            break;        
    }
    
    mq_close(mq);
    
    if (mq_unlink("/mymq") < 0)
        exit_sys("mq_unlink");
    
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
