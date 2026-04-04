#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {

  char buf[PATH_MAX];

  if (getcwd(buf, PATH_MAX) == NULL) {
    perror("pwd");
    return 1;
  }

  puts(buf);
  
  return 0;
}