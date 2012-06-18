// Create a new process. Minimal implementation (for a system without processes):

#include <errno.h>
#undef errno
extern int errno;
int fork() {
  errno=EAGAIN;
  return -1;
}
