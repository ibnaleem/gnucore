#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

bool is_directory(char *path) {

  struct stat st;

  if (stat(path, &st) != 0 ) {return false;}

  return S_ISDIR(st.st_mode);
}

int read_file(char *path) {
  
  FILE* fptr = fopen(path, "r");

  if (fptr == NULL) {
   if (errno == ENOENT) {
    printf("cat: unable to open '%s': no such file\n", path);
    return 1;
   } else if (errno == EACCES) {
   printf("cat: unable to open '%s': permission denied\n", path);
  } else {
    printf(strerror(errno));
  }
    return 1;
  }

  char buff[4096];
  int n = sizeof(buff);

  while (fgets(buff, n, fptr) != NULL) {
    printf("%s", buff);
  }

  fclose(fptr);
  
  return 0;
}

int main(int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("cat: too few arguments: want at least 1, got %d", argc - 1);
    return 1;
  }

  if (argc == 2) {
    char *path = argv[1];

    if (is_directory(path)) {
      printf("cat: cannot access '%s': is a directory\n", path);
      return 1;
    } else {
      read_file(path);
    }

  } else {
    for (int i = 1; i < argc; i++) {
        char *path = argv[i];

        if (is_directory(path)) {
          printf("cat: cannot access '%s': is a directory\n", path);
        }

        printf("\n");
        printf("%s:\n", path);
        read_file(path);
      }
  }
  
  return 0;
}