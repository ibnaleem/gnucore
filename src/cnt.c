#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

bool is_directory(char *path) {

  struct stat st;

  if (stat(path, &st) != 0 ) {return false;}

  return S_ISDIR(st.st_mode);
}

int count_lines_in_file(char *path) {
  FILE* fptr = fopen(path, "r");

  if (fptr == NULL) {
    printf("cnt: unable to open '%s': permission denied\n", path);
    return 1;
  }

  char buff[4096];
  int n = sizeof(buff);

  int lines = 0;

  while (fgets(buff, n, fptr) != NULL) {
    lines++;
  }

  fclose(fptr);
  
  return lines;
}