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

  while (entry != NULL) {
    printf("%s\n", entry->d_name);
    entry = readdir(curr_directory_pointer);
  }

  closedir(curr_directory_pointer);

  return 0;
}

int main(int argc, char *argv[]) {

  if (argc == 1) {

    print_directory_contents(".");

  } else {

    for (int i = 1; i < argc; i++) {
      char *path = argv[i];

      if (!is_directory(path)) {
        printf("ls: cannot access '%s': not a directory\n", path);
      } else {
        printf("%s:\n", path);
        print_directory_contents(path);
        printf("\n");
      }
    }

  }

  return 0;

}