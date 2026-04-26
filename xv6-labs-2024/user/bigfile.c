#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
main()
{
  char buf[BSIZE];
  int fd, i;

  fd = open("big.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf("bigfile: cannot open big.file for writing\n");
    exit(1);
  }

  for(i = 0; i < MAXFILE; i++){
    ((int*)buf)[0] = i;
    if(write(fd, buf, BSIZE) != BSIZE){
      printf("bigfile: error writing block %d\n", i);
      exit(1);
    }
    if(i % 1000 == 0)
      printf(".");
  }

  printf("\nperfectly wrote %ld blocks\n", MAXFILE);
  close(fd);
  exit(0);
}
