#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>

bool is_directory(char *path) {

  struct stat st;

  if (stat(path, &st) != 0 ) {return false;}

  return S_ISDIR(st.st_mode);
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("mv: invalid args: want 2, got %d", argc - 1);
    return 1;
  }

  int error_code = 0;

  char* original_path = argv[1];
  char* new_path = argv[2];

  if (is_directory(new_path)) {
    char dest[1024];


    char* filename = strrchr(original_path, '\\');

    if (filename != NULL) {
      filename++;
    } else {
      filename = original_path;
    }

    snprintf(dest, sizeof(dest), "%s/%s", new_path, filename);

    error_code = rename(original_path, dest);

    if (error_code == -1) {
      perror("mv");
      return 1;
    }

    return 0;
  }

  error_code = rename(original_path, new_path);

  if (error_code == -1) {
      perror("mv");
      return 1;
    }

    return 0;

}