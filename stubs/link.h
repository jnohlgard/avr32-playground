// Establish a new name for an existing file. Minimal implementation:

#include <errno.h>
#undef errno
extern int errno;
int link(char *old, char *new){
  errno=EMLINK;
  return -1;
}
