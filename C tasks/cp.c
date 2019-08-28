#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(){
    FILE *fptr1, *fptr2;
    char filename[100], ch;

    printf("Enter the name of first file:\n");
    scanf("%s", filename);
    if ( (fptr1 = fopen(filename, "r")) == NULL)
    {
        err(1, "Cannot open first file");
    }

    printf("Enter the name of second file:\n");
    scanf("%s", filename);
    if ( (fptr2 = fopen(filename, "w")) == NULL)
    {
        err(1, "Cannot open second file");
    }
    ch = fgetc(fptr1);
    while (ch != EOF)
    {
      fputc(ch, fptr2);
      ch = fgetc(fptr1);
    }
    printf("Content had been copied\n");
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}