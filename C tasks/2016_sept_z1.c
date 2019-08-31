#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

/*
Напишете програма на С, която да работи като обвивка на командата sort тоест
вашата програма изпълнява sort като всички подадени параметри се предават на sort.
Изхода за грешки по време на изпълнението да отива във файл с име serror.txt
*/


int main(int argc, char* argv[])
{
  // int fd1[2]; // fd1[0] is the read end, fd1[1] is the writing end
  //dup2(old_fd, new_fd) duplicates the functions of old fd to new fd

  int my_err_file = open("serror.txt", O_RDWR|O_CREAT);
  dup2(my_err_file, 2);

  if (argc < 2)
  {
    errx(1, "No arguments passed");
  }

  if( execvp("sort", argv) == -1 )
  {
    err(2, "Cant exec sort.");
  }

}
