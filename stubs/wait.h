// Wait for a child process. Minimal implementation:

#include <errno.h>
#undef errno
extern int errno;
int wait(int *status) {
  errno=ECHILD;
  return -1;
}
