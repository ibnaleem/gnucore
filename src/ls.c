#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

bool is_directory(char *path) {

  struct stat st;

  if (stat(path, &st) != 0 ) {return false;}

  return S_ISDIR(st.st_mode);
}

int print_directory_contents(char *path) {
    
  DIR *curr_directory_pointer = opendir(path);

  if (curr_directory_pointer == NULL) {
    printf("ls: cannot access '%s': permission denied\n", path);
    return 1;
  }
  
  struct dirent *entry = readdir(curr_directory_pointer);

  while ((entry = readdir(curr_directory_pointer)) != NULL) {

    char *filename = entry->d_name;

    if (filename[0] == '.') {
      continue;
    }

    if (is_directory(filename)) {
      printf("%s/\n", filename);
    } else {
      printf("%s\n", filename);
    }
  
  }

  closedir(curr_directory_pointer);

  return 0;
}

int main(int argc, char *argv[]) {

  if (argc == 1) {

    print_directory_contents(".");

  } else if (argc == 2) {
    char *path = argv[1];
    print_directory_contents(path);
  } else {

    for (int i = 1; i < argc; i++) {
      char *path = argv[i];

      if (!is_directory(path)) {
        printf("ls: cannot access '%s': not a directory\n", path);
      } else {
        printf("\n");
        printf("%s:\n", path);
        print_directory_contents(path);
      }
    }

  }

  return 0;

}