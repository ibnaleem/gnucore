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

int main(int argc, char *argv[]) {

  if (argc == 1) {
    // print num files and num directories
  } else if (argc == 2) {

    char *path = argv[1];

    if (is_directory(path)) {
      // print num files nad num directories
    } else {
      int filelines = count_lines_in_file(path);

      printf("%d %s\n", filelines, path);

      return 0;

    } // else-block (if is_directory(path))

  } else {

    for (int i=1; i < argc; i++) {
      char *path = argv[i];
      
      if (is_directory(path)) {
      // print num files nad num directories
      } else {

        int filelines = count_lines_in_file(path);

        printf("%d %s\n", filelines, path);


      } // else-block (if is_directory(path))

    } // for-loop

  } // else-block (if argc > 2)

} // main