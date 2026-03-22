#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>

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

void count_files_and_directories_in_directory(char *path, int *files, int *dirs) {

  int hidden_files = 0;
  int hidden_dirs = 0;
  
  DIR *curr_directory_pointer = opendir(path);

  if (curr_directory_pointer == NULL) {
    printf("cnt: cannot access '%s': permission denied\n", path);
    return;
  }
  
  struct dirent *entry = readdir(curr_directory_pointer);

  while ((entry = readdir(curr_directory_pointer)) != NULL) {

    char *filename = entry->d_name;

    if (filename[0] == '.') {
      if (is_directory(filename)) {
        hidden_dirs++;
        continue;
      } else {
        hidden_files++;
        continue;
      }
    }

    if (is_directory(filename)) {
      (*dirs)++;
    } else {
      (*files)++;
    }
  
  }

  closedir(curr_directory_pointer);

  printf("%d files (%d hidden) - %d directories (%d hidden)\n", *files, hidden_files, *dirs, hidden_dirs);

  return;
}

int main(int argc, char *argv[]) {

  int files = 0;
  int dirs = 0;

  if (argc == 1) {
    count_files_and_directories_in_directory(".", &files, &dirs);
    return 0;
  } else if (argc == 2) {

    char *path = argv[1];

    if (is_directory(path)) {
      printf("\n");
      printf("%s:\n", path);
      count_files_and_directories_in_directory(path, &files, &dirs);
    } else {
      int filelines = count_lines_in_file(path);

      printf("%d %s\n", filelines, path);

      return 0;

    } // else-block (if is_directory(path))

  } else {

    for (int i=1; i < argc; i++) {
      char *path = argv[i];

      files = 0;
      dirs = 0;
      
      if (is_directory(path)) {
        printf("\n");
        printf("%s:\n", path);
        count_files_and_directories_in_directory(path, &files, &dirs);
      } else {

        int filelines = count_lines_in_file(path);

        printf("%d %s\n", filelines, path);


      } // else-block (if is_directory(path))

    } // for-loop

  } // else-block (if argc > 2)

} // main