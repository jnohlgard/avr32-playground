// A pointer to a list of environment variables and their values. For a minimal environment, this empty list is adequate:

char *__env[1] = { 0 };
char **environ = __env;
