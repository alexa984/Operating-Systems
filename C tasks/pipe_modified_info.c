// implement the following pipeline:
// find <dir> -type f| xargs stat | grep 'Modify'

#include<unistd.h>
#include<err.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char* argv[])
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t find_pid, xargs_pid;

    if(argc!=2) errx(0, "invalid arguments passed");

    struct stat buff;
    stat(argv[1], &buff);
    if(!S_ISDIR(buff.st_mode)) errx(0, "invalid arguments passed");

    find_pid = fork();
    if(find_pid<0)
    {
        err(1, "cant fork find");
    }
    else if(find_pid==0)
    {
        //in child where exec find
        close(fd1[0]);
        if(dup2(fd1[1], 1) == -1) err(2, "cant dup in find");
        execlp("find", "find", argv[1], "-type", "f", NULL);
        err(3, "cant exec find");
    }
    close(fd1[1]);

    xargs_pid = fork();
    if(xargs_pid<0) err(1, "cant fork xargs");
    else if(xargs_pid == 0)
    {
        //in child to execute xargs
        close(fd2[0]);
        dup2(fd1[0], 0);
        dup2(fd2[1], 1);
        execlp("xargs", "xargs", "stat", NULL);
        err(3, "Cant exec xargs");
    }
    close(fd1[0]);
    close(fd2[1]);
    dup2(fd2[0], 0);
    execlp("grep", "grep", "Modify", NULL);
    err(3, "cant exec grep");

}


