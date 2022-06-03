#include <fcntl.h>
#include <stdio.h>
#include <sys/dir.h>
#include <sys/stat.h>

int main() {
  char name[30];
  for (int i = 0; i < 10; i++) {
    sprintf(name, "temp_%d", i);
    mkdir(name, 0777);
  }
  DIR *dp = opendir(".");
  struct dirent *d;
  while ((d = readdir(dp)) != NULL)
    printf("%d %s\n", (int)d->d_ino, d->d_name);
  closedir(dp);
  return 0;
}