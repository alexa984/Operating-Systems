#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
struct Diff
{
	uint16_t allign;
	uint8_t first;
	uint8_t second;
};
int main(int argc, const char* const argv[])
{
	if (argc != 4)
	{
		errx(1,"Wrong argument");
	}

	int fd1 = open(argv[1],O_RDONLY);

	if ( fd1 == -1 )
	{
		err(2,"File does not exist or we cannot read from it: %s", argv[1]);
	}

	int fd2 = open(argv[2],O_RDONLY);

	if ( fd2 == -1 )
	{
		const int temp = errno;
		close(fd1);
		errno = temp;
		err(3,"File does not exist or we cannot read from it: %s", argv[2]);
	}

	int fd3 = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if ( fd3 == -1)
	{
		const int temp = errno;
		close(fd1);
		close(fd2);
		errno = temp;
		err(4,"File cannot be created: %s", argv[3]);
	}

	if (lseek(fd1,SEEK_END,0) > UINT16_MAX)
	{
		err(6,"Overflow");
	}
	else if (lseek(fd2,SEEK_END,0) > UINT16_MAX)
	{
		err(7,"Overflow");
	}
	else
	{
		lseek(fd1,SEEK_SET,0);
		lseek(fd2,SEEK_SET,0);
	}
	
	struct Diff temp;
	uint16_t currentAll = 0;
	
	
	while( read(fd1, &temp.first,sizeof(temp.first)) == sizeof(temp.first) &&
		read(fd2,&temp.second,sizeof(temp.second)) == sizeof(temp.second))
	{
		if ( temp.first != temp.second )
		{
//			printf("%d %d %d\n",currentAll,temp.first,temp.second);
			temp.allign = currentAll;
			write(fd3,&temp,sizeof(temp));
		}
		currentAll += sizeof(temp.first);
	}


	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}


