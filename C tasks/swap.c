#include<stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		errx(1,"not enough arguments error");
	}
	
	int fd1, fd2;
	fd1 = open(argv[1], O_RDWR);
	if(fd1==-1){
		err(1, "failed to open fd");
	}
	fd2 = open(argv[2], O_RDWR);
	if(fd2==-1)
	{
		close(fd1);
		err(1, "failed to open fd2");
	}
	
	int fd3;
	fd3 = open("my_temp_file", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR);
	if(fd3==-1)
	{
		close(fd1);
		close(fd2);
		err(1, "%s", "my_temp_file");
	}

	char buff[1024];
	ssize_t read_size;
	while((read_size=read(fd1, &buff, sizeof(buff))) > 0)
	{
		if(write(fd3, &buff, read_size) != read_size)
		{
			close(fd1);
			close(fd2);
			close(fd3);
			err(2, "Error while writing");
		}
	}

	lseek(fd1, 0, SEEK_SET);
	while((read_size=read(fd2, &buff, sizeof(buff)))>0)
	{
		if( write(fd1, &buff, read_size) != read_size)
		{
			close(fd1);
			close(fd2);
			close(fd3);
			err(2, "Error while writing");
		}
	}
	
	lseek(fd2, 0, SEEK_SET);
	lseek(fd3, 0, SEEK_SET);

	while((read_size=read(fd3, &buff, sizeof(buff)))>0)
        {
                if( write(fd2, &buff, read_size) != read_size)
                {
                        close(fd1);
                        close(fd2);
                        close(fd3);
                        err(2, "Error while writing");
                }
        }


	close(fd1);
	close(fd2);
	close(fd3);
	execl("/bin/rm", "rm", "my_temp_file", NULL);
}
