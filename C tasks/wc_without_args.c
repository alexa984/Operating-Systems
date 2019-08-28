#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char* argv[]){
	int fd;
	char buff;
	int lines=0;
	int words=0;
	int chars=0;
	if (argc != 2)
	{
		fprintf(stderr, "not enough parameters");
		exit(1);
	}
	if ( (fd=open(argv[1], O_RDONLY)) == -1 )
	{
		fprintf(stderr, "Failed to open file");
		exit(2);
	}

	while( read(fd, &buff, 1) > 0 )
	{
		if(buff=='\n'){
			lines++;
			words++;
		}
		else if(buff==' ')
		{
			words++;
		}
		else chars++;
	
	}
	printf("File %s has %d lines, %d words and %d characters.\n", argv[1], lines, words, chars);
close(fd);
}
