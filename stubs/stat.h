// Status of a file (by name). Minimal implementation:

int stat(char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}
