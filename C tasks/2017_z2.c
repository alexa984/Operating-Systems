#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

/*
Напишете програма на С, която използвайки външни shell команди да извежда статистика за използването
на различните shell-ове от потребителите, дефинирани в системата. Изходът да бъде сортиран във възходящ
ред според броя използвания на shell-овете.
*/

int main(int argc, char* argv[]){
  //Recreate "cut -d ':' -f 7 /etc/passwd | sort | uniq -c | sort -n"

  //we need 3 pipes
  int fd1[2];
  int fd2[2];
  int fd3[2];
  pid_t cut_pid, sort_pid, uniq_pid;

  if (pipe(fd1) == -1) err(1, "cant pipe fd1");
  if (pipe(fd2) == -1) err(1, "cant pipe fd2");
  if (pipe(fd3) == -1) err(1, "cant pipe fd3");

  // cut
  cut_pid = fork();
  if (cut_pid < 0) err(2, "cant fork cut");
  else if (cut_pid == 0)
  {
    // we are in child to execute cut
    close(fd1[0]);  // we dont read here
    if( dup2(fd1[1], 1) == -1 ) err(3, "cant dup write inside cut");
    execlp("cut", "cut", "-d:", "-f7", "/etc/passwd", NULL);  // execute cut
    err(4, "cant exec cut");  // we will only come to this if exec fails
  }
  close(fd1[1]);
  // we are done with cut

  // sort
  sort_pid = fork();
  if( sort_pid < 0 ) err(2, "cant fork sort");
  else if ( sort_pid == 0 )  // we are in child to exec sort
  {
    // we will use fd1[0] and fd2[1]
    close(fd2[0]);
    if (dup2(fd1[0], 0) == -1) err(3, "cant dup read inside sort");
    if (dup2(fd2[1], 1) == -1) err(3, "cant dup write inside sort");

    execlp("sort", "sort", NULL);
    err(4, "cant exec sort");  // we will only come to this if exec fails
  }
  close(fd1[0]);
  close(fd2[1]);
  // done with sort


  // uniq
  uniq_pid = fork();
  if( uniq_pid < 0 ) err(2, "cant fork uniq");
  else if(uniq_pid == 0)  // in child to execute uniq
  {
    // we will use fd2[0] and fd3[1]
    close(fd3[0]);
    if( dup2(fd2[0], 0) == -1 ) err(3, "cant dup read inside uniq");
    if( dup2(fd3[1], 1) == -1 ) err(3, "cant dup write inside uniq");
    execlp("uniq", "uniq", "-c", NULL);
    err(4, "cant exec uniq");
  }
  close(fd2[0]);
  close(fd3[1]);
  // done with uniq

  // sort -n
  if( dup2(fd3[0], 0) == -1 ) err(3, "cant dup inside sort -n");
  execlp("sort", "sort", "-n", NULL);

  // we only came here if exec fails
  close(fd3[0]);
  err(4, "cant exec sort -n");

}
