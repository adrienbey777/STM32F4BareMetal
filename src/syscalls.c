#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>

// stubs pour libc
void _exit(int status) { (void)status; while(1); }
