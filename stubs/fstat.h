// Status of an open file. For consistency with other minimal implementations in these examples, all files are regarded as character special devices. The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.

#include <sys/stat.h>
int fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

