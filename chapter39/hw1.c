#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>

char *permissions(struct stat st) {
  char *modeval = malloc(sizeof(char) * 9 + 1);
  mode_t perm = st.st_mode;
  modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
  modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
  modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
  modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
  modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
  modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
  modeval[6] = (perm & S_IROTH) ? 'r' : '-';
  modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
  modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
  modeval[9] = '\0';
  return modeval;
}

int hw1(int argc, char **argv) {
  if (argc <= 1) {
    fprintf(stderr, "input filename.\n");
    exit(-1);
  }
  char *file = argv[1];
  struct stat file_stat;
  stat(file, &file_stat);
  printf("file %s\n"
         "size %.4f kb\n"
         "block %ld\n"
         "links %ld\n",
         file, file_stat.st_size * 1.0 / 1000, (long)file_stat.st_blocks,
         (long)file_stat.st_nlink);
  //当目录中的文件数目增加或减少，其 links 数目增加或减少
  return 0;
}

int hw2(int argc, char **argv) {
  int only_name = argc <= 1;
  int with_more = argc > 1 && strcmp(argv[1], "-l") == 0;
  DIR *d;
  if (argc > 2)
    d = opendir(argv[2]);
  else
    d = opendir(".");
  struct dirent *file;
  struct stat *file_stat;
  while ((file = readdir(d)) != NULL) {
    if (only_name) {
      printf("%s\n", file->d_name);
    } else {
      printf("%s\t", file->d_name);
      fstat(file->d_ino, file_stat);
      // use S_ISREG, ISDIR to check st_mode
      // use S_IRUSR S_IWUSR S_IXUSR 等检查用户读写执行权限
      printf("%o\t%s\t%d\n", file_stat->st_mode, permissions(*file_stat),
             file_stat->st_uid);
    }
  }
  closedir(d);
  return 0;
}

int hw3(int argc, char **argv) {
  if (argc <= 1) {
    fprintf(stderr, "input one file\n");
    exit(-1);
  }
  int tail_number = 10;
  char *filename;
  if (argv[1][0] == '-' && isnumber(argv[1][1])) {
    tail_number = atoi(++argv[1]);
    filename = argv[2];
  } else {
    filename = argv[1];
  }
  printf("file name is %s, tail %d\n", filename, tail_number);
  struct stat file_info;
  int rc = stat(filename, &file_info);
  if (rc < 0 || !S_ISREG(file_info.st_mode)) {
    fprintf(stderr, "fetch file error\n");
    exit(-1);
  }
  int fd = open(filename, O_RDONLY);
  long filesize = file_info.st_size;
  printf("move point to %lld\n", lseek(fd, -1, SEEK_END));
  char now[1];
  long current;
  while (1) {
    current = lseek(fd, -2, SEEK_CUR);
    read(fd, now, 1);
    if (now[0] == '\n') {
      tail_number--;
      if (tail_number == 0)
        break;
    }
  }
  printf("current is %ld, result is:\n\n", current);
  char *allrest = malloc(file_info.st_size - current);
  read(fd, allrest, file_info.st_size - current);
  write(1, allrest, file_info.st_size - current);
  write(1, "\n", 1);
  return 0;
}

void printSub(char *name, int level) {
  char cwd[100];
  getcwd(cwd, 100);
  struct stat info;
  stat(name, &info);
  if (S_ISDIR(info.st_mode)) {
    DIR *d = opendir(name);
    struct dirent *sub;
    while ((sub = readdir(d)) != NULL) {
      if (DT_DIR & sub->d_type) {
        if (strcmp(sub->d_name, ".") != 0 && 
            strcmp(sub->d_name, "..") != 0) {
          for (int i = 0; i < level; i++)
            putchar(' ');
          printf("|- %s\n", sub->d_name);
          chdir(name);
          printSub(sub->d_name, level + 4);
          chdir(cwd);
        }
      } else {
        for (int i = 0; i < level; i++)
          putchar(' ');
        printf("|- %s\n", sub->d_name);
      }
    }
    closedir(d);
  } else {
    for (int i = 0; i < level; i++)
      putchar(' ');
    printf("|- %s\n", name);
  }
}

int hw4(int argc, char **argv) {
  if (argc <= 1) {
    perror("input your file");
    exit(-1);
  }
  char *filename = argv[1];
  printSub(filename, 1);
  return 0;
}

void printSub2(char *name, int level) {
  char cwd[100];
  getcwd(cwd, 100);
  struct stat info;
  stat(name, &info);
  if (S_ISDIR(info.st_mode)) {
    chdir(name);
    if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
      for (int i = 0; i < level; i++)
        putchar(' ');
      printf("|- %s\n", name);
    }
    DIR *d = opendir(".");
    struct dirent *sub;
    while ((sub = readdir(d)) != NULL) {
      if (strcmp(sub->d_name, ".") != 0 && strcmp(sub->d_name, "..") != 0) {
        printSub2(sub->d_name, level + 4);
      }
    }
    chdir(cwd);
    closedir(d);
  } else {
    for (int i = 0; i < level; i++)
      putchar(' ');
    printf("|- %s\n", name);
  }
}

int hw42(int argc, char **argv) {
  if (argc <= 1) {
    perror("input your file");
    exit(-1);
  }
  char *filename = argv[1];
  printSub(filename, 1);
  return 0;
}

int main(int argc, char **argv) { return hw42(argc, argv); }