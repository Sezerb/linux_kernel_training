/*----------------------------------------------------------------------------------------------------------------------
    mkfifo fonksiyonu ve isimli boru haberleşmesi
----------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

void exit_sys(const char *msg);
void exit_fail(const char *msg);

int main(int argc, char **argv)
{
    int fd;
    int val;
    int i;
    
    if (argc != 2)
        exit_fail("wrong usage\n");
    
    srand((unsigned int)time(NULL));
    
    if (access(argv[1], F_OK) < 0) /* fifo yok*/
        if (mkfifo(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
            exit_sys("mkfifo");
    
    if ((fd = open(argv[1], O_WRONLY)) < 0)
        exit_sys("open");
    
    for (i = 0; i < 10; ++i) {
        val = rand() % 101;
        printf("writer:val=%d\n", val);
        if (write(fd, &val, sizeof(int)) < 0)
            exit_sys("write");
        
        sleep(1);
    }    
    
    close(fd);   
    remove(argv[1]);
    
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
