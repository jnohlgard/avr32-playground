// Query whether output stream is a terminal. For consistency with the other minimal implementations, which only support output to stdout, this minimal implementation is suggested:

    int isatty(int file){
       return 1;
    }

