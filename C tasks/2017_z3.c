/*
Задача 3. Напишете програма на C, която да работи подобно на командата cat, реализирайки само следната
функционалност:
• общ вид на изпълнение: ./main [OPTION] [FILE]...
• ако е подаден като първи параметър -n, то той да се третира като опция, което кара програмата ви да
номерира (глобално) всеки изходен ред (започвайки от 1).
• програмата извежда на STDOUT
• ако няма подадени параметри (имена на файлове), програмата чете от STDIN
• ако има подадени параметри – файлове, програмата последователно ги извежда
• ако някой от параметрите е тире (-), програмата да го третира като специално име за STDIN
*/

#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <err.h>

#define BUFFER_SIZE 8
static char buffer[BUFFER_SIZE];
struct config_t
{
  bool number;
  bool at_start;
  unsigned int line;
};
static bool reader(const int fd, struct config_t *const cfg)
{
  while (1)
  {
    char ch;
    const ssize_t rd = read(fd, &ch, 1);

    if (rd == -1)
    {
      return false;
    }
    else if (rd == 0)
    {
      return true;
    }

    if (cfg->number && cfg->at_start)
    {
      int s = snprintf(buffer, BUFFER_SIZE, "%6u ", cfg->line);
      if (s >= BUFFER_SIZE || s < 0)
      {
        return false;
      }
      if (write(1, &buffer, s) != s)
      {
        return false;
      }
      cfg->at_start = false;
    }

    if (write(1, &ch, 1) != 1)
    {
      return false;
    }

    if (cfg->number && ch == ’\n’)
    {
      cfg->line++;
      cfg->at_start = true;
    }
  }
}


int main(const int argc, const char *const argv[])
{
  struct config_t cfg = {
      .number = argc > 1 && strcmp(argv[1], "-n") == 0,
      .at_start = true,
      .line = 1
    };

  int res = 0;

  if (argc > 1 + cfg.number)
  {
    for (int idx = 1 + cfg.number; idx < argc; idx++)
    {
      if (strcmp(argv[idx], "-") == 0)
      {
        if (!reader(0, &cfg))
        {
          warn("Could not process stdin");
          res = 1;
        }
      }
      else
      {
        const int fd = open(argv[idx], O_RDONLY);
        if (fd == -1)
        {
          warn("Could not open %s", argv[idx]);
          res = 1;
          continue;
        }
        if (!reader(fd, &cfg))
        {
          warn("Could not process %s", argv[idx]);
          res = 1;
        }
        if (close(fd) == -1)
        {
          warn("Could not close %s", argv[idx]);
          res = 1;
        }
      }
    }
  }
  else
  {
    if (!reader(0, &cfg))
    {
      warn("Could not process stdin");
      res = 1;
    }
  }
  return res;
}
