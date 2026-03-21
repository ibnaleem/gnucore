#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>

bool is_directory(char *path) {

  struct stat st;

  if (stat(path, &st) != 0 ) {return false;}

  return S_ISDIR(st.st_mode);
}

int main(int argc, char *argv[]) {

}