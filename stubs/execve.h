// Transfer control to a new process. Minimal implementation (for a system without processes):

#include <errno.h>
#undef errno
extern int errno;
int execve(char *name, char **argv, char **env){
  errno=ENOMEM;
  return -1;
}
