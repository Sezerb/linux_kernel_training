/*----------------------------------------------------------------------------------------------------------------------
    Aşağıdaki örnekte shared memory den okuma yapan process yazma yapan tarafından açıldığından sonra okunacağı garanti
    altındadır
----------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SHM_LENGTH      1024

void exit_sys(const char *msg);
void exit_fail(const char *msg);

int main(int argc, char **argv)
{
    int fd;
    void *ptr;
    pid_t pid;
    
    if ((fd = shm_open("/myshm", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
        exit_sys("shm_open");
    
    if (ftruncate(fd, SHM_LENGTH) < 0)
        exit_sys("ftruncate");
    
    if ((ptr = mmap(NULL, SHM_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
        exit_sys("mmap");
    
    
    strcpy((char *)ptr, "Hello shared memory\n");
    
    puts((char *)ptr);
    
    
    if ((pid = fork()) < 0)
        exit_sys("fork");
    
    if (pid == 0)
        if (execl("./reader", "./reader", (char *)NULL) < 0)
            exit_sys("execl");        
        
    wait(NULL);
    
    
    if (munmap(ptr, SHM_LENGTH) < 0)
        exit_sys("munmap");
    
    
    close(fd);
    
    
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
