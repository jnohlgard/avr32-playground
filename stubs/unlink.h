// Remove a file's directory entry. Minimal implementation:

#include <errno.h>
#undef errno
extern int errno;
int unlink(char *name){
  errno=ENOENT;
  return -1; 
}
