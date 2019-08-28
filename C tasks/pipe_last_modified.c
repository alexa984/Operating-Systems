//implement the following pipeline:   ls -t <arg> | head -n 1

#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include "sys/stat.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        errx(0, "invalid entry");
    }
    struct stat buf;
    stat(argv[1],&buf);
    if(! S_ISDIR(buf.st_mode))
    {
        errx(0, "invalid entry");
    }

    int fd[2];
    pipe(fd);
    pid_t ls_pid;

    ls_pid = fork();
    if(ls_pid<0)
    {
        err(1, "cant fork head");
    }
    else if (ls_pid==0)
    {
        //we are in child with ls. It only writes
        close(fd[0]);
        if(dup2(fd[1], 1) == -1)
        {
            err(2, "cant dup stdout in ls");
        }
        execlp("ls", "ls", "-t", NULL);
    }
    close(fd[1]);
    dup2(fd[0],0);
    execlp("head", "head", "-n1", NULL);

}

