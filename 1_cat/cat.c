#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void catFile(char* f) {
  int fd;
  char buff[4096];
  ssize_t read;
  off_t off = 0;

  if (*f == '-' && f[1] == '\0') 
    fd = 0;
  else {
    fd = open(f, O_RDONLY);
  }

  if (fd >= 0) {
    while ( (read = pread(fd, buff, 4096, off)) > 0) {
      off += read;
      write(1, buff, read);
    }

    if (fd > 0)
      close(fd);
  }
}

void main(int argc, char** argv) {
  int i = 1;

  while (i < argc) {
    catFile(argv[i]);
    i++;
  }
}
