// Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout---so if you need to generate any output, for example to a serial port for debugging, you should make your minimal write capable of doing this. The following minimal implementation is an incomplete example; it relies on a writechar subroutine (not shown; typically, you must write this in assembler from examples provided by your hardware manufacturer) to actually perform the output.

int write(int file, char *ptr, int len){
    int todo;
  
    for (todo = 0; todo < len; todo++) {
        writechar(*ptr++);
    }
    return len;
}
