#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
typedef char* caddr_t;

int _write(int file, char *ptr, int len) {
    // implémente l’envoi de caractères sur UART ou rien du tout
    return len;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = 0; return 0; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _isatty(int file) { return 1; }
void _exit(int status) { (void)status; while(1); }

caddr_t _sbrk(int incr) {
    extern char _ebss; // défini dans le linker script
    static char *heap = &_ebss;
    char *prev = heap;
    heap += incr;
    return (caddr_t)prev;
}
